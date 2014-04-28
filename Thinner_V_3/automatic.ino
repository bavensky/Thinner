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
        if(hh < 23 || mm < 59)
          {  aa=2;  }
          
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
        lcd.print(bb);
        lcd.print(":");
        lcd.print(a);
        lcd.print("m ");
        
        if(bb == hour0 && a == minute0)
        { 
          aa=0; 
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
        lcd.print(hh);
        lcd.print(":");
        lcd.print(mm);
        lcd.print("m ");
        
        if(hh == hour0 && mm == minute0)
        {
          digitalWrite(solid1,LOW);
          digitalWrite(solid2,LOW);
          digitalWrite(relay,LOW); 
          aa=0; 
        }
      }
                                  
       lcd.setCursor(0,1);lcd.print("       Delay          ");delay(2000);
       f=2;
      }
      
      
      
      while(f==2)
      {
        digitalWrite(solid1,LOW);
        delay(20000);
        digitalWrite(solid1,HIGH);
        
        
        buttonstate1 = digitalRead(button1);
        if(buttonstate1 == LOW)
          {
          lcd.setCursor(0,1);lcd.print("      Automatic       ");
          int tt1 = 1; int mm1 = 0;
          h = hour0; m = minute0;
          hh = h+tt1; mm = m+mm1; 
          automatic();
          }
      }
    }
