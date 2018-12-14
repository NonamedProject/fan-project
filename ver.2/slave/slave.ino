#include<Servo.h>

Servo myservo;

//핀
int echo_1 = 2;
int echo_2 = 4;
int echo_3 = 6;
int trig_1 = 3;
int trig_2 = 5;
int trig_3 = 7;
int motor = 9;

//변수
int reco_1 = 0;
int reco_2 = 0;
int reco_3 = 0;
int i; //반복변수
char data; //시리얼통신
int mode_1Stat;
int mode_2Stat;
int mode_3Stat;
int onoffStat;
int powerStat;
int servoTemp = 0;
float setTemp;
float curTemp;

void reco()
{
  /*get distance*/
  //reco_1
  digitalWrite(trig_1,LOW);
  digitalWrite(echo_1,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_1,HIGH);
  delayMicroseconds(10);
  digitalWrite(echo_1,HIGH);

  unsigned long duration1 = pulseIn(echo_1, HIGH);
  float distance1 = ((float)(340 * duration1) / 10000) / 2;

  //reco_2
  digitalWrite(trig_2,LOW);
  digitalWrite(echo_2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_2,HIGH);
  delayMicroseconds(10);
  digitalWrite(echo_2,HIGH);

  unsigned long duration2 = pulseIn(echo_2, HIGH);
  float distance2 = ((float)(340 * duration2) / 10000) / 2;
  
  //reco_3
  digitalWrite(trig_3,LOW);
  digitalWrite(echo_3,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_3,HIGH);
  delayMicroseconds(10);
  digitalWrite(echo_3,HIGH);

  unsigned long duration3 = pulseIn(echo_3, HIGH);
  float distance3 = ((float)(340 * duration3) / 10000) / 2;

  /*get recognition*/
  //reco_1
  if(distance1 <= 200 || distance1 >=2700) 
    reco_1 = 1;
  else 
    reco_1 = 0; 

  //reco_2
  if(distance2 <= 200 || distance2 >=2700) 
    reco_2 = 1;
  else 
    reco_2 = 0;

  //reco_3
  if(distance3 <= 200 || distance3 >=2700) 
    reco_3 = 1;
  else 
    reco_3 = 0;
}

void recoservo()
{
  //1 recognition
  if(reco_1 == 1)
    myservo.write(0);
  else if(reco_2 == 1)
    myservo.write(90);
  else if(reco_3 == 1)
    myservo.write(180);
  
  //2 recognition
  if(reco_1 == 1 && reco_2 == 1)
  {
    for(i = 0 ; i <= 90 ; i++)
      myservo.write(i);
    delay(3000);
    for(i = 90 ; i >= 0 ; i--)
      myservo.write(i);
    delay(3000);
  }
  if(reco_1 == 1 && reco_3 == 1)
  {
    for(i = 0 ; i <= 180 ; i++)
      myservo.write(i);
    delay(3000);
    for(i = 180 ; i >= 0 ; i--)
      myservo.write(i);
    delay(3000);
  }
  if(reco_2 == 1 && reco_3 == 1)
  {
    for(i = 90 ; i <= 180 ; i++)
      myservo.write(i);
    delay(3000);
    for(i = 180 ; i >= 90; i--)
      myservo.write(i);
    delay(3000);
  }
  
  //3 recognition
  if(reco_1 == 1 && reco_2 == 1 && reco_3 == 1)
  {
    for(i = 0 ; i <= 90 ; i++)
      myservo.write(i);
    delay(3000);
    for(i = 90 ; i<= 180; i++)
      myservo.write(i);
    delay(3000);
    for(i = 180 ; i >= 90; i--)
      myservo.write(i);
    delay(3000);
    for(i = 90 ; i >= 0; i--)
      myservo.write(i);
    delay(3000);
  }

 // no recognition
 if(reco_1 == 0 && reco_2 == 0 && reco_3 == 0)
 {
  analogWrite(motor, 0);
 }
}

int servo()
{
  for(i = servoTemp; i<= 180; i++)
  {
    myservo.write(i);
    if(mode_2Stat == 0) //button이 눌리면
    {
      servoTemp = i;
      return 0;
    }
  }
  for(i = 180; i>=0; i++)
  {
    myservo.write(i);
    if(mode_2Stat) //button이 눌리면
    {
      servoTemp = i;
      return 0;
    }
  }
}

void power()
{
  switch (powerStat)
  {
    case 1:
      analogWrite(motor,85);
    case 2:
      analogWrite(motor,170);
    case 3:
      analogWrite(motor,255); 
  }
}

void temppower()
{
  if(temp<setTemp)
    analogWrite(motor,85);
  else if(temp==setTemp)
    analogWrite(motor,170);
  else if(temp>setTemp)
    analogWrite(motor,255);
}

void setup() {
  Serial.begin(115200);
  myservo.attach(A0);
  pinMode(motor,OUTPUT);
  pinMode(8,OUTPUT);
}

void loop() {
  if(Serial.available())
  {
    data = (char)Serial.read();
    digitalWrite(8,1);
    delay(3000);
    digitalWrite(8,0);
    delay(3000);
    
    if(data == '1') //onoffbtn
      onoffStat = 1;
    else if(data == '2')
      onoffStat = 0;

    if(data == '3') //powerbtn
      powerStat++;
    else if(data == '4')
      powerStat--;
    
    if(data == '5') //mode1btn
    {
      mode_1Stat = 1;
      mode_2Stat = 0;
      mode_3Stat = 0;
    }  
    else if(data == '6')
      mode_1Stat = 0;
    
    if(data == '7') //mode2btn
    {
      mode_1Stat = 0;
      mode_2Stat = 1;
      mode_3Stat = 0;
    } 
    else if(data == '8')
      mode_2Stat = 0;
    
    if(data == '9') //mode3btn
    {
      mode_1Stat = 0;
      mode_2Stat = 0;
      mode_3Stat = 1;
    }
    else if(data == '0')
      mode_3Stat = 0;
    if(data == 'u')
      setTemp++;
    if(data == 'd')
      setTemp--;
  }
  while(onoffStat)
  {
    while(mode_1Stat)
    {
      power();
      servo();
    }
    while(mode_2Stat)
    {
      reco();
      recoservo();
    }
    while(mode_3Stat)
    {
      temp = mlx.readAmbientTempC();
      Serial.print(temp);
      tempPower();
    }
  }
}
