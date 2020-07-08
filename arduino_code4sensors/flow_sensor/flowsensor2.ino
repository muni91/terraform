
 
 int flowPin = 2;    
double flowRate; 
volatile int count; 
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);           
  attachInterrupt(0, Flow, RISING);    
  Serial.begin(9600);  
}
void loop() {
  // put your main code here, to run repeatedly:  
  count = 1;      
  interrupts(); 
  delay (1000);  
  noInterrupts(); 
  
  //Start the math
  flowRate = (count * 2.25);       
  flowRate = flowRate * 60;     
  flowRate = flowRate / 1000;       

  Serial.println(flowRate);        
}

void Flow()
{
   count++;
}
