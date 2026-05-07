#include <Arduino.h>
TaskHandle_t CriticalTask;

void sys_abort() {}
void sys_initialize() {}
void sys_ignite() {}
void sys_shutdown() {}

void loopCritical(void * pvParameters) {
  for (;;) {
    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      command.trim(); 

      if (command == "HELLO_ESP") {
        Serial.println("HELLO_BACK");
      }
    }

    vTaskDelay(10 / portTICK_PERIOD_MS); 
  }
}

void setup() 
{
    Serial.begin(115200);
    sys_initialize();

    xTaskCreatePinnedToCore(
        loopCritical,
        "CommsTask",
        10000,
        NULL,
        1,
        &CriticalTask,
        0
    );
}

void loop()
{
  vTaskDelay(10 / portTICK_PERIOD_MS);
}