#include<lpc21xx.h>
 #include"header.h"
 #define Green_led (1<<19)
  #define Red_led (1<<20)
  #define BUZZER (1<<21)
  #define PIR_SENSOR ((IOPIN0>>15)&1)

 void pir_Sensor(void)	
  {
  IODIR0|= Green_led | Red_led | BUZZER;
 
  if(PIR_SENSOR == 1)
  {		
   uart0_tx_string("Motion Status : CLEAR\r\n");
   uart0_tx_string("Security : NORMAL \r\n") ;

   IOCLR0=Green_led;
   IOSET0=Red_led;
  // IOCLR0=BUZZER;

   lcd_cmd(0x01);
   lcd_cmd(0x80);
   lcd_string("Field: Safe");
   lcd_cmd(0xC0);
   lcd_string("NO Motion");
}
 else
 {
 uart0_tx_string("Motion status: DETECTED\r\n");
 uart0_tx_string("Security: ALERT\r\n");
  
  IOCLR0=Red_led;
  IOSET0=Green_led;
//  IOSET0=BUZZER;

   lcd_cmd(0x01);
   lcd_cmd(0x80);
   lcd_string("Motion found");
   lcd_cmd(0xC0);
   lcd_string("check field");


}  

  uart0_tx_string("------------------------------------------\r\n");
  delay_ms(100);
  

}
