#define MIC A3
#define LDR A2
#define LED 1

int curRecord = 0; 
int preRecord = 0; 
boolean lightTurnOn = false;

void setup() {
  pinMode(LED,OUTPUT);
  delay(100);
  preRecord = analogRead(MIC);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkLightUp();
  while(lightTurnOn)
  {
    if(checkBlowLevel())
    {
      analogWrite(LED,0);
      lightTurnOn = false;
      break;  
    }
  }
  delay(5);
 
}

void checkLightUp()
{
  int LDR_value = analogRead(LDR);
  
 for(int i = 0 ; i < 5; i++)
 {
  LDR_value += analogRead(LDR);
 }
 
 LDR_value = LDR_value/5; 

 if(LDR_value < 200)
 {
    lightTurnOn = true;
 }
}

boolean checkBlowLevel()
{
  curRecord = analogRead(MIC);
  if(abs(curRecord - preRecord) > 200) //if blow strength is strong, turn of the flame
  {
    delay(random(100));
    for(int i = 255; i > 0; i -= 20)
    {
      delay(random(5));
      analogWrite(LED,i);  
    }
    curRecord = preRecord;
    return true;
  }
  else if(abs(curRecord - preRecord) > 5) // if blow strength is not strong to blow off, flicker hard
  {
    int flicker = map(curRecord,0,1023,0,255);
    analogWrite(LED,flicker/random(75));  
    preRecord = curRecord;
  }
  else // if blow level is very less randomly blink the led for flicker effect
  {
    analogWrite(LED,random(100)+135);  
  }
  return false;
}
