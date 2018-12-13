//#include <Adafruit_MLX90614.h>
//#include <Wire.h>
#include <Servo.h>

//Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo myservo;

//핀
int Motor = 4;
int Mode1Btn = 5;
int Mode2Btn = 6;
int Mode3Btn = 7;
int OnoffBtn = 10;

//변수
int i;
int OnoffStat = 0;
int Mode1Stat = 0;
int Mode2Stat = 0;
int Mode3Stat = 0;
int ServoTemp = 0;

void mode1()
{
  for(i=ServoTemp; i<=360 ; i++)
  {
    myservo.write(i);
    if(digitalRead(Mode1Btn) == HIGH)
     {
      ServoTemp = i;
      break;
     }
     Serial.print(i);
     Serial.println(" servo");
   }
   for(i = 360;i>=0;i--)
   {
    myservo.write(i);
    if(digitalRead(Mode1Btn) == HIGH)
     {
      ServoTemp = i;
      break;
     }
    Serial.print(i);
    Serial.println(" servo");
   }
}

void mode2()
{
  
}

void setup() {
  Serial.begin(115200); //debug용

  //pin 세팅
  pinMode(Motor,OUTPUT);
  pinMode(OnoffBtn,INPUT);
  pinMode(Mode1Btn,INPUT);
  pinMode(Mode2Btn,INPUT);
  pinMode(Mode3Btn,INPUT);
  
  //servo
  myservo.attach(A0);
}

void loop() {
  while(digitalRead(OnoffBtn))
  {
    if (OnoffStat == 1) OnoffStat = 0;
    else OnoffStat = 1;
  }
  
  while(OnoffStat)
  {
    //mode1
    while(digitalRead(Mode1Btn))
    {
      if(Mode1Stat == 1) Mode1Stat = 0;
      else Mode1Stat = 1;
    }
    while(Mode1Stat)
      mode1();
    
    //reco(mode2)
    while(digitalRead(Mode2Btn))
    {
      if(Mode2Stat == 1) Mode2Stat = 0;
      else Mode2Stat = 1;
    }
    while(Mode2Stat)
      mode2();

  }
}
