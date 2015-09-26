/*
This program can be used to control a bot. 
- It uses three sensors placed in front, left & right direction.
- These sensors detects if there is any obstacle before them within given threshold distance.
- It performs following actions :
    When Front side is clear
      If no obstacle in either of left/right side - go straight.
      If obstacle in left/right side - apply break, move slightly backward & turn to opposite side (indicator LED is switched ON).
    When Front side is blocked
      If Left side is clear to go - apply break, move slightly backward & take right turn (indicator LED is switched ON).
      Otherwise - apply break, move slightly backward & take right turn (indicator LED is switched ON).
*/

#include <NewPing.h>            // Used NewPing library to ping ultrasonic sensors

// Macros (they live only during compilation and these values are replaced during runtime)
#define FRONT 0                // Sensor directions
#define RIGHT 1
#define LEFT  2
#define THRESHOLD 20          // Obstacle distance threshold

#define SONAR_NUM     3      // Numbe of sensors
#define MAX_DISTANCE  300    // Ultrasonic will ping till this max distance
#define PING_INTERVAL 33     // Ultrasonic ping interval

// Constant variables, usually used to store pin values
const int leftWheelP = 2;          // Bot Wheel Pins
const int leftWheelN = 3;
const int rightWheelP = 4;
const int rightWheelN = 5;

const int led = 13;                // Indicator LED pin (using default LED pin)

const int echoFront = 6;          // Sensors' echo & trig pins
const int trigFront = 7;
const int echoRight = 8;
const int trigRight = 9;
const int echoLeft = 10;
const int trigLeft = 11;

NewPing sonar[SONAR_NUM] = {                    // Sensors Array
  NewPing(trigFront, echoFront, MAX_DISTANCE),
  NewPing(trigRight, echoRight, MAX_DISTANCE),
  NewPing(trigLeft, echoLeft, MAX_DISTANCE)
};

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor
unsigned int distance[SONAR_NUM];   // Array where the ping distances are stored
uint8_t currentSensor = 0;          // Keeps track of which sensor is active

// This method is called once, this is used to initilize things
void setup() {                                 

//    Serial.begin(115200);                      // For serial output (used for debugging)
    
    pingTimer[0] = millis() + 75;              // Setting the starting time for each sensor
    for (uint8_t i = 1; i < SONAR_NUM; i++) 
      pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;    
      
    pinMode(leftWheelP, OUTPUT);               // Setting pin mode of wheels and led (pin mode of ultrasonic pins is taken care by library itself)
    pinMode(leftWheelN, OUTPUT);     
    pinMode(rightWheelP, OUTPUT);     
    pinMode(rightWheelN, OUTPUT);     
    pinMode(led, OUTPUT);   
    
}

// This method is called again and again
void loop() {                           
  
  for (uint8_t i = 0; i < SONAR_NUM; i++) {         // Loop through all the sensors
    if (millis() >= pingTimer[i]) {                 // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;    // Setting next time this sensor will be pinged
      if (i == 0 && currentSensor == SONAR_NUM - 1) // If sensor ping cycle is completed - do something with the results
      {
        /*
        for (uint8_t i = 0; i < SONAR_NUM; i++) {      // Printing detected obstacle distances (for debugging purpose)
          Serial.print(i);
          Serial.print("=");
          Serial.print(distance[i]);
          Serial.print("cm ");
        }
        Serial.println();  
        */
        
        if(distance[FRONT] != 0 && distance[RIGHT] != 0 && distance[LEFT] != 0){  // ignoring 0s (sometime sensors through 0 unnecessarily)

          if( distance[FRONT] > THRESHOLD )                                       // If FRONT is clear
          {
            if( distance[LEFT] > THRESHOLD && distance[RIGHT] <= THRESHOLD) {     // Obstacle detected in right
              stopBot();
              delay(1000);
              moveBackward();
              delay(1000);
              turnLeft();
            }
            else if( distance[RIGHT] > THRESHOLD && distance[LEFT] <= THRESHOLD) {     // Obstacle detected in left
              stopBot();  
              delay(1000);
              moveBackward();
              delay(1000);
              turnRight();
            }
            else {                                                                // Both left and right are either clear or blocked
              moveForward();
            }
          }
          else                                             // If FRONT is blocked
          {
            if( distance[LEFT] > THRESHOLD) {              // When Left side is clear to go
              stopBot();  
              delay(1000);
              moveBackward();
              delay(1000);
              turnLeft();
            }
            else {                                         // Otherwise go right, even if there is obstacle (because turnRight will go back and then take right)
              stopBot();
              delay(1000);
              moveBackward();
              delay(1000);
              turnRight();
            }
          }
        }
      }      
      sonar[currentSensor].timer_stop();          // Making sure previous timer is canceled before starting a new ping (insurance)
      currentSensor = i;                          // Sensor being accessed
      distance[currentSensor] = 0;                // Making distance zero in case there's no ping echo for this sensor
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo)
    }
  }
}

// If ping received, set the sensor distance to array
void echoCheck() { 
  if (sonar[currentSensor].check_timer())
    distance[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

// Stop dear Bot !
void stopBot(){
   digitalWrite(leftWheelP, LOW);  
   digitalWrite(leftWheelN, LOW);
   digitalWrite(rightWheelP, LOW);  
   digitalWrite(rightWheelN, LOW);
   digitalWrite(led, HIGH);
}

// Go straight Bot !
void moveForward(){
   moveBot(HIGH, HIGH);
   digitalWrite(led, LOW);
}

// No Bot, go back go back ..
void moveBackward(){
   moveBot(LOW, LOW);
}
   
// Bot, Turn left !
void turnLeft(){
  moveBot(HIGH, LOW);
  digitalWrite(led, HIGH);
}

// Bot, Turn right !
void turnRight(){
  moveBot(LOW, HIGH);
  digitalWrite(led, HIGH);
}

// Generic method to turn bot left/right or move forward/backward
void moveBot(boolean rightWheel, boolean leftWheel){
   digitalWrite(leftWheelP, leftWheel);  
   digitalWrite(leftWheelN, !leftWheel);
   digitalWrite(rightWheelP, rightWheel);  
   digitalWrite(rightWheelN, !rightWheel);
   if(leftWheel != rightWheel)              // While taking turn only one wheel moves, other stays still
   {
     if(!leftWheel)
     {
      digitalWrite(leftWheelN, LOW);      
     }
     if(!rightWheel)
     {
      digitalWrite(rightWheelN, LOW);      
     }
   }
}
