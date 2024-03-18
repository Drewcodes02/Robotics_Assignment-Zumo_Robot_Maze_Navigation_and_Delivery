// Libraries for Zumo
#include <Zumo32U4.h>
#include <stdlib.h> 
#include <Wire.h>

// Zumo componets 
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4ProximitySensors proxSensors;

// Zumo senors, speeds and timing
#define QTR_THRESHOLD     200 // Line sensor detection threshold
#define FORWARD_SPEED     80 // Moving forward speed
#define TURN_SPEED        150 // Turning spped
#define REVERSE_SPEED     100 // Reversing speed 
#define TURN_DURATION     400 // The duration of the each turn
#define OBJECT_DETECTION_THRESHOLD 6 // proximity sensor detection threshold

unsigned int stuckCounter = 0; // Count for when the robot might be stuck
#define STUCK_THRESHOLD   5 // threshold for stuck instances before a 180 degree turn
unsigned long lastTurnTime = 0; // time of the last turn
const unsigned long turnInterval = 10000; // Interval for 180-degree turn every 10 seconds
char lastTurnDirection = 'N'; // N for None, L for Left, R for Right

// Before starting, button is pressed and a countdown will start. and then the zumo will start moving.
void waitForButtonAndCountDown() {
    lcd.clear();
    lcd.print(F("Press A"));
    lcd.gotoXY(0, 1);
    lcd.print(F("to start"));
    
    while (!buttonA.getSingleDebouncedPress()) {}
    
    for (int i = 3; i > 0; i--) {
        lcd.clear();
        lcd.print(i);
        buzzer.playFrequency(440, 500, 15);
        delay(1000);
    }
    
    lcd.clear();
    lcd.print(F("Go!"));
    delay(1000);
}
// this is for the 180 degree turn
void perform180Turn() {
  motors.setSpeeds(-200, 200); // command for 180 degree turn
  delay(1000); // duration for the turn
  motors.setSpeeds(0, 0); // zumo stops after turn
}

// Setup of zumo, initalises the senors and waits for button to be pressed 
void setup() {
    Serial.begin(9600);
  lineSensors.initThreeSensors();
  waitForButtonAndCountDown();
  proxSensors.initThreeSensors();
  lastTurnTime = millis(); // for time tracking
}

// The main loop, manages the robots behavior in the maze
void loop() {
  mazeFunctionalities();
}

// functionalitys for the maze, including object detection and also 180 turn for when it gets stuck
void mazeFunctionalities() {
  unsigned long currentTime = millis();

// 180 turn every 5 seconds incase the zumo gets stuck
     if (currentTime - lastTurnTime >= 5000) { // 5000 milliseconds = 5 seconds
        buzzer.playFrequency(880, 500, 15); // beep before the turn
        delay(500); 
        perform180Turn(); // Performs a 180 degree turn
        lastTurnTime = millis(); 
        return; 
    }
  // proximity sensor readings and object detection 
  proxSensors.read();
    uint8_t leftValue = proxSensors.countsLeftWithLeftLeds(); 
    uint8_t rightValue = proxSensors.countsRightWithLeftLeds(); 
    uint8_t frontValue = proxSensors.countsFrontWithLeftLeds(); 
  
  // object detection logic
    bool objectDetected = leftValue >= OBJECT_DETECTION_THRESHOLD ||
                          rightValue >= OBJECT_DETECTION_THRESHOLD ||
                          frontValue >= OBJECT_DETECTION_THRESHOLD;
  
    if (objectDetected) {
        motors.setSpeeds(0, 0); // stops the zumo 
        buzzer.playFrequency(440, 200, 15); // plays a beep sound so we know when its found the house
        delay(500); 

        if (leftValue >= OBJECT_DETECTION_THRESHOLD) {
            buzzer.play("L"); // beep when found something on the left
        } else if (rightValue >= OBJECT_DETECTION_THRESHOLD) {
            buzzer.play("R"); //beep when found something on the right
        } else {
            buzzer.play("F"); // beep when found somthing in front
        }

        perform180Turn(); 
        lastTurnTime = millis(); 
    } else if (currentTime - lastTurnTime >= 10000) { 
        buzzer.playFrequency(880, 500, 15); 
        delay(500); 
        perform180Turn(); 
        lastTurnTime = millis(); 
    } else {
        mazeNavigation(); // No object detected, continue going through the maze
    }
}

// Navigation through maze, using line sensors
void mazeNavigation() {
    unsigned int sensorValues[3];
    lineSensors.read(sensorValues); // reads line sensor values

    if (sensorValues[1] < QTR_THRESHOLD) {
        motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
        stuckCounter = 0;
        lastTurnTime = millis();
    } else {
        motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED); // Reverse iff off the intended route
        delay(250); 

        // decides next direction based off previous movement and sensor readings 
if (lastTurnDirection == 'N' || lastTurnDirection == 'R') { 
    // if no recent turn or last turned right, attempt to turn left
    if (sensorValues[0] < QTR_THRESHOLD) { // left sensor detects line
        motors.setSpeeds(TURN_SPEED, -TURN_SPEED); // Trn left
        lastTurnDirection = 'L'; // updates direction
    } else {
        motors.setSpeeds(-TURN_SPEED, TURN_SPEED); // otherwise, turn right
        lastTurnDirection = 'R'; // updates direction
    }
} else if (lastTurnDirection == 'L') { // if last turned left, consider turning right
    if (sensorValues[2] < QTR_THRESHOLD) { // right sensor detects line
        motors.setSpeeds(-TURN_SPEED, TURN_SPEED); // turn righ
        lastTurnDirection = 'R'; // updates direction
    } else {
        motors.setSpeeds(TURN_SPEED, -TURN_SPEED); // otherwise, turn left
        lastTurnDirection = 'L'; // updates direction
    }
}


        delay(TURN_DURATION); // waits for turn to complete
        stuckCounter++; 
    }
}

// Sees if the zumo is stuck based on the stuck counter and threshold
bool isStuckOrLooping() {
  return stuckCounter >= STUCK_THRESHOLD;
}
