void setup() 
{
  pinMode(2,OUTPUT); //trig
  pinMode(3,INPUT); //echo
  pinMode(4,OUTPUT); //motor
  Serial.begin(115200);
}

void loop() 
{
  digitalWrite(2,0);
  digitalWrite(3,0);
  delayMicroseconds(2);
  digitalWrite(2,1);
  delayMicroseconds(10);
  digitalWrite(3,1);

   unsigned long duration = pulseIn(3, HIGH);
   float distance = ((float)(340 * duration) / 10000) / 2; 

   Serial.println(distance);
   delay(500);

   if(distance <= 200 || distance >=2700) digitalWrite(4,1);
   else digitalWrite(4,0);
}
