int turnOff = 3;
int up = 4;
int down = 5;
int mode1 = 6;
int mode2 = 7;
int rotation = 8;

void setup()
{
  Serial.begin(115200);
  pinMode(turnOff, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(mode1, INPUT_PULLUP);
  pinMode(mode2, INPUT_PULLUP);
  pinMode(rotation, INPUT_PULLUP);
}
 
void loop()
{
  if (digitalRead(turnOff) == LOW)
        Serial.print("1");
        
  if (digitalRead(up) == LOW)
        Serial.print("1");
        
  if (digitalRead(down) == LOW)
        Serial.print("1");
        
  if (digitalRead(mode1) == LOW)
        Serial.print("1");
        
  if (digitalRead(mode2) == LOW)
        Serial.print("1");
        
  if (digitalRead(rotation) == LOW)
        Serial.print("1");
}
