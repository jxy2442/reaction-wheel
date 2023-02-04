//------------RIT Launch Initiative---------------
//-------Reaction Control Demonstrator------------
//----------------IREC 2023-----------------------
#include <Arduino.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include <Math.h>

Adafruit_LIS3MDL lis3mdl;

#define PWM 11
#define INA2 10 //If high will set direction to Clockwise 
#define INA1 9 //If high will set direction to Counter Clockwise 
#define ENCA 3
#define ENCB 2
#define signof(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))

const float VOLTS_PER_PWM = 15.0 / 255.0;
const float PWM_PER_VOLT = 1 / VOLTS_PER_PWM;

float min_x = 0.0;
float max_x = 0.0;
float min_y = 0.0;
float max_y = 0.0;
volatile float heading = 0.0;
volatile float headinglp = 0.0;
float x_calibrated = 0.0;
float y_calibrated = 0.0;

const float vFriction = 3.2;
volatile float v1Filt = 0.0;
volatile float v1Prev = 0.0;
volatile float v2Filt = 0.0;
volatile float v2Prev = 0.0;

float Varm = 0.0;
int pos = 0;
long prevT = 0;
int posPrev = 0;
volatile int pos_i = 0;

float eprev = 0;
float Veleintegral =0;
int Vel_integrator_en = 0;
float TargetVel = 0;

float magprev = 0;
float Magintegral = 0;
float MagePrev = 0;

void setup(void) {
  // put your setup code here, to run once:
Serial.begin(115200);
while (!Serial) delay(10);
cal_sensor();
Serial.println("Cal_sensor Finished");Serial.print("\t");
initMotorPins();
Serial.println("Motor Pins Enabled");Serial.print("\t");
initPWMtimer2();
Serial.println("PWM Pins Enabled");Serial.print("\t");

attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
}
void initMotorPins(void)
{
  // Serial.println("In motor pin init");
  pinMode(INA2,OUTPUT);
  pinMode(INA1,OUTPUT);
  pinMode(PWM,OUTPUT);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
}

