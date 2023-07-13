The sensor is a HC-SR04 ultrasonic sensor. The GitHub page can be fond here: https://github.com/sparkfun/HC-SR04_UltrasonicSensor     
The data sheet can be found here: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf      

The sensor operates off 5 volts, with a range distance of 2cm to 4m.    
The measuring angle seems to be about 15 degrees or so.

The module is a 4 pin module. The pins are:
- VCC to 5V on the uC
- GND to GND on the uC
- Trigger to pin 12 on the uC
- Echo to pin 13 on the uC   

The trigger and echo pins can defined as:
```
const int trigPin = 12;
const int exhoPin = 13;
```

This this is an ultrasonic sensor, we are dealing with sound waves. In the code, we will need two variables: **duration** and **distance**:
```
float duration, distance;
```

The next stage needs us to set up trigger pin and an output and the echo pin as an input:

```
void setup()
{
    pinMode(trigPin, OUTPUT);       
    pinMode(echoPin, INPUT);       
    Serial.begin(9600);      
}
````

The next stage is to set a loop where the trigger in is set low for 2 microseconds (to ensure the pin is low first), then it is set high for 10 microseconds. It is this process which sends out the 8-cycle sonic bursts from the transmitter which are bounced by towards the receiver (which is connected to the echo pin):

```
void loop() { 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH); 
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW); 
 ```
 When the wave comes back to the receiver, it tuens the echo pin high for the length of time the wave is travelling for. This can be acheived by using the Arduino function:
 ```
 pulseIn()
 ```
 This function takes two arguments: the pin we are listening on, and either a high or low state. The state is important, because whenever the function detects that state, a time starts, and the timer stops when the state changes. 
