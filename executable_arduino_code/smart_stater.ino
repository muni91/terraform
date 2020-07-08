#include "ACS712.h"
ACS712 load(ACS712_30A, A1);

#include <SoftwareSerial.h>
SoftwareSerial monitor(8,9);//rx/tx

int relay=3;
int flowPin = 2;    
double flowRate; 
volatile int count; 
float I;
int i=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("WELCOME to SMART STARTER");
  delay(1000);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  pinMode(flowPin,INPUT);
  attachInterrupt(0, Flow, RISING);  
  load.calibrate();  

  monitor.begin(9600);
  delay(500);
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("GSM INIT...");
  delay(1000);
  monitor.println("AT");
  delay(4000);
  
  monitor.println("AT+CMGF=1");
  delay(3000);
  
  monitor.println("AT+CMGD=1");
  delay(3000);
  monitor.println("AT+CMGD=2");
  delay(3000);
  monitor.println("AT+CMGD=3");
  delay(3000);
    
  monitor.println("AT+CNMI=2,2,0,0,0");
  delay(3000);
  
  while(monitor.available())
  {
    char temp=monitor.read();
  }
  delay(5000);
  
 
  Serial.println("GSM CONNECTED ");
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int voltage = analogRead(A0);
  Serial.print("Voltage:");
  Serial.println(voltage);
  delay(100);
      
  
  if(voltage>=600 || voltage<=450)
  {
    Serial.println("Voltage Alert");
    delay(100);
    digitalWrite(relay,LOW);
    Serial.println("Motor OFF FOR Fluctuations");
   // while(analogRead(A0==1))
    
    gsm_sendmsg_mob("9550391359","Motor OFF FOR Fluctuations");
    delay(4000);
    
  
  }
  else
  {

     if(i==0)
     {
       digitalWrite(relay,HIGH);
      Serial.println("Motor ON");
     }
    
      I = load.getCurrentAC();
      Serial.print("Current:");
      Serial.println( I );
      delay(100);
      count = 1;
      interrupts();
      delay(1000);
      noInterrupts();
  
      flowRate = (count * 1.25);
      flowRate = flowRate * 60;
      flowRate = flowRate / 1000;
      Serial.print("flow:");
      Serial.println(flowRate);
      delay(2000);
      
    if(flowRate>=0)
    {
    Serial.println("GooD ConditioN");
      gsm_sendmsg_mob("9550391359","Motor flows successuflly.");
      delay(4000);
    }
    
    else
    {
     
      digitalWrite(relay,LOW);
      Serial.println("Motor OFF for Flow");
      delay(100);
      i=1;
      
      gsm_sendmsg_mob("9550391359","Motor OFF alert at flow.");
      delay(4000);
    }
    
  }
  
   
}

void Flow()
{
   count++;
}

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