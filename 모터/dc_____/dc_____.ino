int moterPin = 6;
int pushBtn = 8;
int Led[3] = {3,4,5};
int i, stat, tmp = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(moterPin, OUTPUT);
pinMode(pushBtn, INPUT);

for(i=0;i<3;i++)
{
  pinMode(Led[i], OUTPUT);
}

}

void loop() {
  // put your main code here, to run repeatedly:
delay(100);
while (digitalRead(pushBtn))
  stat = HIGH;

if(stat==HIGH){
  tmp++;
  stat = LOW;
}

tmp %= 4;
  
switch(tmp)
{
  case 0:
    for(i=0;i<3;i++)
    {
      digitalWrite(Led[i], LOW);
    }
    analogWrite(moterPin, 0);
    break;
  case 1:
    digitalWrite(Led[0], HIGH);
    analogWrite(moterPin,85);
    break;
  case 2:
    digitalWrite(Led[0], LOW);
    digitalWrite(Led[1], HIGH);
    analogWrite(moterPin,170);
    break;
  case 3:
    digitalWrite(Led[1], LOW);
    digitalWrite(Led[2], HIGH);
    analogWrite(moterPin, 255);
    break;
  }
}
