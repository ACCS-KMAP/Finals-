#include <Wire.h>
// #include "main.h"     //TODO  (Did we lose this?) (I hope just the variables)


double valuesAccX_1 = 0; double valuesAccY_1 = 0; double valuesAccZ_1 = 0;
double valuesGyX_1 = 0; double valuesGyY_1 = 0; double valuesGyZ_1 = 0;

double valuesAccX_2 = 0; double valuesAccY_2 = 0; double valuesAccZ_2 = 0;
double valuesGyX_2 = 0; double valuesGyY_2 = 0; double valuesGyZ_2 = 0;


double AccX = 0; double AccY = 0; double AccZ = 0;
double GyX = 0; double GyY = 0; double GyZ = 0;


double averageAccX = 0;  double averageAccY = 0;  double averageAccZ = 0;
double averageGyX = 0;   double averageGyY = 0;   double averageGyZ = 0;


int totalValues = 0;
/*
void i2c_init()
{
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
}
void timer1_init()
{
    // set up timer with prescaler = 8
    TCCR1B |= (1 << CS11);
    TCNT1 = 45536; //10ms
    //TCNT1 = 51536; //7ms
    //TCNT1 = 57536; //4ms
    // enable overflow interrupt
    TIMSK1 |= (1 << TOIE1);
    sei();
}
*/
void setup() 
{
  
  //i2c_init();
  //timer1_init();
  //pinMode(LED_pin,OUTPUT);
  Serial.begin(9600);
  //calculate_IMU_error(); // Call this function if you need to get the IMU error values for your module
 
}

/*
void read_accel()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / ACCEL_SCALE_2G ; // X-axis value                           ////// Read from CSV Here 
  AccY = (Wire.read() << 8 | Wire.read()) / ACCEL_SCALE_2G ; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / ACCEL_SCALE_2G ; // Z-axis value
  //rms_a=pow((pow(AccX,2)+pow(AccY,2)+pow(AccZ,2)),0.5);
}

void read_gyro()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); 
  GyX = (Wire.read() << 8 | Wire.read()) / GYRO_SCALE_250; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyY = (Wire.read() << 8 | Wire.read()) / GYRO_SCALE_250;
  GyZ = (Wire.read() << 8 | Wire.read()) / GYRO_SCALE_250;    ////// Read from CSV Here  
}

*/
void print_all()
{
  Serial.print("AX: ");
  Serial.print(AccX);
  Serial.print("\tAY: ");
  Serial.print(AccY);
  Serial.print("\tAZ: ");
  Serial.print(AccZ);

  Serial.print("\tGX: ");
  Serial.print(GyX);
  Serial.print("\tGY: ");
  Serial.print(GyY);
  Serial.print("\tGZ: ");
  Serial.println(GyZ);
}

void column_avg()
{
  averageAccX = (valuesAccX_1 + valuesAccX_2)/ totalValues;  //15 values + 15 values ek saath average lenge
  averageAccY = (valuesAccY_1 + valuesAccY_2)/ totalValues; 
  averageAccZ = (valuesAccZ_1 + valuesAccZ_2)/ totalValues; 

  averageGyX = (valuesGyX_1 + valuesGyX_2) / totalValues; 
  averageGyY = (valuesGyY_1 + valuesGyY_2) / totalValues; 
  averageGyZ = (valuesGyZ_1 + valuesGyZ_2) / totalValues; 
  
}
void reset_values()
{
  valuesAccX_2 = valuesAccX_1; valuesAccY_2 = valuesAccY_1 ; valuesAccZ_2 = valuesAccZ_1;
  valuesGyX_2 = valuesGyX_1; valuesGyY_2 = valuesGyY_1; valuesGyZ_2 = valuesGyZ_1;
  
  valuesAccX_1 = 0; valuesAccY_1 = 0; valuesAccZ_1 = 0;
  valuesGyX_1 = 0; valuesGyY_1 = 0; valuesGyZ_1 = 0;
  
  totalValues = 15;   //15 values have been cleared
  //calculate_flag = 1;
}

void handle_data()
{
  valuesAccX_1 += AccX; valuesAccY_1 += AccY; valuesAccZ_1 += AccZ;
  valuesGyX_1 += GyX;   valuesGyZ_1 += GyZ;   valuesGyZ_1 += GyZ; 
  totalValues++;
}


void predict()
{ 
  double a =  1.793448955856741 ;
  double b =  -2.2175591848784673 ;
  double c =  0.13261748920926242 ;
  double d =  0.00044467518841145984 ;
  double e =  0.005613919363039376 ;
  double f =  0.04211877060872497 ;
  double intercept =  0.48888174909240767 ;
  double z = a*averageAccX + b*averageAccY + c*averageAccZ + d*averageGyX + e*averageGyY + f*averageGyZ + intercept;
  double prediction = 1/(1+exp(-z));
  
  //Serial.print("z = ");Serial.print(z);Serial.print("\t");
  // Serial.print("prediction = ");Serial.println(prediction);
  double LRThreshold = 0.5;
  if(prediction>LRThreshold) inflate_airbags();
}
/*
ISR(TIMER1_OVF_vect)
{
  TCNT1 = 45536;  //10ms
  //TCNT1 = 51536; //7ms
  //TCNT1 = 57536; //4ms
  calculate_flag=0;
  n++;
}
*/
void inflate_airbags()
{
  //digitalWrite(LED_pin,HIGH);
}

void task_scheduler()
{
  //while(calculate_flag == 1) //calculate_flag becomes 0 after 10ms //Write an ISR for this.   /// If we ensure 15 values in 250ms we can say while(totalValues < 30)
  while(totalValues < 30)
  {
    //TODO 
    // preferably combine both the below functions into a single read_csv function. Easier for you 
    //read_accel();           // Read a value and store in AccX,AccY,AccZ  
    //read_gyro();            // Read a value and store in GyX,GyY,GyZ 
    handle_data();         
  }

  //if(time difference from previous prediction is 0.25s i.e 250ms ()) /// If we ensure 15 values in 250ms we can say if(totalValues == 30)
  if(totalValues == 30)
  {
    column_avg();
    predict();
    reset_values();
  }
}

void loop() 
{
  task_scheduler();
  //print_all();
}
