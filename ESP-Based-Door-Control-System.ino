#include <LiquidCrystal.h>

LiquidCrystal lcd(36, 35, 37, 26, 27, 28, 29);
const int Leds[] = {43, 44, 45, 46};
const int Buttons[] = {38, 39, 40, 41};
int control_led = 31;
int motorPin1 = 8;  
int motorPin2 = 9;
int enablePin = 10;

void setup() {
  Serial.begin(9600); 
  for (int i = 0; i < 4; i++) {
    pinMode(Leds[i], OUTPUT);
    pinMode(Buttons[i], INPUT);
  }
  pinMode(control_led, OUTPUT);
  digitalWrite(control_led, HIGH);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  main_screen();
}

void loop() {
  test();
}

void test() {
  if (digitalRead(38) == 1) {
    delay(50);
    while (digitalRead(38) == 1);
    delay(50);
    lcd.clear();
    open_door();
    delay(1000); 
    close_door();
    lcd.clear();
    main_screen();
    Serial.println("Door is open"); 
  }
  if (digitalRead(39) == 1) {
    delay(50);
    while (digitalRead(39) == 1);
    delay(50);
    lcd.clear();
    close_door(); 
    lcd.clear();
    main_screen();
    Serial.println("Door is closed"); 
  }
}

void open_door() {
  lcd.setCursor(0, 1);
  lcd.print("  Door is open ");
  for (int i = 0; i < 4; i++) {
    digitalWrite(Leds[i], HIGH);
  }
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 255); 
  delay(1000); 
}

void close_door() {
  lcd.setCursor(0, 1);
  lcd.print(" Door is closed ");
  for (int i = 0; i < 4; i++) {
    digitalWrite(Leds[i], LOW);
  }


  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin, 255); 
  delay(1000); 
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);
}

void blinkLEDs() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(Leds[i], HIGH); 
    delay(200);
    digitalWrite(Leds[i], LOW);  
  }
}

void main_screen() {
  lcd.begin(16, 2);
  lcd.cursor();
  lcd.print("You are Welcome ");
  lcd.setCursor(0, 1);
  lcd.print("Press the Button ");
  blinkLEDs();
  Serial.println("Welcome screen");
}
