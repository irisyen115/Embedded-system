#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin(18, 19);
  lcd.init();
  lcd.backlight();
}

void loop() {
  const float BETA = 3950;
  int analogValue = analogRead(34);
  float celsius = 1 / (log(1 / (4095. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  int temp = static_cast<int>(celsius);
  lcd.setCursor(0, 0);
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print(temp);
  delay(500); // this speeds up the simulation
}
`