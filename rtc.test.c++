#include <Wire.h>
#include <U8g2lib.h>
#include <RTClib.h>

#define SCREEN_WIDRH 128
#define SCREEN_HEIGHT 64

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // 創建一個U8g2物件

RTC_DS1307 RTC; // 創建一個RTC_DS1307物件
char days[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; // 用來儲存星期幾的字串陣列

void setup() {
  Serial.begin(115200);

  if (!RTC.begin()) { // 如果RTC無法開始運作
    Serial.println("Couldn't find RTC"); // 印出錯誤訊息
    while(1); // 無限死迴圈
  }

  u8g2.begin(); // 初始化U8g2物件
  u8g2.clearBuffer(); // 清除緩存區
  u8g2.setFont(u8g2_font_ncenB08_tr); // 設定字體
  u8g2.drawStr(20, 20, "RTC"); // 顯示文字
  u8g2.sendBuffer(); // 更新螢幕
}

void loop() {
  DateTime now = RTC.now(); // 取得現在的日期時間

  u8g2.clearBuffer(); // 清除緩存區
  u8g2.setCursor(0, 10); // 設定游標位置
  u8g2.print(now.day());
  u8g2.print('/');
  u8g2.print(now.month());
  u8g2.print('/');
  u8g2.print(now.year());
  u8g2.print(" ");
  u8g2.print(days[now.dayOfTheWeek()]); // 顯示日期和星期幾
  u8g2.setCursor(0, 30); // 設定游標位置
  u8g2.print(now.hour());
  u8g2.print(':');
  if (now.minute() < 10)
    u8g2.print('0');
  u8g2.print(now.minute());
  u8g2.print(':');
  if (now.second() < 10)
    u8g2.print('0');
  u8g2.print(now.second()); // 顯示時間
  u8g2.sendBuffer(); // 更新螢幕
  delay(1000); // 延遲 1 秒，加速模擬速度
}