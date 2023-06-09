#include <U8g2lib.h> 
#define LED 5
#define ISR_PIN 33 
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

uint8_t score = 0; 
volatile bool flashlight = false; 
SemaphoreHandle_t xSem; 

void IRAM_ATTR ISR() { 
  flashlight = true; 
  xSemaphoreGiveFromISR(xSem, NULL); 
}

void taskOLED (void * pvParam) { 
  u8g2.begin(); 
  u8g2.setFont (u8g2_font_inb63_mn); 
  String txt; 

  while (1) {
    if (score < 10) { 
      txt = "0" + String(score); 
    } else { 
      txt = String(score); 
    }
    
    u8g2.firstPage(); 
    do {
      u8g2.drawStr(12, 63, txt.c_str()); 
    } while ( u8g2.nextPage()); 

    vTaskDelay (pdMS_TO_TICKS (100)); 
    }
}

void taskScore (void * pvParam) { 
  uint32_t preMs = 0; 

  while (1) { 
    if (xSemaphoreTake(xSem, portMAX_DELAY) == pdPASS) {
      if (xTaskGetTickCountFromISR() - preMs < 1000)
        continue;  
        
      if (++score == 100) score = 0; 
      preMs = xTaskGetTickCountFromISR();
    }
  }
}

void taskBlink (void * pvParam) { 
  uint8_t counter = 0; 
  pinMode(LED, OUTPUT);

  while (1) { 
    digitalWrite(LED, !digitalRead(LED)); 
    
    if (!flashlight) {
      vTaskDelay (pdMS_TO_TICKS (500));
    } else { 
      if (++counter == 10) { 
        counter = 0; 
        flashlight = false;
      }
      vTaskDelay (pdMS_TO_TICKS (100));
    }
  }
}

void setup() {
  Serial.begin(115200); 
  pinMode (ISR_PIN, INPUT_PULLUP); 
  attachInterrupt (ISR_PIN, ISR, RISING);

  xSem = xSemaphoreCreateBinary(); 
  if (xSem == NULL) {
    Serial.println("無法建立「二元旗號」物件~");
  }

  xTaskCreate(taskScore, "score task", 1000, NULL, 2, NULL); 
  xTaskCreate(taskBlink, "blink task", 1000, NULL, 1, NULL); 
  xTaskCreate(taskOLED, "OLED task", 1500, NULL, 1, NULL);

}

void loop() {}