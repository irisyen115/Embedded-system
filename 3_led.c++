class Led {  
  private:     
    byte _pin;    
    String _color;    
    int _delayTime; 
    int _toggleNum;
    int _toggleCount;

  public:    
    Led();    // 建構子
    Led(byte pin_param, int delayTime = 1000, String color_param = "UNKNOWN", int toggleNum = 0);    // 建構子多載
    
    void setPin(byte pin_param);     // 設定腳位
    byte getPin() const; // 取得腳位
    
    int getDelayTime() const { return _delayTime; }; // 取得延遲時間
    int getToggleNum() const { return _toggleNum; }; // 取得 toggle 次數
    int getToggleCount() const { return _toggleCount; }; // 取得已 toggle 次數
    
    void on() const; // 開燈
    void off() const; // 關燈
    void toggle(); // 切換燈的狀態

};

Led::Led() { 
  _pin = 2; 
  _color = "UNKNOWN"; 
  _delayTime = 500;
  _toggleNum = 0;
  _toggleCount = 0;
}

Led::Led(byte pin_param, int delayTime, String color_param, int toggleNum) : 
_pin(pin_param), _delayTime(delayTime), _color(color_param), _toggleNum(toggleNum), _toggleCount(0) {
  pinMode(_pin, OUTPUT);
}

void Led::setPin(byte pin_param) {
  if ((pin_param < 40) && (pin_param >= 0)) { 
    _pin = pin_param; 
    pinMode(_pin, OUTPUT); 
  } else {
    _pin = 2; 
    Serial.println("無效的腳位編號，使用預設腳位 2。"); 
  }
}

byte Led::getPin() const { 
  return _pin; 
}

void Led::on() const { 
  digitalWrite(_pin, HIGH);
}

void Led::off() const { 
  digitalWrite(_pin, LOW);
}

void Led::toggle() {
  if (_toggleCount < _toggleNum || _toggleNum == 0) {
    digitalWrite(_pin, !digitalRead(_pin));
    _toggleCount++;
  } 
}

//--------------------------------------------------------

void task1(void* pt) { 
  Led ledGreen(33, 500, "GREEN", 15); 
  while (1) { 
    ledGreen.toggle();
    vTaskDelay(ledGreen.getDelayTime());
    
    // 判斷是否達到切換次數後長亮
    if (ledGreen.getToggleCount() >= ledGreen.getToggleNum()) {
      ledGreen.on();
      vTaskDelete(NULL); // 結束任務
    }
  }
}

void task2(void* pt) { 
  Led ledYellow(26, 500, "YELLOW", 8); 
  while (1) { 
    ledYellow.toggle();
    vTaskDelay(ledYellow.getDelayTime()); 
  

  if (ledYellow.getToggleCount() >= ledYellow.getToggleNum()) {
      ledYellow.on();
      vTaskDelete(NULL); 
    }
  }
}

void task3(void* pt){ 
  Led ledRed(27, 500, "RED", 3); 
  while (1) { 
    ledRed.toggle();
    vTaskDelay(ledRed.getDelayTime()); 
    
    if (ledRed.getToggleCount() >= ledRed.getToggleNum()) {
      ledRed.on();
      vTaskDelete(NULL); 
    }
  }
}

void setup() {
  Serial.begin(9600);
  if (xTaskCreate(task1, "Blink 23", 1024, NULL, 1, NULL) == pdPASS) {
    Serial.println("Task1 Created.");
  }
  if (xTaskCreate(task2, "Blink 21", 1024, NULL, 1, NULL) == pdPASS) {
    Serial.println("Task2 Created.");
  }
  if (xTaskCreate(task3, "Blink 27", 1024, NULL, 1, NULL) == pdPASS) {
    Serial.println("Task3 Created.");
  }
}

void loop() {}
