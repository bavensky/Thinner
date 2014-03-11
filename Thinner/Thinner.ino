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
int time = 30; byte i=0; byte u=0; int f=0; int y=0; int t=0; int a=0; int aa=0; int bb=0;
int h=0; int hh=0; int m=0; int mm=0; int t1 = 0; int m1 = 0; int g=0;
//int temp_c;  
int temp_f; 
int year0; int month0; int day0; int hour0; int minute0; int second0; 
int maintemp1=100  ,maintemp2=0,temp;
int temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0,temp7=0,temp8=0,temp9=0,temp10=0;


////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Wire.begin();rtc.begin();thermocouple.init(0);
  if(! rtc.isrunning()){rtc.adjust(DateTime(__DATE__,__TIME__));}
  
  pinMode(solid1, OUTPUT); pinMode(solid2, OUTPUT); pinMode(relay, OUTPUT);

  pinMode(button1, INPUT);pinMode(button2, INPUT);
  pinMode(button3, INPUT);pinMode(button4, INPUT);
  pinMode(Manual1, INPUT);pinMode(Manual2, INPUT);
  pinMode(Manual3, INPUT);pinMode(Manual4, INPUT);
  
  maintemp2 = maintemp1+5;
  
  lcd.begin(16,4);lcd.print("  Distiller thinner ");delay(2000);
  lcd.setCursor(0, 1);lcd.print("    Please Choose   ");
}

//////////////////////////////////////////// Loop Start //////////////////////////////////////////////////////
void loop()
{
  f=0;
  
  DateTime now = rtc.now(); 
  year0 = now.year(); month0 = now.month();   day0 = now.day();
  hour0 = now.hour(); minute0 = now.minute(); second0 = now.second();
  DateTime future (now.unixtime() + 7 * 86400L + 30);
  
  lcd.setCursor(0, 1);lcd.print("    Please Choose   ");
  display_time();
  
 /////////////////////////////////////  Switch Set  /////////////////////////////////////////////////////// 
 /////////////////////////////////////  Automatic Mode  /////////////////////////////////////////////////////// 
  buttonstate1 = digitalRead(button1);
  if(buttonstate1 == LOW)
  {
    lcd.setCursor(0,1);lcd.print("      Automatic       ");
    int tt1 = 2; int mm1 = 30;
    h = hour0; m = minute0;
    hh = h+tt1; mm = m+mm1; 
    automatic();
  }
 /////////////////////////////////////  Set time and temperature  ///////////////////////////////////////////////////////  
  buttonstate2 = digitalRead(button2);
  if(buttonstate2 == LOW)
  { delay(200);i = 1;}
    
    while(i == 1)
    {
      lcd.setCursor(0,1);lcd.print("Set Time || Set Temp");
      buttonstate3 = digitalRead(button3);
      if(buttonstate3 == LOW)
        { lcd.setCursor(0,1);lcd.print("      Set Time        ");delay(1000);settime();i=0; }
      buttonstate4 = digitalRead(button4);
      if(buttonstate4 == LOW)         
        { lcd.setCursor(0,1);lcd.print("   Set Temperature    ");delay(1000);settemp();i=0; }
    }
/////////////////////////////////////  Hearter on  ///////////////////////////////////////////////////////
  Manualstate1 = digitalRead(Manual1);
  if(Manualstate1 == LOW)
  { delay(200);u=1;}
  
  while(u == 1)
    {                             
      lcd.setCursor(0,1);lcd.print("       Heater       ");
      display_time();check();
      
      Manualstate3 = digitalRead(Manual3);
      if(Manualstate3 == LOW)
      { delay(200);lcd.setCursor(0,1);lcd.print("     END Heater     ");delay(500);digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW);u=0; }
      
      Manualstate2 = digitalRead(Manual2);
      if(Manualstate2 == LOW)                  
      { y=1;}
       while(y == 1) 
      {
        display_time();
        delay(200);lcd.setCursor(0,1);lcd.print("    Pump / Fan      ");digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);   
        Manualstate4 = digitalRead(Manual4);
        if(Manualstate4 == LOW)
        { delay(200);lcd.setCursor(0,1);lcd.print("  Stop Pump / Fan   ");delay(500);digitalWrite(solid2,LOW);digitalWrite(relay,LOW);y=0;}
      }
    } 
