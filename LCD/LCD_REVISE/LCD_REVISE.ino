#include <SimpleTimer.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
#include <Wire.h>

//SimpleTimer timer;
//Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define MODE3_MENU_NOW_TEMP 1
#define MODE3_MENU_SET_TEMP -1

const int btnUp = 4;
const int btnDown = 5;
const int mode3_Btn = 8;

int mode3_BtnStat = 1;
float setTemp = 17.0;
float nowTemp = 20.0;

int Mode3MenuStat = -1;

int a = 0;
int completed = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(mode3_Btn,INPUT);
  pinMode(btnUp, INPUT);
  pinMode(btnDown, INPUT);
  lcd.init();
  lcd. backlight();
  Hello_select_menu();

 // timer.setInterval(1000, Temp_value);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 // timer.run();

  if(digitalRead(mode3_Btn) == LOW)
  {
    delay(30);
    intro();  
    Mode3MenuStat *= -1;
    
    while(digitalRead(mode3_Btn) == LOW);
    delay(30);
  }

  if(Mode3MenuStat == MODE3_MENU_NOW_TEMP)//모드 상태가 현재 온도 출력일 때
  {
     if(completed>0)
     {
       Setup_completed();
     }
    Current_temp();
  }
  
  if(a>0 && Mode3MenuStat == MODE3_MENU_SET_TEMP)//모드 상태가 설정 온도 출력 일 때
  {
    Set_temp();
    if(digitalRead(btnUp) == LOW)
    {
      delay(30);
      setTemp++;

      while(digitalRead(btnUp) == LOW);
      delay(30);
    }
    if(digitalRead(btnDown) == LOW)
    {
      delay(30);
      setTemp--;

      while(digitalRead(btnDown) == LOW);
      delay(30);
    }
    completed++;
  }
}

void Hello_select_menu()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello!");
  lcd.setCursor(0,1);
  lcd.print("please wait...");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("================");
  lcd.setCursor(0,1);
  lcd.print("Select the mode!");
}
void intro()
{
    a++;
    if(a==1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("================");
      lcd.setCursor(0,1);
      lcd.print("This is mode 3.");
      delay(1000);
      lcd.clear();
    }  
   
}
void Set_temp()   //설정 온도 출력
{
    lcd.setCursor(0,0);
    lcd.print("Setting Temp...");
    lcd.setCursor(1,1);
    lcd.print(setTemp);
    Serial.println(setTemp);
}

void Current_temp() //현재 온도 출력
{
 // MsTimer2::stop();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current Temp");
  lcd.setCursor(1,1);
  lcd.print(nowTemp);
  
}

void Setup_completed()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Setup completed!");
  delay(1000);
  completed = 0;
}

/*void Temp_value()
{
    nowTemp = mlx.readObjectTempC();
}*/

