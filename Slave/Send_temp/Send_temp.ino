#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SimpleTimer.h>

Simple Timer timer;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float nowTemp();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mlx.begin();
  timer.setInterval(3000, Read_temp);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.run();
  if(nowTemp!=nowTemp)
  {
    Serial.print(nowTemp);
  }
}

void Read_temp()
{
  nowTemp = mlxreadObjectTempC();
}