/////////////////////////////////////  Pump Fan on  ///////////////////////////////////////////////////////  
  Manualstate2 = digitalRead(Manual2);
  if(Manualstate2 == LOW)
  { delay(200);u=2;}
  
  while(u == 2)
    {
       lcd.setCursor(0,1);lcd.print("    Pump / Fan      ");digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);
       display_time();
       
       Manualstate1 = digitalRead(Manual1);
       if(Manualstate1 == LOW)
       { delay(200);y=1;}
       while(y == 1)
       {                             
          lcd.setCursor(0,1);lcd.print("       Heater       ");
          display_time();check();
      
          Manualstate3 = digitalRead(Manual3);
          if(Manualstate3 == LOW)
          { delay(200);lcd.setCursor(0,1);lcd.print("     END Heater     ");delay(500);digitalWrite(solid1,LOW);delay(1000);y=0; }         
        } 
          
      Manualstate4 = digitalRead(Manual4);
      if(Manualstate4 == LOW)                  
      { delay(200);lcd.setCursor(0,1);lcd.print("  Stop Pump / Fan   ");delay(500);digitalWrite(solid2,LOW);digitalWrite(relay,LOW);delay(1000);u=0; }
    }    
    
    
}///////////////////////////////////// END Loop //////////////////////////////////////////////////////////////


/////////////////////////////////////  Settime  //////////////////////////////////////////////////////////////
void settime()
{
   delay(200);lcd.clear();lcd.print("  Distiller thinner "); i=1;
   while(i==1)
   {
     lcd.setCursor(3,1);lcd.print("Set Time : ");lcd.print(m1);lcd.print("  ");t1 = 0;
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
     lcd.setCursor(3,1);lcd.print("Set Temp : ");lcd.print(maintemp1);
     display_time();
     buttonstate2 = digitalRead(button2);if(buttonstate2 == LOW){i=2;}; 
     buttonstate3 = digitalRead(button3);if(buttonstate3 == LOW){delay(200);maintemp1 = maintemp1 + 1;}; 
     buttonstate4 = digitalRead(button4);if(buttonstate4 == LOW){delay(200);maintemp1 = maintemp1 - 1;}; 
     maintemp2 = maintemp1+5;
   }
}
/////////////////////////////////// Automatic  /////////////////////////////////////////////////////////
void automatic()
{
    f=1;
    while(f == 1)
    {
      aa = 0;      
      if(hh < 23 || mm < 59){aa=2;}
      if(hh > 23 || mm > 59)
      {
        if(hh > 23){ bb = hh - 24;} 
        if(mm > 59){ a = mm - 60; bb = hh + 1;}
        aa = 1;
      }

    while(aa == 1)
  {
    digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);
    DateTime now = rtc.now(); hour0 = now.hour();minute0 = now.minute();
    lcd.setCursor(0,1);lcd.print(" Time");lcd.print(bb);lcd.print(":");lcd.print(a);lcd.print("m ");lcd.print("Temp");lcd.print(temp1);lcd.print("C ");
    display_time();check();
    if(bb == hour0 && a == minute0)
    { digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW); aa=0; }
  }
  
    while( aa == 2)
  {
    digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);
    DateTime now = rtc.now(); hour0 = now.hour();minute0 = now.minute();
    lcd.setCursor(0,1);lcd.print(" Time");lcd.print(hh);lcd.print(":");lcd.print(mm);lcd.print("m ");lcd.print("Temp");lcd.print(temp1);lcd.print("C ");
    display_time();check();
    if(hh == hour0 && mm == minute0)
    { digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW); aa=0; }
  }
  
   lcd.setCursor(0,1);lcd.print("       Finish         ");delay(3000);
   f=2;
  }
}


