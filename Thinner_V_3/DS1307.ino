 /*******************************************************************************
 * ฟังก์ชั่นใช้งาน Real Time Clock (RTC)                                             
 * วัน              เดือน            ปี                                            
 * day0            month0          year0                                        
 *                                                                              
 * ชั่วโมง           นาที             วินาที                                          
 * hour0           minute0         second0  
 *******************************************************************************/
 
  void  ds1307()
  {
    DateTime now = rtc.now(); 
    year0 = now.year(); month0 = now.month();   day0 = now.day();
    hour0 = now.hour(); minute0 = now.minute(); second0 = now.second();
    DateTime future (now.unixtime() + 7 * 86400L + 30);
  }
     
