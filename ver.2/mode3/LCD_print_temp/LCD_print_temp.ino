#include <LiquidCrystal_I2C.h>

const int btnUp = 2;      //화살표 윗방향
const int btnDown = 4;    //화살표 아래방향
const int mode_2Btn = 7;

int mode_2Stat;      
int mode_2Menu = 1;
int num = 1;
       
int btnUpStat;            //화살표 윗방향 상태
int btnDownStat;          //화살표 아래방향 상태
float setTemp = 17.0;         //설정 온도

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
lcd.init();         //lcd 초기화
lcd.backlight();    //백라이트 켜기
lcd.clear();        //lcd 글자 모두 지우기


lcd.setCursor(0,0); //0행 0열로 커서 이동
lcd.print("Setting");

lcd.setCursor(0,1);//0행 1열로 커서 이동
lcd.print("MODE IS ...");

pinMode(mode_2Btn,INPUT);
pinMode(btnUp, INPUT);
pinMode(btnDown, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(mode_2Btn) == HIGH)
  {
    delay(30);
    mode_2Menu *= -1;
    Serial.println("asdf");
    while(digitalRead(mode_2Btn) == HIGH); // 스위치를 누르면 깜빡거리는 버그를 없애줌      
    delay(30);
  }
  
    if(mode_2Menu == -1)   //현재 온도 출력
    {
      Current_temp();
    }

    if(mode_2Menu == 1)   //온도 설정 모드
    {
      Set_temp();
      if(digitalRead(btnUp) == HIGH) // 7번 핀이 LOW 일 때, 버튼을 눌렀을 때
      {
       delay(30); // delay함수를 통해 처음 버튼을 눌렀을 때 생기는 잡신호들을 무시
       setTemp++;   //설정 온도 +1
       
      while(digitalRead(btnUp) == HIGH); // 스위치를 누르면 깜빡거리는 버그를 없애줌      
      delay(30);
      
      }
  
      if(digitalRead(btnDown)==HIGH) // 7번 핀이 LOW 일 때, 버튼을 눌렀을 때
     {
       delay(30); // delay함수를 통해 처음 버튼을 눌렀을 때 생기는 잡신호들을 무시
       setTemp--;    //설정 온도 -1

      while(digitalRead(btnDown) == HIGH); // 스위치를 누르면 깜빡거리는 버그를 없애줌      
      delay(30);
       }
    }
}

void Set_temp()   //설정 온도 출력
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Setting Temp...");
    lcd.setCursor(0,1);
    lcd.print(setTemp);

}

void Current_temp() //현재 온도 출력
{
 // MsTimer2::stop();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current Temp");
  lcd.setCursor(0,1);
  lcd.print("17.3");


}



