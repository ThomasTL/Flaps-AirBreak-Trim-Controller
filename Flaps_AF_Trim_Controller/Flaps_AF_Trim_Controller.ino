// Requires Arduino Joystick Library https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Joystick.h>

#define FLAPS_PIN       A2
#define AIRBREAKS_PIN   A1
#define TRIM_PIN        A3
#define BUTTON_1        9
#define BUTTON_2        8
#define BUTTON_3        7

Joystick_ Joystick (  JOYSTICK_DEFAULT_REPORT_ID,
                      JOYSTICK_TYPE_JOYSTICK,
                      3,     // Number of available buttons
                      0,      // Number of available hat switches
                      false,   // X Axis
                      false,   // Y Axis
                      false,   // Z Axis
                      true,  // X Axis Rotation
                      true,  // Y Axis Rotation
                      true,  // Z Axis Rotation
                      false,  // Rudder
                      false,  // Throttle
                      false,  // Accelerator
                      false,  // Brake
                      false   // Steering
                     ); 
 
int FlapsValue;
int AirBreakValue;
int TrimValue;

int lastButton1State = 0;
int lastButton2State = 0;
int lastButton3State = 0;

void setup() {

  pinMode(FLAPS_PIN, INPUT_PULLUP);
  pinMode(AIRBREAKS_PIN, INPUT_PULLUP); 
  pinMode(TRIM_PIN, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  
  Joystick.setRzAxisRange(0, 1023); 
  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);

  Joystick.begin();
}

void loop() {
  
  // Flaps linear potentiometer
  FlapsValue = analogRead(FLAPS_PIN); 
  Joystick.setRxAxis(FlapsValue);

  // Air break linear potentiometer
  AirBreakValue = analogRead(AIRBREAKS_PIN); 
  Joystick.setRyAxis(AirBreakValue);

  // Trim linear potentiometer
  TrimValue = analogRead(TRIM_PIN);
  Joystick.setRzAxis(TrimValue);

  // Read buttons state
  int currentButton1State = !digitalRead(BUTTON_1);
  if(currentButton1State != lastButton1State) {
    Joystick.setButton(0, currentButton1State);
    lastButton1State = currentButton1State;
  }

  int currentButton2State = !digitalRead(BUTTON_2);
  if(currentButton2State != lastButton2State) {
    Joystick.setButton(1, currentButton2State);
    lastButton2State = currentButton2State;
  }

  int currentButton3State = !digitalRead(BUTTON_3);
  if(currentButton3State != lastButton3State) {
    Joystick.setButton(2, currentButton3State);
    lastButton3State = currentButton3State;
  }    

  // Pole delay/debounce
  delay(10);
  
  Joystick.sendState();
} 
