// Define all the pins of the motor driver module L298N
#define enaPin 3
#define in1 5
#define in2 6
#define in3 9
#define in4 10
#define enbPin 11

// Define the pins fan/motor driver L9110S
#define fan1 7
#define fan2 8

// Define the pin for IR sensor
#define IRsensor 12

// Pins for the ultrasonic sensor
#define trigPin 2
#define echoPin 4

void setup() {

  Serial.begin(9600); // Start the serial monitor 


// Define if pins are input or output
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
}

void loop() {
  
  // CODE FOR ULTRASONIC SENSOR TO DETECT A BARRIER IN FRONT OF IT
  
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

  

  //CODE AS TO HOW BOB SHOULD WORK

  if (Trash == 0) {         //When Trash detected
    Stop();
    RunFan();
    delay(5000);
    StopFan();
  }

  else if (Trash == 1) {    //When Trash not detected

    if (distance > 30){
      Forward();
      delay(100);
      //Stop();
    }
    else if (distance <= 30) {
      Backward();
      delay(500);
      Stop();
      delay(500);
      Left();
      delay(200);
      Stop();
    }
  }
}

// FUNCTIONS TO CHANGE THE DIRECTION OF THE WHEELS
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


// FUNCTIONS FOR THE FAN TO ROTATE AND STOP

void StopFan() {
  digitalWrite(fan1,LOW);
  digitalWrite(fan2,LOW);
}

void RunFan() {
  digitalWrite(fan1,HIGH);
  digitalWrite(fan2,LOW);
}
