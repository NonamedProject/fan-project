#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  //mlx모듈을 읽어들이기 시작합니다.
}

void loop() {
  Serial.print("Ambient = "); 
  Serial.print(mlx.readAmbientTempC()); // 주변온도를 읽습니다.
  Serial.print("*C\tObject = "); 
  Serial.print(mlx.readObjectTempC()); Serial.println("*C"); //객체 온도를 읽습니다.
  //아래는 같은것을 화씨로 읽어들입니다.
  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = ");
  Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  delay(500);
}
