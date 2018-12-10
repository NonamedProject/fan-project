#include <Adafruit_MLX90614.h>
#include <Wire.h>
#include <Servo.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo myservo;

//핀
int Trig = 2;
int Echo = 3;
int Motor = 4;
int ServoBtn = 5;
int PowerBtn = 6;
int RecoBtn = 7;
int TempBtn = 8;
int OnoffBtn = 9;
int Led[3] = {10,11,12};

//변수
int i;
int PowerValue = 0;
int PowerTemp = 0;
int PowerStat = 0;
int OnoffStat = 0;
int RecoStat = 0;
int ServoTemp = 0;
int ServoStat = 0;
int TempStat = 0;

void power()
{
    PowerTemp++;
    PowerTemp %= 4;

    switch(PowerTemp)
    {
      case 0:
        for(i=0;i<3;i++) digitalWrite(Led[i],LOW);
        PowerValue = 0;
        break;
      case 1:
        digitalWrite(Led[0] ,HIGH);
        PowerValue = 85;
        break;
      case 2:
        digitalWrite(Led[0] ,LOW);
        digitalWrite(Led[1] ,HIGH);
        PowerValue = 170;
        break;
      case 3:
        digitalWrite(Led[1] ,LOW);
        digitalWrite(Led[2] ,HIGH);
        PowerValue = 255;
        break;
    }
    Serial.print(PowerValue);
    Serial.println(" power");
}

int reco()
{
  digitalWrite(Trig,LOW);
  digitalWrite(Echo,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Echo,HIGH);

  unsigned long duration = pulseIn(Echo, HIGH);
  float distance = ((float)(340 * duration) / 10000) /2;

  if(distance <=200 || distance >= 2700) 
    analogWrite(Motor,PowerValue);
  else
  {
    delay(2000);
    if(distance <=200 || distance >= 2700) 
      analogWrite(Motor,PowerValue);
    digitalWrite(Motor,LOW);
  }
  if(digitalRead(RecoBtn) == HIGH)
    return 0;
  Serial.print(distance);
  Serial.println(" recomode");
}

int temp()
{
  if(digitalRead(TempBtn) == HIGH)
    return 0;
}

void servo()
{
  for(i=ServoTemp; i<=180 ; i++)
  {
    myservo.write(i);
    if(digitalRead(ServoBtn) == HIGH)
     {
      ServoTemp = i;
      break;
     }
     Serial.print(i);
     Serial.println(" servo");
   }
   for(i = 180;i>=0;i--)
   {
    myservo.write(i);
    if(digitalRead(ServoBtn) == HIGH)
     {
      ServoTemp = i;
      break;
     }
    Serial.print(i);
    Serial.println(" servo");
   }
}
void setup() {
  Serial.begin(115200); //debug용

  //pin 세팅
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(Motor,OUTPUT);
  pinMode(ServoBtn,INPUT);
  pinMode(PowerBtn,INPUT);
  pinMode(RecoBtn,INPUT);
  pinMode(TempBtn,INPUT);
  pinMode(OnoffBtn,INPUT);
  for(i=0;i<3;i++) pinMode(Led[i],OUTPUT);
  
  //temp
  mlx.begin();

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
    //Power
    while(digitalRead(PowerBtn))
      PowerStat = HIGH;
    if(PowerStat == HIGH)
    {
      PowerStat = LOW;
      power();
    }
    analogWrite(Motor,PowerValue);
    
    //reco
    while(digitalRead(RecoBtn))
      RecoStat == HIGH;
    if(RecoStat == HIGH)
    {
      TempStat = LOW;
      RecoStat = LOW;
      reco();
    }

    //temp
    while(digitalRead(TempBtn))
      TempStat == HIGH;
    if(TempStat == HIGH)
    {
      RecoStat = LOW;
      TempStat = LOW;
      temp();
    }
    
    //servo
    while(digitalRead(ServoBtn))
      ServoStat == HIGH;
    if(ServoStat == HIGH)
      servo();
  }
}
