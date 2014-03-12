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
//int temp_c; int temp_f; 
int year0; int month0; int day0; int hour0; int minute0; int second0; 
int maintemp1=100  ,maintemp2=0,temp;
int temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0,temp7=0,temp8=0,temp9=0,temp10=0;
int temp11=0,temp12=0,temp13=0,temp14=0,temp15=0,temp16=0,temp17=0,temp18=0,temp19=0,temp20=0;
int tempreal,num1,num2,num3,num4,num5;


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
    lcd.setCursor(0,1);lcd.print(" Time");lcd.print(bb);lcd.print(":");lcd.print(a);lcd.print("m ");lcd.print("Temp");lcd.print(maintemp1);lcd.print("C ");
    display_time();check();
    if(bb == hour0 && a == minute0)
    { digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW); aa=0; }
  }
  
    while( aa == 2)
  {
    digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);
    DateTime now = rtc.now(); hour0 = now.hour();minute0 = now.minute();
    lcd.setCursor(0,1);lcd.print(" Time");lcd.print(hh);lcd.print(":");lcd.print(mm);lcd.print("m ");lcd.print("Temp");lcd.print(maintemp1);lcd.print("C ");
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
  if(tempreal <= maintemp1 )
  {
    digitalWrite(solid1,HIGH);
  }
  if(tempreal >= maintemp2)
  {
    digitalWrite(solid1,LOW);
  }  
}
///////////////////////////////////  Display  /////////////////////////////////////////////////////////
void display_time()
{
  calculus();//temp_f = thermocouple.measure(TEMPF);
  lcd.setCursor(4, 2);
  lcd.print(" Temperature = ");lcd.print(tempreal);lcd.print("C ");
  //lcd.print(" & ");lcd.print("T:");lcd.print(temp_f);lcd.print(" F ");
  
  DateTime now = rtc.now();
  lcd.setCursor(7, 3);
  lcd.print("Time: ");lcd.print(now.hour(), DEC);lcd.print(':');lcd.print(now.minute(), DEC);lcd.print(':');lcd.print(now.second(), DEC);
  DateTime future (now.unixtime() + 7 * 86400L + 30);
}
///////////////////////////////////  Calculus /////////////////////////////////////////////////////////
void calculus()
{
  calculus1();
  num1 = temp;
  calculus1();
  num2 = temp;
  calculus1();
  num3 = temp;
  calculus1();
  num4 = temp;
  calculus1();
  num5 = temp;
  
  tempreal = (num1+num2+num3+num4+num5)/5;
  
}


