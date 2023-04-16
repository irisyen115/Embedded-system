#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // 螢幕寬度
#define SCREEN_HEIGHT 64 // 螢幕高度

#define DHTPIN 15 // 溫濕度感測器的數位腳位
#define DHTTYPE DHT22 // 使用DHT22溫濕度感測器

DHT dht(DHTPIN, DHTTYPE); // 創建一個DHT物件

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // 創建一個Adafruit_SSD1306物件

void setup() {
  Serial.begin(115200);
  dht.begin(); // 啟動DHT感測器
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // 啟動OLED顯示器
  display.clearDisplay(); // 清除OLED顯示器的畫面
  display.display(); // 更新OLED顯示器的畫面
}

void loop() {
  float temperature = dht.readTemperature(); // 讀取溫度數值
  float humidity = dht.readHumidity(); // 讀取濕度數值

  display.clearDisplay(); // 清除OLED顯示器的畫面
  display.setCursor(0,0); // 設定游標的位置
  display.setTextSize(2); // 設定文字大小
  display.setTextColor(SSD1306_WHITE); // 設定文字顏色
  display.print("Temperature: "); // 顯示文字
  display.println(temperature, 1); // 顯示溫度數值，保留1位小數
  display.print("Humidity: "); // 顯示文字
  display.println(humidity, 1); // 顯示濕度數值，保留1位小數
  display.display(); // 更新OLED顯示器的畫面
  delay(2000); // 延遲2秒
}