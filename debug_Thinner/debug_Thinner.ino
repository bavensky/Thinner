#include <LiquidCrystal.h>
#include <AD595.h>
#include <Wire.h>
#include "RTClib.h"

LiquidCrystal lcd(13,11,10,12,9,8);
RTC_DS1307 rtc;
AD595 thermocouple;
///////////////////////////////////////////////////////////////////////////////////////////
int button1 = 7;  int button2 = 6;  
int button3 = 4; int button4 = 5;
int Manual1 = 3; int Manual2 = 2;  
int Manual3 = 1;  int Manual4 = 0;
int buttonstate1 = 0; int buttonstate2 = 0; 
int buttonstate3 = 0; int buttonstate4 = 0; 
int Manualstate1 = 0; int Manualstate2 = 0; 
int Manualstate3 = 0; int Manualstate4 = 0; 
int solid1 = A1; int solid2 = A2; int relay = A3;
////////////////////////////////////////////////////////////////////////////////////////////
int time = 30; byte i=0; byte u=0; int f=0; int y=0; int t=0; int a=0; int aa=0; int b=0; int bb=0;
int h=0; int hh=0; int m=0; int mm=0; int t1 = 0; int m1 = 0;
int temp_c;  int temp_f;  int tempc;  int tempf;
int temp1=30; int temp2=0; int temp3=0; int temp4=0;
int year0; int month0; int day0; int hour0; int minute0; int second0; 
////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Wire.begin();rtc.begin();thermocouple.init(A0);
  if(! rtc.isrunning()){rtc.adjust(DateTime(__DATE__,__TIME__));}
  
  pinMode(solid1, OUTPUT); pinMode(solid2, OUTPUT); pinMode(relay, OUTPUT);

  pinMode(button1, INPUT);pinMode(button2, INPUT);
  pinMode(button3, INPUT);pinMode(button4, INPUT);
  pinMode(Manual1, INPUT);pinMode(Manual2, INPUT);
  pinMode(Manual3, INPUT);pinMode(Manual4, INPUT);
  
  temp2 = temp1+2;  //Serial.begin(9600);
  
  lcd.begin(16,4);lcd.print("  Distiller thinner ");
  lcd.setCursor(0, 1);lcd.print("    Please Choose   ");delay(2000);
}

void loop()
{
  // Start //
  f=0;
  DateTime now = rtc.now(); 
  year0 = now.year(); month0 = now.month();   day0 = now.day();
  hour0 = now.hour(); minute0 = now.minute(); second0 = now.second();
  DateTime future (now.unixtime() + 7 * 86400L + 30);
  lcd.setCursor(0, 1);lcd.print("    Please Choose   ");
  display_time();delay(300);
  
 /////////////////////////////////////  Switch Set  /////////////////////////////////////////////////////// 
  buttonstate1 = digitalRead(button1);
  if(buttonstate1 == LOW)
  {
    lcd.setCursor(0,1);lcd.print("      Automatic       ");
    int tt1 = 2; int mm1 = 30;
    h = hour0; m = minute0;
    hh = h+tt1; mm = m+mm1; 
    automatic();
  }
 
  buttonstate2 = digitalRead(button2);
  if(buttonstate2 == LOW)
  { delay(200);i = 1;}
    
    while(i == 1)
    {
      lcd.setCursor(0,1);lcd.print("Set Time || Set Temp");
      buttonstate3 = digitalRead(button3);
      if(buttonstate3 == LOW)
        { lcd.setCursor(0,1);lcd.print("      Set Time        ");delay(2000);settime();i=0; }
      buttonstate4 = digitalRead(button4);
      if(buttonstate4 == LOW)         
        { lcd.setCursor(0,1);lcd.print("   Set Temperature    ");delay(2000);settemp();i=0; }
    }
/////////////////////////////////////  Hearter  ///////////////////////////////////////////////////////
  Manualstate1 = digitalRead(Manual1);
  if(Manualstate1 == LOW)
  { delay(200);u=1;}
  
  while(u == 1)
    {                             
      lcd.setCursor(0,1);lcd.print("       Heater       ");
      display_time();check();
      
      Manualstate3 = digitalRead(Manual3);
      if(Manualstate3 == LOW)
      { delay(200);lcd.setCursor(0,1);lcd.print("     END Heater     ");digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW);u=0; }
      
      Manualstate2 = digitalRead(Manual2);
      if(Manualstate2 == LOW)                  
      { delay(200);lcd.setCursor(0,1);lcd.print("    Pump / Fan      ");digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);}
      
      Manualstate4 = digitalRead(Manual4);
      if(Manualstate4 == LOW)
      { delay(200);lcd.setCursor(0,1);lcd.print("  Stop Pump / Fan   ");digitalWrite(solid2,LOW);digitalWrite(relay,LOW);}
    } 
