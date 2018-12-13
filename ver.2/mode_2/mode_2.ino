#include<Servo.h>

Servo myservo;

//핀
int echo1 = 2;
int echo2 = 4;
int echo3 = 6;
int trig1 = 3;
int trig2 = 5;
int trig3 = 7;
int motor = 8;

//변수
int reco1;
int reco2;
int reco3;
int i;

void reco()
{
  /*get distance*/
  //reco1
  digitalWrite(trig1,LOW);
  digitalWrite(echo1,LOW);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);
  delayMicroseconds(10);
  digitalWrite(echo1,HIGH);

  unsigned long duration1 = pulseIn(echo1, HIGH);
  float distance1 = ((float)(340 * duration1) / 10000) / 2;

  //reco2
  digitalWrite(trig2,LOW);
  digitalWrite(echo2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(10);
  digitalWrite(echo2,HIGH);

  unsigned long duration2 = pulseIn(echo2, HIGH);
  float distance2 = ((float)(340 * duration2) / 10000) / 2;
  
  //reco3
  digitalWrite(trig3,LOW);
  digitalWrite(echo3,LOW);
  delayMicroseconds(2);
  digitalWrite(trig3,HIGH);
  delayMicroseconds(10);
  digitalWrite(echo3,HIGH);

  unsigned long duration3 = pulseIn(echo3, HIGH);
  float distance3 = ((float)(340 * duration3) / 10000) / 2;

  /*get recognition*/
  //reco1
  if(distance1 <= 200 || distance1 >=2700) 
    reco1 = 1;
  else 
    reco1 = 0; 

  //reco2
  if(distance2 <= 200 || distance2 >=2700) 
    reco2 = 1;
  else 
    reco2 = 0;

  //reco3
  if(distance3 <= 200 || distance3 >=2700) 
    reco3 = 1;
  else 
    reco3 = 0;
}

void recoservo()
{
  //1 recognition
  if(reco1 == 1)
    myservo.write(0);
  else if(reco2 == 1)
    myservo.write(90);
  else if(reco3 == 1)
    myservo.write(180);
  
  //2 recognition
  if(reco1 == 1 && reco2 == 1)
  {
    for(i = 0 ; i <= 90 ; i++)
      myservo.attach(i);
    delay(3000);
    for(i = 90 ; i >= 0 ; i--)
      myservo.attach(i);
    delay(3000);
  }
  if(reco1 == 1 && reco3 == 1)
  {
    for(i = 0 ; i <= 180 ; i++)
      myservo.attach(i);
    delay(3000);
    for(i = 180 ; i >= 0 ; i--)
      myservo.attach(i);
    delay(3000);
  }
  if(reco2 == 1 && reco3 == 1)
  {
    for(i = 90 ; i <= 180 ; i++)
      myservo.attach(i);
    delay(3000);
    for(i = 180 ; i >= 90; i--)
      myservo.attach(i);
    delay(3000);
  }
  
  //3 recognition
  if(reco1 == 1 && reco2 == 1 && reco3 == 1)
  {
    for(i = 0 ; i <= 90 ; i++)
      myservo.attach(i);
    delay(3000);
    for(i = 90 ; i<= 180; i++)
      myservo.attach(i);
    delay(3000);
    for(i = 180 ; i >= 90; i--)
      myservo.attach(i);
    delay(3000);
    for(i = 90 ; i >= 0; i--)
      myservo.attach(i);
    delay(3000);
  }

 // no recognition
 if(reco1 == 0 && reco2 == 0 && reco3 == 0)
 {
  analogWrite(motor, 0);
 }
}

void setup() {
  Serial.begin(115200);
  myservo.attach(A0);

  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);
  pinMode(echo3,INPUT);
  pinMode(trig1,OUTPUT);
  pinMode(trig2,OUTPUT);
  pinMode(trig3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  reco();
  recoservo();

  
}
