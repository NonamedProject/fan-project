#include <Servo.h>

Servo myservo;
int sw = 5;
int cnt = 0;
int angle = 0;
int tmp = 0;
int i;


void setup()
{
  myservo.attach(A0);
  pinMode(sw, INPUT);
}

void loop()
{
while(1)//루프 돌때마다 변수가 초기화되므로 반복문으로 무한반복
{    
  sw = digitalRead(5);  //5번 포트로 입력을 받는다
  if(sw == 1)
  {
    delay(200);   //debounce 0.2초 대기
    while(sw == 1)    //bounce이후 재확인 스위치가 때어지면 나온다
      sw = digitalRead(5);
    if(sw == 0)
    {
      delay(200);
      sw = digitalRead(5);
      if(sw==0)
      cnt++;
     }
   }

if(digitalRead(sw) == HIGH)
{
  for(i=0; i<=180; i++)
  {
    myservo.write(i);
     
    if(digitalRead(sw) == HIGH)
    {
      tmp = i;
      break;
     }
   }
}
   
if(digitalRead(sw) == HIGH && tmp != 0)
{
  for(i=0; i<=180; i++)
   {
      myservo.write(i);
     
     if(digitalRead(sw) == HIGH)
     {
       tmp = i;
       break;
      }
    }
 }

  }
}       //loop END


/*
 *   if(cnt == 1)
  { 
    delay(200);   
    myservo.write(0);
   }

   if(cnt == 2)
   {
     delay(200);  
     myservo.write(90);
   }

   if(cnt == 3)
   {
     delay(200);
     myservo.write(180);
     cnt = 0;
    }
  }       //while END   
 */

