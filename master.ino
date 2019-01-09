#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

//핀
int onoffBtn = 3;
int upBtn = 4;
int downBtn = 5;
int mode_1Btn = 6;
int mode_2Btn = 7;
int mode_3Btn = 8;

//변수
int onoffStat = 1;
int mode_1Stat = 1;
int mode_2Stat = 1;
int mode_3Stat = 1;
float setTemp;
float curTemp;
int cnt = 0;
int mode_3Menu = 1;

//함수
void Set_temp() //설정 온도 출력
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Setting Temp...")
  lcd.setCursor(0,1);
  lcd.print(setTemp);
}

void Current_temp() //현재 온도 출력
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current Temp");
  lcd.setCursor(0,1);
  lcd.print(curTemp);
}

void Lcd_setting()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void Current_power()  //현재 파워 출력
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current power");
    lcd.setCursor(0,1);
    lcd.print(cnt);
}

void setup() 
{
  Serial.begin(115200);
  pinMode(onoffBtn, INPUT);
  pinMode(upBtn, INPUT);
  pinMode(downBtn, INPUT);
  pinMode(mode_1Btn, INPUT);
  pinMode(mode_2Btn, INPUT);
  pinMode(mode_3Btn, INPUT);

  Lcd_setting();
}

void loop() 
{
  if(Serial.available())
    curTemp = (float)Serial.read();
  
  if(digitalRead(onoffBtn) == HIGH) //onoff버튼이 눌렸을때
  {
    if(onoffStat == 1)
    {
      Serial.print('n');  //킨다
      onoffStat = 0;  
    }
    else
    {
      Serial.print('f');  //끈다
      onoffStat = 1;
    }
  }

  if(digitalRead(mode_1Btn) == HIGH)  //mode1버튼이 눌렸을때
  {
      Serial.print('1');
      mode_1Stat = 1;
      mode_2Stat = 0;
      mode_3Stat = 0;
  }

  
  if(digitalRead(mode_2Btn) == HIGH)  //mode1버튼이 눌렸을때
  {
      Serial.print('2');
      mode_1Stat = 0;
      mode_2Stat = 1;
      mode_3Stat = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Current mode");
      lcd.setCursor(0,1);
      lcd.print("mode2");
  }

  
  if(digitalRead(mode_3Btn) == HIGH)  //mode1버튼이 눌렸을때
  {
      Serial.print('3');
      mode_1Stat = 1;
      mode_2Stat = 0;
      mode_3Stat = 0;
  }

  if(mode_1Stat)  //모드1일때
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current mode");
    lcd.setCursor(0,1);
    lcd.print("mode1");
    
    if(digitalRead(upBtn) == HIGH) //up버튼이 눌렸을때
    {
      Serial.print('4');
      if(cnt<3) //파워숫자 증가
        cnt++;
      Current_power();
      delay(3000);
    }

    if(digitalRead(downBtn) == HIGH) //down버튼이 눌렸을때
    {
      Serial.print('5');
      if(cnt>1) //파워숫자 감소
        cnt--;
      Current_power();
      delay(3000);
    }
  }

  if(mode_3Stat)  //모드3일때
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current mode");
    lcd.setCursor(0,1);
    lcd.print("mode1");
    
    if(digitalRead(mode_3Btn) == HIGH)
      mode_3Menu *= -1;
    
    if(mode_3Menu == -1)
      Current_temp();
    if(mode_3Menu == 1)
    {
      Set_temp();
      if(digitalRead(upBtn) == HIGH)
      {
        setTemp++;
        Serial.print('6');
      }
      if(digitalRead(downBtn) == HIGH)
      {
        setTemp--;
        Serial.print('7');
      }
    }
  }
}
