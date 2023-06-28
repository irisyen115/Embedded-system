# include <ESP32Servo.h>
// 定義模擬輸入腳位
#define IN_X 32
#define IN_Y 33
// 定義伺服馬達輸出腳位
#define OUT_X 12
#define OUT_Y 13
// 定義取樣點數和中間位置
#define size 5
#define middle size/2

// 創建兩個伺服馬達物件
Servo servoX, servoY;

// 創建兩個存放取樣數據的陣列
int valX[size] = {0, 0, 0, 0, 0};
int valY[size] = {0, 0, 0, 0, 0};

// 排序用的比較函數
int cmp (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

// 過濾取樣數據
void filter() {
  static byte i = 0;

  valX[i] = analogRead(IN_X);
  valY[i] = analogRead(IN_Y);

  qsort(valX, size, sizeof(int), cmp);
  qsort(valY, size, sizeof(int), cmp);

  if (++i % size == 0) i = 0;
}

// 控制伺服馬達移動
void control() {
  int posX, posY;

  // 取中間位置的數值作為控制信號
  posX = valX[middle];
  posY = valY[middle];

  // 寫入控制信號到伺服馬達
  servoX.write(posX);
  servoY.write(posY);

  // 在序列埠上顯示控制信號
  printf("posX: %d \n", posX);
  printf("posY: %d \n", posY);

  // 等待300毫秒
  delay(300);
}

void setup() {
  // 設定模擬輸入的 ADC 參數
  analogSetAttenuation(ADC_11db);
  analogSetWidth(10);
  // 連接伺服馬達輸出腳位
  servoX.attach(OUT_X, 500, 2400);
  servoY.attach(OUT_X, 500, 2400);
}

void loop() {
  // 過濾取樣數據
  filter();
  // 控制伺服馬達移動
  control();
}