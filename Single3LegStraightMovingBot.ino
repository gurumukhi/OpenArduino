/*
  Single3LegStraightMovingBot.ino
*/

const int frontWheelP = 6;        // Wheets pins
const int frontWheelN = 7;
const int leftWheelP = 9;
const int leftWheelN = 8;
const int rightWheelP = 10;
const int rightWheelN = 11;
const int led = 13;                // Indicator LED pin (using default LED pin)

// This method is called once, this is used to initilize things
void setup() {                                 
    Serial.begin(115200);                      // For serial output (used for debugging)    
    pinMode(frontWheelN, OUTPUT);               // Setting pin mode of wheels and led     
    pinMode(frontWheelP, OUTPUT);     
    pinMode(leftWheelP, OUTPUT);
    pinMode(leftWheelN, OUTPUT);     
    pinMode(rightWheelP, OUTPUT);     
    pinMode(rightWheelN, OUTPUT);     
    pinMode(led, OUTPUT);   
}

// This method is called again and again
void loop() {
   Serial.println("Moving");
   digitalWrite(frontWheelP, HIGH);  
   digitalWrite(frontWheelN, LOW);
   digitalWrite(leftWheelP, HIGH);  
   digitalWrite(leftWheelN, LOW);
   digitalWrite(rightWheelP, HIGH);  
   digitalWrite(rightWheelN, LOW);
   digitalWrite(led, HIGH);
   delay(1000);
//   stopBot();
   delay(1000);
}

// Stop dear Bot !
void stopBot(){
  Serial.println("stop");
   digitalWrite(frontWheelP, LOW);  
   digitalWrite(frontWheelN, LOW);
   digitalWrite(leftWheelP, LOW);  
   digitalWrite(leftWheelN, LOW);
   digitalWrite(rightWheelP, LOW);  
   digitalWrite(rightWheelN, LOW);
   digitalWrite(led, LOW);
}
