 /*******************************************************************************
  โหมดการทำงานอัตโนมัติ
  ทำงานครั้งแรก ๑ ชั่วโมง ครั้งถัดไป ครึ่งชั่วโมง 
  เปิดการใช้งานฮีตเตอร์ ปั๊มน้ำ พัดลม ตลอดเวลา                                         
  หยุดการทำงานโดนการกดปุ่มเดิม ( button1 )                                                                    
 *******************************************************************************/
 /////////////////////////////////// Automatic  /////////////////////////////////
    void automatic()
    {
      f=1;
      while(f == 1)
      {
       aa = 0;     
       /*** not over ***/
       if(hh < 23 || mm < 59)
       {  
         aa=2;
       }
       
       /***  over  ***/   
       if(hh > 23 || mm > 59)
       {
         if(hh > 23){ bb = hh - 24;} 
         if(mm > 59){ a = mm - 60; bb = hh + 1;}
         aa = 1;
       }
    
      while(aa == 1)
      {
        digitalWrite(solid1,HIGH);
        digitalWrite(solid2,HIGH);
        digitalWrite(relay,HIGH);
        
        ds1307(); 
        lcd.setCursor(0,1);
        lcd.print("  Time");
        lcd.print(hour0);
        lcd.print(":");
        lcd.print(minute0);
        lcd.print("m ");
        
        if(bb == hour0 && a == minute0)
        { 
          digitalWrite(solid1,LOW);
          aa=0; 
        }
        
        buttonstate1 = digitalRead(button1);
        if(buttonstate1 == LOW)
        {
          delay(200);
          f=0;aa=0;
        }
        
      }
      
      while( aa == 2)
      {
        digitalWrite(solid1,HIGH);
        digitalWrite(solid2,HIGH);
        digitalWrite(relay,HIGH);
        
        ds1307();   
        lcd.setCursor(0,1);
        lcd.print(" Time");
        lcd.print(hour0);
        lcd.print(":");
        lcd.print(minute0);
        lcd.print("m ");
        
        if(hh == hour0 && mm == minute0)
        {
          digitalWrite(solid1,LOW); 
          aa=0; 
        }
        
        buttonstate1 = digitalRead(button1);
        if(buttonstate1 == LOW)
        {
          delay(200);
          f=0;aa=0;
        }
      }
                                  
      lcd.setCursor(0,1);lcd.print("       Delay          ");delay(2000);
      f=2;
      }
      
      
      while(f==2)
      {
        digitalWrite(solid1,LOW);
        delay(20000);
        
        h = hour0; m = minute0;
        hh = 0;   mm = 0;
        hh = h+0; mm = m+30;
        
       /*** not over ***/
       if(hh < 23 || mm < 59)
       {  
         t=2;
       }
       
       /***  over  ***/   
       if(hh > 23 || mm > 59)
       {
         if(hh > 23){ bb = hh - 24;} 
         if(mm > 59){ a = mm - 60; bb = hh + 1;}
         t=1;
       }
       
       while(t==1)
       {
        digitalWrite(solid1,HIGH);
        digitalWrite(solid2,HIGH);
        digitalWrite(relay,HIGH);
        
        ds1307();   
        lcd.setCursor(0,1);
        lcd.print(" Time");
        lcd.print(hour0);
        lcd.print(":");
        lcd.print(minute0);
        lcd.print("m ");
        
         if(bb == hour0 && a == minute0)
         { 
           digitalWrite(solid1,LOW);
           t=0; 
         }
         
         buttonstate1 = digitalRead(button1);
         if(buttonstate1 == LOW)
         {
           delay(200);
           f=0;aa=0;t=0;
         }
       }
       
       while(t==2)
       {
         digitalWrite(solid1,HIGH);
         digitalWrite(solid2,HIGH);
         digitalWrite(relay,HIGH);
        
         ds1307();   
         lcd.setCursor(0,1);
         lcd.print(" Time");
         lcd.print(hour0);
         lcd.print(":");
         lcd.print(minute0);
         lcd.print("m ");
        
         if(hh == hour0 && mm == minute0)
         { 
           digitalWrite(solid1,LOW);
           t=0; 
         }
         
         buttonstate1 = digitalRead(button1);
         if(buttonstate1 == LOW)
         {
           delay(200);
           f=0;aa=0;t=0;
         }
       }
      }
    }
