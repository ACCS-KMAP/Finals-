float values[6];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    int i=0;
    if(Serial.available>0)
    {
      values = Serial.readStringUntil('$');
      accX = values[i] - '0';
      accY = values[i+1] - '0';
      accZ = values[i+2] - '0';
      gyroX = values[i+3] - '0';
      gyroY = values[i+4] - '0';
      gyroZ = values[i+5] - '0';
    }
}
