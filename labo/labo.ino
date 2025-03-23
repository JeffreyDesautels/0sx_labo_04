// Impair (2255309) donc enonce B
#include <LCD_I2C.h>
#include <HCSR04.h>

#define TRIGGER_PIN 6
#define ECHO_PIN 7

LCD_I2C lcd(0x27, 16, 2);
HCSR04 hc(TRIGGER_PIN, ECHO_PIN);


unsigned long current_time = 0;

void setup() {
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();

  start_task();
}

void loop() {
  current_time = millis();

  distance_task(current_time);
  // serial_port_task(current_time);
}

void start_task() {
  lcd.setCursor(0, 0);
  lcd.print("2255309");

  lcd.setCursor(0, 1);
  lcd.print("Labo 4B");

  delay(2000);
  lcd.clear();
}

void distance_task(unsigned long cT) { // bug dans fonction, interval bcp trop long
  static unsigned long previous_time = 0;
  const long interval = 50;
  float distance = hc.dist();

  if (cT - previous_time >= interval) {
    previous_time = cT;

    Serial.print("Distance: ");
    Serial.println(distance);

    lcd.setCursor(0, 0);
    lcd.print("Dist : ");
    lcd.setCursor(7, 0);
    lcd.print(distance);
    lcd.print(" cm     ");

    lcd.setCursor(0, 1);
    lcd.print("Obj  : ");
    lcd.setCursor(7, 1);
    if (distance < 30) {
      lcd.print("Trop pres  ");
    } else if (distance > 60) {
      lcd.print("Trop loin  ");
    } else {
      lcd.print("Tres bien  "); //afficher angle stepper ici
    }
  }
}

void stepper_task() {

}

void serial_port_task(unsigned long cT) {
  static unsigned long previous_time = 0;
  const long interval = 100;

  if (cT - previous_time >= interval) {
    previous_time = cT;

    Serial.print("etd:2255309,dist:");
    // Serial.print(distance);
    Serial.println(",deg:");
    // Serial.print(angle);
  }
}