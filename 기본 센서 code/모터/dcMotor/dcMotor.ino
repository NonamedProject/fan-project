int moterPin = 6; // 모터 핀 
int pushBtn = 8; // 약, 중, 강 선택 버튼
int Led[3] = {3,4,5}; // 약, 중, 강, 표시 LED, 다 꺼지면 전원 off
int i, stat, tmp = 0; //i == 반복문 제어, stat == 스위치 상태, tmp == 스위치를 몇 번 눌렀는지 확인

void setup() {
  // put your setup code here, to run once:
pinMode(moterPin, OUTPUT); //모터 핀 출력
pinMode(pushBtn, INPUT); //스위치 입력

for(i=0;i<3;i++)
{
  pinMode(Led[i], OUTPUT); //led 출력
}

}

void loop() {
  // put your main code here, to run repeatedly:
delay(100); //  1/10초 기다림
while (digitalRead(pushBtn)) //버튼을 누르면
  stat = HIGH; //stat을 high로 설정

if(stat==HIGH){ 만약 버튼을 누르면
  tmp++; //tmp를 1증가
  stat = LOW; //tmp를 1증가 했으므로 중복되지 않도록 다시 low로 바꿔준다.
}

tmp %= 4;  //tmp를 4로 나눈 나머지를 저장하므로 1(약), 2(중), 3(강)일 때는 값이 그대로 저장되고 4가 되었을 때는 0으로 초기화 시킨다.
  
switch(tmp) 스위치가 몇번눌렀는지에 따라서
{
  case 0: 0번눌렀다면
    for(i=0;i<3;i++)
    {
      digitalWrite(Led[i], LOW); //전원 off
    }
    analogWrite(moterPin, 0); //    0/255만큼 출력
    break;
  case 1: //한 번 눌렀다면
    digitalWrite(Led[0], HIGH); //약 표시
    analogWrite(moterPin,85);  // 85/255만큼 출력
    break;
  case 2:// 두 번 눌렀다면
    digitalWrite(Led[0], LOW);  //약 표시하던 led off
    digitalWrite(Led[1], HIGH); //중 표시
    analogWrite(moterPin,170); // 170/255만큼 출력
    break;
  case 3://세번 눌렀다면
    digitalWrite(Led[1], LOW); //중 표시하던 led off
    digitalWrite(Led[2], HIGH); // 강 표시
    analogWrite(moterPin, 255); // 255/255만큼 출력
    break;
  }
}
