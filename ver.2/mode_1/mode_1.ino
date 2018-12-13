#include<Servo.h>

Servo myservo;

//핀
int motor = 8;

//변수
int i;
int servoTemp = 0;

int servo()
{
  for(i = servoTemp; i<= 180; i++)
  {
    myservo.write(i);
    if() //button이 눌리면
    {
      servoTemp = i;
      return 0
    }
  }
  for(i = 180; i>=0; i++)
  {
    myservo.write(i);
    if() //button이 눌리면
    {
      servoTemp = i;
      return 0;
    }
  
}

void setup() {
  pinMode(motor,OUTPUT);
  myservo.attach(A0);
  // put your setup code here, to run once:


}

void loop() {
  // put your main code here, to run repeatedly:

}
