// 定義按鈕和LED的接腳編號
const int buttonPin1 = 4; // 按鈕接腳編號
const int buttonPin2 = 2; // 按鈕接腳編號
const int ledPin = 5; // LED接腳編號

// 定義變數用於儲存按鈕狀態
int buttonState = 0;

void setup() {
  // 設定串列通訊速率為115200
  Serial.begin(115200); 
  // 將按鈕接腳設定為輸入模式 
  pinMode(buttonPin2, INPUT);
  // 將LED接腳設定為輸出模式
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 讀取按鈕的狀態
  buttonState = digitalRead(buttonPin2);
  // 在序列埠顯示按鈕狀態
  Serial.println(buttonState);
    Serial.println(digitalRead(buttonPin1));

  // 如果按鈕被按下
  // if (buttonState == HIGH) {
  //   // 點亮LED
  //   digitalWrite(ledPin, HIGH);
  // } else {
  //   // 熄滅LED
  //   digitalWrite(ledPin, LOW);
  // }
}