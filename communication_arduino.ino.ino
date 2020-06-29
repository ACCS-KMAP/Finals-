double valuesAccX_1 = 0; double valuesAccY_1 = 0; double valuesAccZ_1 = 0;
double valuesGyX_1 = 0; double valuesGyY_1 = 0; double valuesGyZ_1 = 0;

double valuesAccX_2 = 0; double valuesAccY_2 = 0; double valuesAccZ_2 = 0;
double valuesGyX_2 = 0; double valuesGyY_2 = 0; double valuesGyZ_2 = 0;


double AccX = 0; double AccY = 0; double AccZ = 0;
double GyX = 0; double GyY = 0; double GyZ = 0;


double averageAccX = 0;  double averageAccY = 0;  double averageAccZ = 0;
double averageGyX = 0;   double averageGyY = 0;   double averageGyZ = 0;


int totalValues = 0;


String values;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    int i=0;
    if(Serial.available()>0)
    {
      values = Serial.readStringUntil('$');
      AccX = values[i] - '0';
      AccY = values[i+1] - '0';
      AccZ = values[i+2] - '0';
      GyX = values[i+3] - '0';
      GyY = values[i+4] - '0';
      GyZ = values[i+5] - '0';
    }
}
