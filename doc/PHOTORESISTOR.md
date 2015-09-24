### Photoresistor


A photoresistor, or light-dependent resistor (LDR), or photocell is a resistor whose resistance will decrease when incident light intensity increase; in other words, it exhibits photoconductivity.

![alt text](img/photo.jpg)

Basically we'll be able to measure how bright or dark the room is using the photocell. Note that photocells are not precision measurement devices, and this technique is also not very precise so its only good for basic measurements.

#### Features

* working voltage: 3.3~5V
* output: digital switching  (LOW or HIGH voltage on D pin)
* output current >= 15mA, can directly light LED.
* with adjustable potentiometer to adjust the sensitivity

### Raspberry PI usage:

#### Pinout

![alt text](img/pir2.jpg)

#### Wiring

![alt text](img/photo.png)

### Arduino nano usage:

#### Pinout

![alt text](img/arduino_pinout.png)

#### Wiring

![alt text](img/photoardu.png)

#### Example code
```
int ledPin = 13; // LED connected to digital pin 13
int inPin = 4;   // Photoresistor connected to digital pin 7
int val = 0;     // variable to store the read value

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin 13 as output
  pinMode(inPin, INPUT);      // sets the digital pin 7 as input
}

void loop()
{
  val = digitalRead(inPin);   // read the input pin
  digitalWrite(ledPin, val);    // sets the LED to the Photoresistor's value
}
```

###### Source:
[Here](http://uugear.com)
