 /*******************************************************************************
  ฟังก์ชั่นแสดงผลค่าอุณหภูมิและเวลาปัจจุบัน
 *******************************************************************************/
 ///////////////////////////////////  Display  /////////////////////////////////////////////////////////
    void display_time()
    {
      temp = thermocouple.measure(TEMPC);    
      lcd.setCursor(4, 2);
      lcd.print(" Temperature = ");
      lcd.print(temp);
      lcd.print("C ");
      
      ds1307();
      lcd.setCursor(7, 3);
      lcd.print("Time: ");
      lcd.print(hour0);
      lcd.print(':');
      lcd.print(minute0);
      lcd.print(':');
      lcd.print(second0);
    }
