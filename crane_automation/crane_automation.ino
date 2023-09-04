#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int joystick1XPin = A0, joystick1YPin = A1, joystick2XPin = A2, joystick2YPin = A3;
const int relay1Pin = 2, relay2Pin = 3, relay3Pin = 6, relay4Pin = 7, relay5Pin = 5, relay6Pin = 4;
const int limitSwitch1Pin = 10, limitSwitch2Pin = 11;




void setup() {
  Serial.begin(9600);
  lcd.begin();


  lcd.backlight();
  lcd.print("Device on");
  pinMode(joystick1XPin, INPUT);
  pinMode(joystick1YPin, INPUT);
  pinMode(joystick2XPin, INPUT);
  pinMode(joystick2YPin, INPUT);
  pinMode(limitSwitch1Pin, INPUT_PULLUP);
  pinMode(limitSwitch2Pin, INPUT_PULLUP);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  pinMode(relay5Pin, OUTPUT);
  pinMode(relay6Pin, OUTPUT);
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);
  digitalWrite(relay4Pin, HIGH);
  digitalWrite(relay5Pin, HIGH);
  digitalWrite(relay6Pin, HIGH);
  delay(2000);
  lcd.clear();
}

void loop() {
  int joystick1XValue = map(analogRead(joystick1XPin), 0, 1023, 0, 100);
  int joystick1YValue = map(analogRead(joystick1YPin), 0, 1023, 0, 100);
  int joystick2XValue = map(analogRead(joystick2XPin), 0, 1023, 0, 100);

  bool limitSwitch1State = digitalRead(limitSwitch1Pin);
  bool limitSwitch2State = digitalRead(limitSwitch2Pin);

  digitalWrite(relay3Pin, (joystick1XValue > 80 ) ? LOW : HIGH);
  digitalWrite(relay4Pin, (joystick1XValue < 20 ) ? LOW : HIGH);
  digitalWrite(relay1Pin, (joystick1YValue > 80 && limitSwitch1State == 1 ) ? LOW : HIGH);
  digitalWrite(relay2Pin, (joystick1YValue < 20 && limitSwitch2State == 1 ) ? LOW : HIGH);

  digitalWrite(relay5Pin, (joystick2XValue > 70) ? LOW : HIGH);
  digitalWrite(relay6Pin, (joystick2XValue < 20) ? LOW : HIGH);

  Serial.print("Joystick 1 X: ");
  Serial.print(joystick1XValue);
  Serial.print("\tJoystick 1 Y: ");
  Serial.print(joystick1YValue);
  Serial.print("\tJoystick 2 X: ");
  Serial.println(joystick2XValue);
  Serial.print("Limit Switch 1: ");
  Serial.print(limitSwitch1State);
  Serial.print("  Limit Switch 2: ");
  Serial.println(limitSwitch2State);

  lcd.setCursor(0, 0);
  lcd.print("CRANE:");

  lcd.setCursor(0, 1);
  lcd.print("PULLY:");

  String pullyStatus; // String variable to store motor status
  String motorStatus;
  // Check the joystick values and limit switch states to determine the motor status
  if (joystick1XValue > 80 ) {
    motorStatus = "UP   ";
  } else if (joystick1XValue < 20 ) {
    motorStatus = "DOWN ";
  } else if (joystick1YValue > 80 && limitSwitch1State == 1) {

    motorStatus = "RIGHT";
  } else if (joystick1YValue < 20 && limitSwitch2State == 1) {

    motorStatus = "LEFT ";
  } else {
    motorStatus = "STOP ";
  }

  if (joystick2XValue > 70) {
    pullyStatus   = "UP  ";
  } else if (joystick2XValue < 20) {
    pullyStatus = "DOWN ";
  }
  else
  {
    pullyStatus = "STOP";
  }

  // Clear the LCD and print the motor status
  lcd.setCursor(8, 0);
  lcd.print(motorStatus);
  lcd.setCursor(8, 1);
  lcd.print(pullyStatus);



  delay(1000);


}
