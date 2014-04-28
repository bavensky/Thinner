/*******************************************************************************
 * Project  : Distiller thinner                                                *
 * Compiler : Arduino 1.0.2                                                    *
 * Board    : Arduino UNO                                                      *
 * Shield   : [DFROBOT] Arduino LCD Keypad Shield                              *
 * Module   : Solidstate relay x 2  relay x 1                                  *
 *          : RealTimeClock Module                                             *
 *          : CD4050 and thermocouple type K                                   *
 * Author   : Bavensky :3                                                      *
 * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
 * Date     : 28/04/2557 [dd/mm/yyyy]                                          *
 *******************************************************************************/
 /*******************************************************************************
 * เรียกใช้งานไลบรารี่ต่างๆ                                                          *
 *******************************************************************************/
    #include <LiquidCrystal.h>
    #include <AD595.h>
    #include <Wire.h>
    #include "RTClib.h"
 /*******************************************************************************
 * กำหนดตัวแปรใช้งาน                                                              *
 *******************************************************************************/    
    LiquidCrystal lcd(13,11,10,12,9,8);
    RTC_DS1307 rtc;
    AD595 thermocouple;
///////////////////////////////////////////////////////////////////////////////////////////
    int button1 = 7;        int button2 = 6;  
    int button3 = 4;        int button4 = 5;
    int Manual1 = 3;        int Manual2 = 2;  
    int Manual3 = 1;        int Manual4 = 0;
    int buttonstate1 = 0;   int buttonstate2 = 0; 
    int buttonstate3 = 0;   int buttonstate4 = 0; 
    int Manualstate1 = 0;   int Manualstate2 = 0; 
    int Manualstate3 = 0;   int Manualstate4 = 0; 
    
    int solid1 = A1;        int solid2 = A2;         int relay = A3;
////////////////////////////////////////////////////////////////////////////////////////////
    int time = 30; 
    int i=0,  u=0,  f=0,  y=0,  t=0,  a=0,  aa=0,  bb=0;
    int h=0,  hh=0,  m=0,  mm=0,  t1 = 0,  m1 = 0,  g=0;
    int year0,month0,day0;   int hour0,minute0,second0; 
    int maintemp1=100  ,maintemp2=0,  temp,  temp1;
////////////////////////////////////////////////////////////////////////////////////////////

    void setup()
    {
      Wire.begin();rtc.begin();thermocouple.init(0);
      if(! rtc.isrunning()){rtc.adjust(DateTime(__DATE__,__TIME__));}
      /*solid1 mean hearter  ||   solid2 mean pump    ||   relay mean fan    */
      pinMode(solid1, OUTPUT); pinMode(solid2, OUTPUT); pinMode(relay, OUTPUT);
      
      /*   8 button    */
      pinMode(button1, INPUT);pinMode(button2, INPUT);
      pinMode(button3, INPUT);pinMode(button4, INPUT);
      pinMode(Manual1, INPUT);pinMode(Manual2, INPUT);
      pinMode(Manual3, INPUT);pinMode(Manual4, INPUT);
      
      /*    Start display     */
      lcd.begin(16,4);lcd.print("  Distiller thinner ");delay(2000);
      lcd.setCursor(0, 1);lcd.print("    Please Choose   ");
    }

//////////////////////////////////////////// Loop Start //////////////////////////////////////////////////////
    void loop()
    {
      f=0;
      
      
      
      lcd.setCursor(0, 1);lcd.print("    Please Choose   ");
      display_time();
      
   /////////////////////////////////////  Switch Set  /////////////////////////////////////////////////////// 
   /////////////////////////////////////  Automatic Mode  /////////////////////////////////////////////////////// 
      buttonstate1 = digitalRead(button1);
      if(buttonstate1 == LOW)
      {
        lcd.setCursor(0,1);lcd.print("      Automatic       ");
        int tt1 = 1; int mm1 = 0;
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
          display_time();
          
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
          display_time();
      
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
        display_time();
        if(bb == hour0 && a == minute0)
        { digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW); aa=0; }
      }
      
        while( aa == 2)
      {
        digitalWrite(solid2,HIGH);digitalWrite(relay,HIGH);
        DateTime now = rtc.now(); hour0 = now.hour();minute0 = now.minute();
        lcd.setCursor(0,1);lcd.print(" Time");lcd.print(hh);lcd.print(":");lcd.print(mm);lcd.print("m ");lcd.print("Temp");lcd.print(maintemp1);lcd.print("C ");
        display_time();
        if(hh == hour0 && mm == minute0)
        { digitalWrite(solid1,LOW);digitalWrite(solid2,LOW);digitalWrite(relay,LOW); aa=0; }
      }
      
       lcd.setCursor(0,1);lcd.print("       Finish         ");delay(3000);
       f=2;
      }
    }
///////////////////////////////////  Display  /////////////////////////////////////////////////////////
    void display_time()
    {
      temp = thermocouple.measure(TEMPC);
      lcd.setCursor(4, 2);
      lcd.print(" Temperature = ");lcd.print(temp);lcd.print("C ");
      
      DateTime now = rtc.now();
      lcd.setCursor(7, 3);
      lcd.print("Time: ");lcd.print(hour0);lcd.print(':');lcd.print(minute0);lcd.print(':');lcd.print(second0);
      DateTime future (now.unixtime() + 7 * 86400L + 30);
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
