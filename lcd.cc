  #include <Wire.h> 
 #include <LiquidCrystal.h>
  
LiquidCrystal lcd(12,11,5,4,3,2);
  String milliSec; boolean debounce1, debounce2;
  unsigned long btn1PressStart=0, btn2PressStart=0;
  unsigned long Sec, Min, startMillis; int lapNum = 1;
extern volatile unsigned long timer0_millis;

int buttonPushCounter = 0;    // counter for the number of button presses
int up_buttonState = 0;       // current state of the up button
int up_lastButtonState = 0;   // previous state of the up button
bool bPress = false;  
  int switchlapPin=7;
int switchStateLap=0;
int stopwatchMilli=0;//milliseconds
int stopWatchSecond=0;//Second
int stopwatchMinute=0;//MinuteUp_buttonPin
  void setup()
  
  { 
      
       lcd.begin(16,2);
      Serial.begin(9600);
      
    pinMode(7,INPUT);
      
     pinMode( switchlapPin, INPUT_PULLUP);
   //   lcd.setCursor(0,1);
     // lcd.print(" Press to start");
}
void loop()
{
  switchStateLap=digitalRead(switchlapPin);
  if(millis()-btn1PressStart > 500) debounce1 = true;
  if(digitalRead(4) == HIGH && debounce1 == true)
  {
    btn1PressStart = millis();
    debounce1 = false;
    
  }
        
          startMillis = millis();
  while(1)
  {   
            if(millis()-btn1PressStart > 500) debounce1 = true;
            if(digitalRead(4) == HIGH && debounce1 == true)
    {
              btn1PressStart = millis();
              debounce1 = false;
       
              lapNum = 1;
              //btn2PressStart = 0;
              
    }
    //-------------------------------------------------
    if(millis()-btn2PressStart > 500) debounce2 = true;
    if(digitalRead(7) == HIGH && debounce2 == true) 
    {
      btn2PressStart = millis();
      debounce2 = false;

      
    }
    //-------------------------------------------------
          milliSec = String((millis()-startMillis)%1000);
          Sec = ((millis()-startMillis)/1000)%60;
          Min = ((millis()-startMillis)/60000)%60;
    //-------------------------------------------------
          lcd.setCursor(0,1);
          lcd.print("BGN ");
          if(Min < 10)
          {
            lcd.print("0");
            lcd.print(Min);
          }
          else lcd.print(Min);
          lcd.print(":");
          if(Sec < 10)
          {
            lcd.print("0"); 
            lcd.print(Sec);
          }
          else lcd.print(Sec);
          lcd.print(":");
          lcd.print(milliSec[0]); 
          lcd.print(milliSec[1]);
           if ( bPress)
  {
    bPress = false;
   // lcd.setCursor(14, 1);
    //lcd.print("               ");
    lcd.setCursor(14, 1);
    lcd.print(buttonPushCounter);
             noInterrupts ();
timer0_millis = 0;
interrupts ();
  }
switchStateLap=digitalRead(switchlapPin);
if(switchStateLap==LOW){
  lcd.setCursor(0,0);
 lcd.print(" Elasped");
lcd.print(Min);
lcd.print(":");
lcd.print(Sec);
lcd.print(":");
  lcd.print(milliSec);
  

}

  up_buttonState = digitalRead(switchlapPin);
  if (up_buttonState != up_lastButtonState)    // compare the buttonState to its previous state
  {
    if (up_buttonState == LOW)   // if the state has changed, increment the counter
    {
      bPress = true;  // if the current state is HIGH then the button went from off to on:
      
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    }
    else {
      Serial.println("off"); // if the current state is LOW then the button went from on to off:
    }
    //delay(50);  // Delay a little bit to avoid bouncing
  }

  up_lastButtonState = up_buttonState;  
        }
      
      //============================================================
      
      
        String lapMilliSec = milliSec;
        int lapSec = Sec, lapMin = Min;
        //---------------------------------------------
        lcd.setCursor(0,1);
        lcd.print("LP");
        lcd.print(lapNum);
        lapNum++;
        lcd.setCursor(4,1);
        if(Min < 10)
        {
          lcd.print("0"); lcd.print(lapMin);
        }
        else lcd.print(lapMin);
        lcd.print(":");
        if(Sec < 10)
        {
          lcd.print("0"); lcd.print(lapSec);
        }
        else lcd.print(lapSec);
        lcd.print(".");
        lcd.print(lapMilliSec[0]); lcd.print(lapMilliSec[1]);
      }
