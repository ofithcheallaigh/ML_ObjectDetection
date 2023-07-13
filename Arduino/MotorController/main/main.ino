#include <Servo.h>

Servo servo;
int angle = 10;

void setup() {
  servo.attach(8);
  servo.write(angle);
}


void loop() 
{ 
 // scan from 0 to 180 degrees
  for(angle = 10; angle < 50; angle++)  
  {                                  
    servo.write(angle);               
    delay(200);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 50; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(200);       
  } 
}