void calculus1()
{
  temp1 = thermocouple.measure(TEMPC);  temp2 = thermocouple.measure(TEMPC);delay(10);  
  temp3 = thermocouple.measure(TEMPC);  temp4 = thermocouple.measure(TEMPC);delay(10);
  temp5 = thermocouple.measure(TEMPC);  temp6 = thermocouple.measure(TEMPC);delay(10);
  temp7 = thermocouple.measure(TEMPC);  temp8 = thermocouple.measure(TEMPC);delay(10);
  temp9 = thermocouple.measure(TEMPC);  temp10 = thermocouple.measure(TEMPC);delay(10);
  temp11 = thermocouple.measure(TEMPC); temp12 = thermocouple.measure(TEMPC);delay(10);  
  temp13 = thermocouple.measure(TEMPC); temp14 = thermocouple.measure(TEMPC);delay(10);
  temp15 = thermocouple.measure(TEMPC); temp16 = thermocouple.measure(TEMPC);delay(10);
  temp17 = thermocouple.measure(TEMPC); temp18 = thermocouple.measure(TEMPC);delay(10);
  temp19 = thermocouple.measure(TEMPC); temp20 = thermocouple.measure(TEMPC);delay(10);
  
  if(temp1<=temp2 &&  temp1<=temp3 && temp1<=temp4 && temp1<=temp5 && temp1<=temp6 && temp1<=temp7 && temp1<=temp8 && temp1<=temp9 && temp1<=temp10 && temp1<=temp11 && temp1<=temp12 && temp1<=temp13 && temp1<=temp14 && temp1<=temp15 && temp1<=temp16 && temp1<=temp17 && temp1<=temp18 && temp1<=temp19 && temp1<=temp20 )
  { temp = temp1; }
  if(temp2<=temp1 &&  temp2<=temp3 && temp2<=temp4 && temp2<=temp5 && temp2<=temp6 && temp2<=temp7 && temp2<=temp8 && temp2<=temp9 && temp2<=temp10 && temp2<=temp11 && temp2<=temp12 && temp2<=temp13 && temp2<=temp14 && temp2<=temp15 && temp2<=temp16 && temp2<=temp17 && temp2<=temp18 && temp2<=temp19 && temp2<=temp20)
  { temp = temp2; }
  if(temp3<=temp1 &&  temp3<=temp2 && temp3<=temp4 && temp3<=temp5 && temp3<=temp6 && temp3<=temp7 && temp3<=temp8 && temp3<=temp9 && temp3<=temp10 && temp3<=temp11 && temp3<=temp12 && temp3<=temp13 && temp3<=temp14 && temp3<=temp15 && temp3<=temp16 && temp3<=temp17 && temp3<=temp18 && temp3<=temp19 && temp3<=temp20)
  { temp = temp3; }
  if(temp4<=temp1 &&  temp4<=temp2 && temp4<=temp3 && temp4<=temp5 && temp4<=temp6 && temp4<=temp7 && temp4<=temp8 && temp4<=temp9 && temp4<=temp10 && temp4<=temp11 && temp4<=temp12 && temp4<=temp13 && temp4<=temp14 && temp4<=temp15 && temp4<=temp16 && temp4<=temp17 && temp4<=temp18 && temp4<=temp19 && temp4<=temp20)
  { temp = temp4; }
  if(temp5<=temp1 &&  temp5<=temp2 && temp5<=temp3 && temp5<=temp4 && temp5<=temp6 && temp5<=temp7 && temp5<=temp8 && temp5<=temp9 && temp5<=temp10 && temp5<=temp11 && temp5<=temp12 && temp5<=temp13 && temp5<=temp14 && temp5<=temp15 && temp5<=temp16 && temp5<=temp17 && temp5<=temp18 && temp5<=temp19 && temp5<=temp20)
  { temp = temp5; }
  if(temp6<=temp1 &&  temp6<=temp2 && temp6<=temp3 && temp6<=temp4 && temp6<=temp5 && temp6<=temp7 && temp6<=temp8 && temp6<=temp9 && temp6<=temp10 && temp6<=temp11 && temp6<=temp12 && temp6<=temp13 && temp6<=temp14 && temp6<=temp15 && temp6<=temp16 && temp6<=temp17 && temp6<=temp18 && temp6<=temp19 && temp6<=temp20)
  { temp = temp6; }
  if(temp7<=temp1 &&  temp7<=temp2 && temp7<=temp3 && temp7<=temp4 && temp7<=temp5 && temp7<=temp6 && temp7<=temp8 && temp7<=temp9 && temp7<=temp10 && temp7<=temp11 && temp7<=temp12 && temp7<=temp13 && temp7<=temp14 && temp7<=temp15 && temp7<=temp16 && temp7<=temp17 && temp7<=temp18 && temp7<=temp19 && temp7<=temp20)
  { temp = temp7; }
  if(temp8<=temp1 &&  temp8<=temp2 && temp8<=temp3 && temp8<=temp4 && temp8<=temp5 && temp8<=temp6 && temp8<=temp7 && temp8<=temp9 && temp8<=temp10 && temp8<=temp11 && temp8<=temp12 && temp8<=temp13 && temp8<=temp14 && temp8<=temp15 && temp8<=temp16 && temp8<=temp17 && temp8<=temp18 && temp8<=temp19 && temp8<=temp20)
  { temp = temp8; }
  if(temp9<=temp1 &&  temp9<=temp2 && temp9<=temp3 && temp9<=temp4 && temp9<=temp5 && temp9<=temp6 && temp9<=temp7 && temp9<=temp8 && temp6<=temp10 && temp9<=temp11 && temp9<=temp12 && temp9<=temp13 && temp9<=temp14 && temp9<=temp15 && temp9<=temp16 && temp9<=temp17 && temp9<=temp18 && temp9<=temp19 && temp9<=temp20)
  { temp = temp9; }
  if(temp10<=temp1 &&  temp10<=temp2 && temp10<=temp3 && temp10<=temp4 && temp10<=temp5 && temp10<=temp6 && temp10<=temp7 && temp10<=temp8 && temp10<=temp9 && temp10<=temp11 && temp10<=temp12 && temp10<=temp13 && temp10<=temp14 && temp10<=temp15 && temp10<=temp16 && temp10<=temp17 && temp10<=temp18 && temp10<=temp19 && temp10<=temp20)
  { temp = temp10; }
  
  if(temp11<=temp1 && temp11<=temp2 &&  temp11<=temp3 && temp11<=temp4 && temp11<=temp5 && temp11<=temp6 && temp11<=temp7 && temp11<=temp8 && temp11<=temp9 && temp11<=temp10 && temp11<=temp12 && temp11<=temp13 && temp11<=temp14 && temp11<=temp15 && temp11<=temp16 && temp11<=temp17 && temp11<=temp18 && temp11<=temp19 && temp11<=temp20 )
  { temp = temp11; }
  if(temp12<=temp1 &&  temp12<=temp2 &&  temp12<=temp3 && temp12<=temp4 && temp12<=temp5 && temp12<=temp6 && temp12<=temp7 && temp12<=temp8 && temp12<=temp9 && temp12<=temp10 && temp12<=temp11 && temp12<=temp13 && temp12<=temp14 && temp12<=temp15 && temp12<=temp16 && temp12<=temp17 && temp12<=temp18 && temp12<=temp19 && temp12<=temp20)
  { temp = temp12; }
  if(temp13<=temp1 &&  temp13<=temp2  &&  temp13<=temp3 && temp13<=temp4 && temp13<=temp5 && temp13<=temp6 && temp13<=temp7 && temp13<=temp8 && temp13<=temp9 && temp13<=temp10 && temp13<=temp11 && temp13<=temp12 && temp13<=temp14 && temp13<=temp15 && temp13<=temp16 && temp13<=temp17 && temp13<=temp18 && temp13<=temp19 && temp13<=temp20)
  { temp = temp13; }
  if(temp14<=temp1 &&  temp14<=temp2 && temp14<=temp3 && temp14<=temp4 && temp14<=temp5 && temp14<=temp6 && temp14<=temp7 && temp14<=temp8 && temp14<=temp9 && temp14<=temp10 && temp14<=temp11 && temp14<=temp12 && temp14<=temp13 && temp14<=temp15 && temp14<=temp16 && temp14<=temp17 && temp14<=temp18 && temp14<=temp19 && temp14<=temp20)
  { temp = temp14; }
  if(temp15<=temp1 &&  temp15<=temp2 && temp15<=temp3 && temp15<=temp4 && temp15<=temp5 && temp15<=temp6 && temp15<=temp7 && temp15<=temp8 && temp15<=temp9 && temp15<=temp10 && temp15<=temp11 && temp15<=temp12 && temp15<=temp13 && temp15<=temp14 && temp15<=temp16 && temp15<=temp17 && temp15<=temp18 && temp15<=temp19 && temp15<=temp20)
  { temp = temp15; }
  if(temp16<=temp1 &&  temp16<=temp2 && temp16<=temp3 && temp16<=temp4 && temp16<=temp5 && temp16<=temp6 && temp16<=temp7 && temp16<=temp8 && temp16<=temp9 && temp16<=temp10 && temp16<=temp11 && temp16<=temp12 && temp16<=temp13 && temp16<=temp14 && temp16<=temp15 && temp16<=temp17 && temp16<=temp18 && temp16<=temp19 && temp16<=temp20)
  { temp = temp16; }
  if(temp17<=temp1 &&  temp17<=temp2 && temp17<=temp3 && temp17<=temp4 && temp17<=temp5 && temp17<=temp6 && temp17<=temp7 && temp17<=temp8 && temp17<=temp9 && temp17<=temp10 && temp17<=temp11 && temp17<=temp12 && temp17<=temp13 && temp17<=temp14 && temp17<=temp15 && temp17<=temp16 && temp17<=temp18 && temp17<=temp19 && temp17<=temp20)
  { temp = temp17; }
  if(temp18<=temp1 &&  temp18<=temp2 && temp18<=temp3 && temp18<=temp4 && temp18<=temp5 && temp18<=temp6 && temp18<=temp7 && temp18<=temp8 && temp18<=temp9 && temp18<=temp10 && temp18<=temp11 && temp18<=temp12 && temp18<=temp13 && temp18<=temp14 && temp18<=temp15 && temp18<=temp16 && temp18<=temp17 && temp18<=temp19 && temp18<=temp20)
  { temp = temp18; }
  if(temp19<=temp1 &&  temp19<=temp2 && temp19<=temp3 && temp19<=temp4 && temp19<=temp5 && temp19<=temp6 && temp19<=temp7 && temp19<=temp8 && temp19<=temp9 && temp19<=temp10 && temp19<=temp11 && temp19<=temp12 && temp19<=temp13 && temp19<=temp14 && temp19<=temp15 && temp19<=temp16 && temp19<=temp17 && temp19<=temp18 && temp19<=temp20)
  { temp = temp19; }
  if(temp20<=temp1 &&  temp20<=temp2 && temp20<=temp3 && temp20<=temp4 && temp20<=temp5 && temp20<=temp6 && temp20<=temp7 && temp20<=temp8 && temp20<=temp9 && temp20<=temp10 && temp20<=temp11 && temp20<=temp12 && temp20<=temp13 && temp20<=temp14 && temp20<=temp15 && temp20<=temp16 && temp20<=temp17 && temp20<=temp18 && temp20<=temp19)
  { temp = temp20; }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
