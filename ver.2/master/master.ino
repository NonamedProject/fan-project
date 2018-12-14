#include <Adafruit_MLX90614.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

//핀
int onoffBtn = 3;
int upBtn = 4;
int downBtn = 5;
int mode1Btn = 6;
int mode2Btn = 7;
int mode3Btn = 8;

//변수
int onoffStat;
int mode_1Stat;
int mode_2Stat;
int mode_3Stat;
float setTemp;
float curTemp;
int cnt=0;

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
  lcd.print(temp);
}

void lcdsetting()
{
  lcd.init();         //lcd 초기화
  lcd.backlight();    //백라이트 켜기
  lcd.clear();        //lcd 글자 모두 지우기
}

void setup()
{
  Serial.begin(115200);
  pinMode(onoffBtn, INPUT);
  pinMode(upBtn, INPUT);
  pinMode(downBtn, INPUT);
  pinMode(mode1Btn, INPUT);
  pinMode(mode2Btn, INPUT);
  pinMode(mode3Btn, INPUT);
  pinMode(13,OUTPUT);

  lcdsetting();

  mlx.begin();
}
 
void loop()
{ 
  if(Serial.available())
    temp = (float)Serial.read();
  if (digitalRead(onoffBtn) == HIGH)
  {
    if(onoffStat == 1)
    {
      Serial.print('1');
      onoffStat == 0;
    }
    else
    {
      Serial.print('2');
      onoffStat == 1;
    }
  }
        
  if (digitalRead(upBtn) == HIGH)
  {
    Serial.print('3');
    if(cnt<3)
      cnt++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current power");
    lcd.setCursor(0,1);
    lcd.print(cnt);
    delay(2000);
  }
    
        
  if (digitalRead(downBtn) == HIGH)
  {
    Serial.print('4');
    if(cnt>1)
      cnt--;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current power");
    lcd.setCursor(0,1);
    lcd.print(cnt);
    delay(2000);
  }
        
  if (digitalRead(mode1Btn) ==HIGH)
  {
    if(mode_1Stat == 1)
    {
      Serial.print('5');
      mode_1Stat == 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Current mode");
      lcd.setCursor(0,1);
      lcd.print("mode1");
    }
    else
    {
      Serial.print('6');
      mode_1Stat == 1;
    }
  }
     
  if (digitalRead(mode2Btn) == HIGH)
  {
    if(mode_2Stat == 1)
    {
      Serial.print('7');
      mode_2Stat == 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Current mode");
      lcd.setCursor(0,1);
      lcd.print("mode1");
    }
    else
    {
      Serial.print('8');
      mode_2Stat == 1;
    }
  }

  if (digitalRead(mode3Btn) ==HIGH)
  {
    
    if(mode_3Stat == 1)
    {
      Serial.print('9');
      mode_3Stat == 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Current mode");
      lcd.setCursor(0,1);
      lcd.print("mode1");
    }
    else
    {
      Serial.print('0');
      mode_3Stat == 1;
    }
  }
  while(mode_3Stat)
  {
    if(mode_2Menu == -1)   //현재 온도 출력
    {
      Current_temp();
    }

    if(mode_2Menu == 1)   //온도 설정 모드
    {
      Set_temp();
      if(digitalRead(upBtn) == HIGH) // 7번 핀이 LOW 일 때, 버튼을 눌렀을 때
      {
       delay(30); // delay함수를 통해 처음 버튼을 눌렀을 때 생기는 잡신호들을 무시
       setTemp++;   //설정 온도 +1
       Serial.print('u');
       
      while(digitalRead(upBtn) == HIGH); // 스위치를 누르면 깜빡거리는 버그를 없애줌      
      delay(30);
      }
  
      if(digitalRead(downBtn)==HIGH) // 7번 핀이 LOW 일 때, 버튼을 눌렀을 때
     {
       delay(30); // delay함수를 통해 처음 버튼을 눌렀을 때 생기는 잡신호들을 무시
       setTemp--; //설정 온도 -1
       Serial.print('d');

      while(digitalRead(downBtn) == HIGH); // 스위치를 누르면 깜빡거리는 버그를 없애줌      
      delay(30);
      }
    }
  }
}