////////////////////////////////////  Check  ////////////////////////////////////////////////////////
void check()
{
  calculus();
  if(temp <= maintemp1 )
  {
    digitalWrite(solid1,HIGH);
  }
  if(temp >= maintemp2)
  {
    digitalWrite(solid1,LOW);
  }  
}
///////////////////////////////////  Display  /////////////////////////////////////////////////////////
void display_time()
{
  calculus();temp_f = thermocouple.measure(TEMPF);
  lcd.setCursor(6, 2);
  lcd.print("T:");lcd.print(temp);lcd.print(" C ");
  lcd.print(" & ");lcd.print("T:");lcd.print(temp_f);lcd.print(" F ");
  
  DateTime now = rtc.now();
  lcd.setCursor(7, 3);
  lcd.print("Time: ");lcd.print(now.hour(), DEC);lcd.print(':');lcd.print(now.minute(), DEC);lcd.print(':');lcd.print(now.second(), DEC);
  DateTime future (now.unixtime() + 7 * 86400L + 30);
}
///////////////////////////////////  Calculus /////////////////////////////////////////////////////////
void calculus()
{
  temp1 = thermocouple.measure(TEMPC);delay(100);  temp2 = thermocouple.measure(TEMPC);delay(100);  
  temp3 = thermocouple.measure(TEMPC);delay(100);  temp4 = thermocouple.measure(TEMPC);delay(100);
  temp5 = thermocouple.measure(TEMPC);delay(100);  temp6 = thermocouple.measure(TEMPC);delay(100);
  temp7 = thermocouple.measure(TEMPC);delay(100);  temp8 = thermocouple.measure(TEMPC);delay(100);
  temp9 = thermocouple.measure(TEMPC);delay(100);  temp10 = thermocouple.measure(TEMPC);delay(100);
  
  if(temp1<temp2 &&  temp1<temp3 && temp1<temp4 && temp1<temp5 && temp1<temp6 && temp1<temp7 && temp1<temp8 && temp1<temp9 && temp1<temp10 )
  { temp = temp1; }
  if(temp2<temp1 &&  temp2<temp3 && temp2<temp4 && temp2<temp5 && temp2<temp6 && temp2<temp7 && temp2<temp8 && temp2<temp9 && temp2<temp10 )
  { temp = temp2; }
  if(temp3<temp1 &&  temp3<temp2 && temp3<temp4 && temp3<temp5 && temp3<temp6 && temp3<temp7 && temp3<temp8 && temp3<temp9 && temp3<temp10 )
  { temp = temp3; }
  if(temp4<temp1 &&  temp4<temp2 && temp4<temp3 && temp4<temp5 && temp4<temp6 && temp4<temp7 && temp4<temp8 && temp4<temp9 && temp4<temp10 )
  { temp = temp4; }
  if(temp5<temp1 &&  temp5<temp2 && temp5<temp3 && temp5<temp4 && temp5<temp6 && temp5<temp7 && temp5<temp8 && temp5<temp9 && temp5<temp10 )
  { temp = temp5; }
  if(temp6<temp1 &&  temp6<temp2 && temp6<temp3 && temp6<temp4 && temp6<temp5 && temp6<temp7 && temp6<temp8 && temp6<temp9 && temp6<temp10 )
  { temp = temp6; }
  if(temp7<temp1 &&  temp7<temp2 && temp7<temp3 && temp7<temp4 && temp7<temp5 && temp7<temp6 && temp7<temp8 && temp7<temp9 && temp7<temp10 )
  { temp = temp7; }
  if(temp8<temp1 &&  temp8<temp2 && temp8<temp3 && temp8<temp4 && temp8<temp5 && temp8<temp6 && temp8<temp7 && temp8<temp9 && temp8<temp10 )
  { temp = temp8; }
  if(temp9<temp1 &&  temp9<temp2 && temp9<temp3 && temp9<temp4 && temp9<temp5 && temp9<temp6 && temp9<temp7 && temp9<temp8 && temp6<temp10 )
  { temp = temp9; }
  if(temp10<temp1 &&  temp10<temp2 && temp10<temp3 && temp10<temp4 && temp10<temp5 && temp10<temp6 && temp10<temp7 && temp10<temp8 && temp10<temp9 )
  { temp = temp10; }
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

