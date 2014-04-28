 /*******************************************************************************
 * ฟังก์ชั่นใช้งาน Real Time Clock (RTC)                                             
 * วัน              เดือน            ปี                                            
 * day0            month0          year0                                        
 *                                                                              
 * ชั่วโมง           นาที             วินาที                                          
 * hour0           minute0         second0  
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
