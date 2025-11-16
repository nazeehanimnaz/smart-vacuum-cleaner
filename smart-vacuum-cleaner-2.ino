// Install library IRremote by Armin Joachimsmeyer 
// This code supports version 4.4.1 of the above library
//#include <IRremote.hpp>

// Define IR receiver pin
//#define irReceiver 12 

// Define all the pins of the motor driver module
#define enaPin 3
#define in1 5
#define in2 6
#define in3 9
#define in4 10
#define enbPin 11
#define fan1 7
#define fan2 8
#define IRsensor 12
#define trigPin 2
#define echoPin 4
#define IRsensorS 13

void setup() {
  //Serial.begin(115200); // Establish serial communication
  //IrReceiver.begin(irReceiver, ENABLE_LED_FEEDBACK); // Start the receiver

  Serial.begin(9600);

  // Configure the pins as INPUT or OUTPUT
  //pinMode(irReceiver, INPUT);
  pinMode(enaPin, OUTPUT);
  pinMode(enbPin, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
  pinMode(IRsensor,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IRsensorS,INPUT);
}

void loop() {
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  int Trash = digitalRead(IRsensor);    //Get reading from IR sensor
  //int barrier = analogRead(IRsensorS);

   // Serial.print("Barrier: ");
  //Serial.println(barrier);
    //  Serial.print("\n");

  if (Trash == 0) {         //When Trash detected
    Stop();
    RunFan();
    delay(5000);
    StopFan();
  }

  else if (Trash == 1) {    //When Trash not detected

    if (distance > 30){
      Forward();
      //delay(500);
      //Stop();
    }
    else if (distance <= 30) {
      Backward();
      delay(500);
      Stop();
      delay(500);
      Left();
      delay(500);
      Stop();
    }
  }
}

// Functions to change the direction
void Backward() {
  analogWrite(enaPin,180);
  analogWrite(enbPin,180);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

 void Forward() {
  analogWrite(enaPin,180);
  analogWrite(enbPin,180);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

 void Stop() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void Right() {
  digitalWrite(enaPin,HIGH);
  digitalWrite(enbPin,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void Left() {
  digitalWrite(enaPin,HIGH);
  digitalWrite(enbPin,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void StopFan() {
  digitalWrite(fan1,LOW);
  digitalWrite(fan2,LOW);
}

void RunFan() {
  digitalWrite(fan1,HIGH);
  digitalWrite(fan2,LOW);
}