void initPWMtimer2(void)
{
  //-----------------------------------------------------------------
  // Use Timer 2 for direct motor drive PWM generation.
  // Prescale = 1, FAST PWM, 8-bit (Mode 3) -> 62.5 kHz PWM
  // Output pins OC2B (d3~) and OC2A (d11~) driven by counter hardware.
  cli();
  TCCR2B = 0;
  TCCR2A = 0;
  TCCR2B =  (0 << WGM22); // start FAST PWM mode 3 setup
  TCCR2A =  (1 << WGM21) | (1 << WGM20); // finish FAST PWM setup
  TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20); // clock prescale = 1
  TCCR2A |= (1 << COM2A1) | (0 << COM2A0); // OCR2A pin (d11~) noninverting PWM
  OCR2A = 1;
  sei();
}
void cal_sensor(void)
{
  if (! lis3mdl.begin_I2C()) 
  {          // hardware I2C mode, can pass in address & alt Wire
    Serial.println("Failed to find LIS3MDL chip");
    while (1) 
    {
      delay(10);
    }
  }
//lis3mdl.setPerformanceMode(LIS3MDL_ULTRAHIGHMODE);
lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
lis3mdl.setDataRate(LIS3MDL_DATARATE_1000_HZ);
Serial.print("Data rate set to: ");Serial.print("\t");
  switch (lis3mdl.getDataRate()) {
    case LIS3MDL_DATARATE_155_HZ: Serial.println("155 Hz");Serial.print("\t"); break;
    case LIS3MDL_DATARATE_300_HZ: Serial.println("300 Hz"); break;
    case LIS3MDL_DATARATE_560_HZ: Serial.println("560 Hz"); break;
    case LIS3MDL_DATARATE_1000_HZ: Serial.println("1000 Hz"); break;
  }

lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
lis3mdl.setIntThreshold(500);
lis3mdl.configInterrupt(false, false, false, // enable z axis
                        false, // polarity
                        false, // don't latch
                        false); // enabled!
Serial.println("Magnetic Sensor settings set");
delay(1000);
//Stores values in RAM for filling calibration values
  volatile float cal_max_x = -800.0;
  volatile float cal_min_x = 800.0;
  volatile float cal_max_y = -800.0;
  volatile float cal_min_y = 800.0;
  volatile float x = 0.0;
  volatile float y = 0.0;
  Serial.println("Calibration Starting");Serial.print("\t");
  for (int i = 0; i < 360; i++)
  {
  //  Serial.println(i);Serial.print("\t");
    Serial.println(" "); Serial.print(i);
    lis3mdl.read();
    y = lis3mdl.y;
    x = lis3mdl.z;
    if (cal_max_y < y)
    {
      cal_max_y = y;
    }
    if (cal_min_y > y)
    {
      cal_min_y = y;
    }
    if (cal_max_x < x)
    {
      cal_max_x = x;
    }
    if (cal_min_x > x)
    {
      cal_min_x = x;
    }
    delay(25);
    Serial.print(" y="); Serial.print(y);Serial.print(" x="); Serial.print(x);
  }
  //Stores values from RAM into registers to be used to calculate heading
  min_x = cal_min_x;
  max_x = cal_max_x;
  min_y = cal_min_y;
  max_y = cal_max_y;
  //delay(20);
  Serial.println("Hard Iron Settings Stored");Serial.print("\t");
  
}
void loop() {  
//-------------------Get timestep--------------------------
long currT = micros();
float deltaT = ((float)(currT-prevT))/1.0e6;
prevT = currT;
//--------------------Get Heading--------------------------
lis3mdl.read();
heading = get_heading(lis3mdl.z, lis3mdl.y); 
//--------------------Filter Heading-----------------------
headinglp = heading*0.2 + headinglp*0.8;
//-------------------Heading Control-----------------------
float Magkp = 1.5;
float Magki = 1.0;
float Magkd = 0;
int target_heading = 180; //In degrees 
//Error in Heading
int Mage = target_heading - headinglp;
int MageAcc = signof(Mage) * Mage * Mage;
//Heading Integral setup
//Integrator Clamp
if(TargetVel >= 800 && ((MageAcc < 0 && TargetVel < 0) || (MageAcc > 0 && TargetVel > 0))){
  Magintegral = 0;
}
else
{
  Magintegral = Magintegral + MageAcc*deltaT;  
}
//Heading Deriative setup
float Magdedt = (MageAcc - MagePrev)/(deltaT);
MagePrev = MageAcc;
//Calculating Target Velocity from Heading Error 
TargetVel = Magkp*MageAcc + Magki*Magintegral + Magkd*Magdedt;//PID controller
//---------------Get Velocity(Encoder counts)-------------
pos = pos_i;
float velocity1 =(pos - posPrev)/deltaT;
posPrev = pos;
//--------------Convert encoder counts to RPM-------------
float v1 = velocity1/116.4*60;
//---------Filter Velocity in RPM to 25 hz cut off---------
v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
v1Prev =v1;
//-----------------Velocity Control------------------------
float Velkp = 0.06;
float Velki = 0.008;
//Velocity error Calculation
int Vele = TargetVel - v1Filt; //Error between target velocity and actual velocity
float control_signal = Velkp*Vele + Velki*Veleintegral;//PI controller
//Velocity Integral Setup
//Integrator Clamp
if((control_signal > 5) && ((Vele < 0 && control_signal < 0) || (Vele > 0 && control_signal > 0))){
  Veleintegral = 0;
}
else
{
  Veleintegral = Veleintegral + Vele*deltaT; 
}
eprev = Vele;
//Calculating Varm from Velocity Error 
//float vFF = vFriction * signof(Vele);
//----------------Motor Plant Model----------------------
//Feedforward for more precise control 
float vFF = 0;
float Varm = vFF + control_signal;
 
//float Varm = 2.8;
//constrain to not blow the motor
Varm=constrain(Varm,-8,8);

motorVolts(Varm);
Serial.print(target_heading);
Serial.print(" ");
Serial.print(headinglp);
Serial.print(" ");
Serial.print(Mage);
Serial.print(" ");
Serial.print(Varm);
Serial.print(" ");
Serial.print(TargetVel);
Serial.print(" ");
Serial.print(v1Filt);
Serial.println();
delay(1);
}

void readEncoder()
{
  int b=digitalRead(ENCB);
  int increment = 0;
  if(b>0){
    increment = 1;
  }
  else{
    increment = -1;
  } 
  pos_i = pos_i + increment;
}
void motorVolts(float volts)
{
    int pwm_command = (int)(volts * PWM_PER_VOLT);

  if (pwm_command < 0) { // negative case -- set direction CW
    pwm_command = - int(pwm_command);
    digitalWrite(INA2, LOW);
    digitalWrite(INA1, HIGH);  
    OCR2A = constrain(pwm_command, 0, 255); //Serial.println(OCR2A);
  }
  else
  { //positive case -- set direction CCW
    pwm_command = int(pwm_command);
    digitalWrite(INA2, HIGH);
    digitalWrite(INA1, LOW);   
    OCR2A = constrain(pwm_command, 0, 255); //Serial.println(OCR2B);
  }
}
float get_heading(float x, float y)
{
  //Serial.println("Get heading");
  float x1 = (min_x + max_x)/2;  //x + min_x;
  float y1 = (min_y + max_y)/2;  //y + min_y;
  float x_full_range = max_x - min_x;
  float y_full_range = max_y - min_y;
  x_calibrated = (x-x1)/ x_full_range;
  y_calibrated = (y-y1)/ y_full_range;
  float angle = atan2(y_calibrated, x_calibrated) * (180.0 / 3.141592654);
  return (angle > 0) ? angle : 360 + angle;
}
