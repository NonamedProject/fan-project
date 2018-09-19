void setup() 
{
  pinMode(3,INPUT);
  Serial.begin(115200);
}

void loop() 
{
  int state = analogRead(A0);
  Serial.println(state);
  delay(1000);

}
