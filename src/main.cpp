#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <servo.h>

/*---------------------- 1 - Define tasks ---------------------*/
void TaskServoTest(void *pvParameters);

/*---------------------- 2 - Main functions ---------------------*/
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  };
  // Now set up two tasks to run independently.
  // xTaskCreate(TaskServoTest, "ServoTest", 256, NULL, 2, NULL);
  

}
void loop()
{
  // Empty. Things are done in Tasks.
}

/*---------------------- 3 - Tasks ---------------------*/
void TaskServoTest(void *pvParameters)
{
  (void)pvParameters;
  uint16_t time = 500;
  initMotor();
  // Short startup delay
  vTaskDelay(time / portTICK_PERIOD_MS);
  Serial.println("Servo single-test: Forward");
  runForward();
  vTaskDelay(time / portTICK_PERIOD_MS);
  Serial.println("Servo single-test: Backward");
  runBackward();
  vTaskDelay(time / portTICK_PERIOD_MS);
  Serial.println("Servo single-test: Left");
  runLeft();
  vTaskDelay(time / portTICK_PERIOD_MS);
  Serial.println("Servo single-test: Right");
  runRight();
  vTaskDelay(time / portTICK_PERIOD_MS);
  stopServo();
  // Stop and delete this task so it doesn't run forever
  vTaskDelete(NULL);
}