/////////////////////////////////////  Pump Fan  ///////////////////////////////////////////////////////  
  Manualstate2 = digitalRead(Manual2);
  if(Manualstate2 == LOW)
  { delay(200);lcd.setCursor(0,1);lcd.print("    Pump / Fan      ");digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);u=2;}
  
  while(u == 2)
    {
      
       Manualstate1 = digitalRead(Manual1);
       if(Manualstate1 == LOW)
       { delay(200);y=1;}
       while(y == 1)
       {                             
          lcd.setCursor(0,1);lcd.print("       Heater       ");
          display_time();check();
      
          Manualstate3 = digitalRead(Manual3);
          if(Manualstate3 == LOW)
          { delay(200);lcd.setCursor(0,1);lcd.print("     END Heater     ");digitalWrite(solid1,LOW);delay(1000);y=0; }         
        } 
          
      Manualstate4 = digitalRead(Manual4);
      if(Manualstate4 == LOW)                  
      { delay(200);lcd.setCursor(0,1);lcd.print("  Stop Pump / Fan   ");digitalWrite(solid2,LOW);digitalWrite(relay,LOW);delay(1000);u=0; }
    }    
    
    
}// END //
/////////////////////////////////////  Settime  ///////////////////////////////////////////////////////
void settime()
{
   delay(200);lcd.clear();lcd.print("  Distiller thinner "); i=1;
   while(i==1)
   {
     lcd.setCursor(3,1);lcd.print("Set Time : ");lcd.print(m1);t1 = 0;
     display_time();
     buttonstate2 = digitalRead(button2);if(buttonstate2 == LOW){i=2;}; 
     buttonstate3 = digitalRead(button3);if(buttonstate3 == LOW){delay(200);m1 = m1 + 1;}; 
     buttonstate4 = digitalRead(button4);if(buttonstate4 == LOW){delay(200);m1 = m1 - 1;}; 
     h = hour0; m = minute0;
     hh = h+t1; mm = m+m1; 
   }
   automatic(); 
}
/////////////////////////////////////  Settemp  ///////////////////////////////////////////////////////
void settemp()
{
   delay(200);lcd.clear();lcd.print("  Distiller thinner "); i=1;
   while(i==1)
   {
     lcd.setCursor(3,1);lcd.print("Set Temp : ");lcd.print(temp1);
     display_time();
     buttonstate2 = digitalRead(button2);if(buttonstate2 == LOW){i=2;}; 
     buttonstate3 = digitalRead(button3);if(buttonstate3 == LOW){delay(200);temp1 = temp1 + 1;}; 
     buttonstate4 = digitalRead(button4);if(buttonstate4 == LOW){delay(200);temp1 = temp1 - 1;}; 
     temp2 = temp1+2;
   }
}
/////////////////////////////////// Automatic  /////////////////////////////////////////////////////////
void automatic()
{
    f=1;
    while(f == 1)
    {
      aa = 0;digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);
      Serial.println("Start");
      DateTime now = rtc.now(); 
      hour0 = now.hour(); minute0 = now.minute();second0 = now.second();
      DateTime future (now.unixtime() + 7 * 86400L + 30);
    if(hh < 23 || mm < 59){aa=2;}
    if(hh > 23 || mm > 59){
    if(hh > 23){ b = hh - 24;} 
    if(mm > 59){ a = mm - 60; bb = hh + 1;}
    aa = 1;}
 
    while(aa == 1)
  {
    DateTime now = rtc.now(); hour0 = now.hour();minute0 = now.minute();
    lcd.setCursor(0,1);lcd.print("Time ");lcd.print(bb);lcd.print(":");lcd.print(a);lcd.print("m ");lcd.print("Temp ");lcd.print(temp1);lcd.print("C");
    display_time();check();
    if(bb == hour0 && a == minute0)
    { digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW); aa=0; }
  }
  
    while( aa == 2)
  {
    DateTime now = rtc.now(); hour0 = now.hour();minute0 = now.minute();
    lcd.setCursor(0,1);lcd.print("Time ");lcd.print(hh);lcd.print(":");lcd.print(mm);lcd.print("m ");lcd.print("Temp ");lcd.print(temp1);lcd.print("C");
    display_time();check();
    if(hh == hour0 && mm == minute0)
    { digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW); aa=0; }
  }
  
   lcd.setCursor(0,1);lcd.print("       Finish         ");delay(5000);
   f=2;
  }
}
////////////////////////////////////  Check  ////////////////////////////////////////////////////////
void check()
{
  temp_c = thermocouple.measure(TEMPC);
  if(temp_c <= temp1 )
  {
    digitalWrite(solid1,HIGH);
  }
  else if(temp_c >= temp2)
  {
    digitalWrite(solid1,LOW);
  }
  
}
///////////////////////////////////  Display  /////////////////////////////////////////////////////////
void display_time()
{
  temp_c = thermocouple.measure(TEMPC);
  temp_f = thermocouple.measure(TEMPF);
  lcd.setCursor(6, 2);
  lcd.print("T:");lcd.print(temp_c);lcd.print(" C");lcd.print(" & ");
  lcd.print("F:");lcd.print(temp_f);lcd.print(" F  ");
  
  DateTime now = rtc.now();
  lcd.setCursor(7, 3);
  lcd.print("Time: ");lcd.print(now.hour(), DEC);lcd.print(':');lcd.print(now.minute(), DEC);lcd.print(':');lcd.print(now.second(), DEC);
  DateTime future (now.unixtime() + 7 * 86400L + 30);
}
////////////////////////////////////////////////////////////////////////////////////////////
