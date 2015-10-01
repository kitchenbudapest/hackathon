### HC-SR501 PIR sensor

PIR sensors allow you to sense motion, almost always used to detect whether a human has moved in or out of the sensors range.

#### Features:

+ Output: Digital pulse high (3V) when triggered (motion detected) digital low when idle (no motion detected). Pulse lengths are determined by resistors and capacitors on the PCB and differ from sensor to sensor.
+ Sensitivity range: up to 20 feet (6 meters) 110 degrees x 70 degrees detection range
+ Power supply: 3.3V - 5V input voltage

![alt text](img/hcsr501.jpg)


When connecting up the PIR sensor as above, the DO (Digital OUT) does not stay on HIGH level when moving in front of it but actually turns HIGH and LOW every second or so. That is called "non-retriggering".

![alt text](img/pir4.gif)

When change the jumper, so that it is in the H position. You will notice that now the DO does stay HIGH level the entire time that something is moving. That is called "retriggering".

![alt text](img/pir5.gif)

### Raspberry PI usage:

#### Pinout

![alt text](img/pir2.jpg)

#### Wiring

![alt text](img/pir3.png)

### Arduino nano usage:

#### Pinout

![alt text](img/arduino_pinout.png)

#### Wiring

![alt text](img/hcsr501ardu.png)

#### Example code
```
int pirPin = 7;
int val;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(pirPin); //read state of the PIR

  if (val == LOW) {
    Serial.println("No motion"); //if the value read is low, there was no motion
  }
  else {
    Serial.println("Motion!"); //if the value read was high, there was motion
  }

  delay(1000);
}
```
##### Source:
[Here](http://robotic-controls.com/book/export/html/16)
