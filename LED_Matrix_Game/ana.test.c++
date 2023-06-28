#include <MD_MAX72xx.h>

#define MAX_DEVICES 4

const int maxX = MAX_DEVICES * 8 - 1;
const int maxY = 7;

// 設定 LED Dot Matrix 連接的硬體引腳
#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN    5 

// 設定按鈕的硬體引腳
#define VERT_PIN  34
#define HORZ_PIN  35
#define SEL_PIN   27

// 定義 LED Dot Matrix 硬體的類型
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

// 建立 MD_MAX72xx物件
MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::PAROLA_HW, CS_PIN, MAX_DEVICES);

// 設定遊戲的繪圖起點
int x = 0;
int y = 0;

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.clear();
  mx.update();
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  int horz = analogRead(HORZ_PIN);
  int vert = analogRead(VERT_PIN);
  if (vert < 300) {
    y = min(y + 1, maxY);
  }
  if (vert > 700) {
    y = max(y - 1, 0);
  }
  if (horz > 700) {
    x = min(x + 1, maxX);
  }
  if (horz < 300) {
    x = max(x - 1, 0);
  }
  if (digitalRead(SEL_PIN) == LOW) {
    mx.clear();
    x = 0;
    y = 0;
  }
  mx.setPoint(y, x, true);
  mx.update();
  delay(100);
}