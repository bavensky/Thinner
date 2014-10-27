   /*******************************************************************************
   โหมดการตั้งค่าอุณหภูมิ                                                                  
   *******************************************************************************/
    /////////////////////////////////////  Settemp  ///////////////////////////////////////////////////////
      void settemp()
      {
         delay(200);
         lcd.clear();
         lcd.print("  Distiller thinner "); 
         i=1;
         while(i==1)
         {
           display_time();
           lcd.setCursor(3,1);
           lcd.print("Set Temp : ");
           lcd.print(maintemp1);
    ///////  End set tempurature  ////////////////////////////////////////////////////////////////////////////////
           buttonstate2 = digitalRead(button2);
           if(buttonstate2 == LOW)
           {
             delay(200);
             i=2;
           } 
    ///////  Up tempurature  ////////////////////////////////////////////////////////////////////////////////////
           buttonstate3 = digitalRead(button3);
           if(buttonstate3 == LOW)
           {
             delay(200);
             maintemp1 = maintemp1 + 1;
           }
    ///////  Down tempurature  //////////////////////////////////////////////////////////////////////////////////
           buttonstate4 = digitalRead(button4);
           if(buttonstate4 == LOW)
           {
             delay(200);
             maintemp1 = maintemp1 - 1;
           } 
         }
      }
    /////////////////////////////////////////  END  ////////////////////////////////////////////////////////////
