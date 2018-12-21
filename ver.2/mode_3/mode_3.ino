//변수
int mode_3Stat;      
int mode_3Menu = 1;
       
int btnUpStat;            //화살표 윗방향 상태
int btnDownStat;          //화살표 아래방향 상태
float setTemp = 17.0;     //설정 온도

void temppower()
{
  if(temp<setTemp)
    analogWrite(motor,85);
  else if(temp==setTemp)
    analogWrite(motor,170);
  else if(temp>setTemp)
    analogWrite(motor,255);
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
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current Temp");
  lcd.setCursor(0,1);
  lcd.print("17.3");
}

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  temp = mlx.readAmbientTempC();
  Serial.println(temp);
  if()//만약에 모드버튼이 눌렸으면
  {
    mode_3Menu *= -1;
  }
  if(mode_3Menu == -1)   //현재 온도 출력
  {
    Current_temp();
  }
  if(mode_3Menu == 1)   //온도 설정 모드
  {
    Set_temp();
    if() //업 버튼이 눌리면
    {
      delay(30); // delay함수를 통해 처음 버튼을 눌렀을 때 생기는 잡신호들을 무시
      setTemp++;   //설정 온도 +1
    }  
    if() // 다운 버튼이 눌리면
    {
       delay(30); // delay함수를 통해 처음 버튼을 눌렀을 때 생기는 잡신호들을 무시
       setTemp--;    //설정 온도 -1
    }
  }
}



