 /*******************************************************************************
 โหมดการตั้งค่าอุณหภูมิ                                                                  
 *******************************************************************************/
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
       }
    }
