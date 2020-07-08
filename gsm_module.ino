void gsm_sendmsg_mob(char mob[],char msg[])
{
 
 Serial.println("SENDING SMS");
  delay(2000);
  monitor.print("AT+CMGS=");
  monitor.write('"');
  monitor.print(mob);
  monitor.write('"');
  monitor.println();
  delay(2000);
  
  monitor.print(msg);
  monitor.print(",");
  delay(3000);
  monitor.write(0x1A);
  delay(5000);
  
  
  Serial.println("SMS SENT");
  delay(2000);
  while(monitor.available())
    char temp=monitor.read();
}