#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <motor.h>
/*---------------------- 1 - Global variables ---------------------*/
// Motor
#define MOTOR_LEFT_IN1 8
#define MOTOR_LEFT_IN2 9
#define MOTOR_RIGHT_IN3 10
#define MOTOR_RIGHT_IN4 11
// IR sensors
#define S1 A1 // leftmost
#define S2 A2
#define S3 A3 // center
#define S4 A4
#define S5 A5 // rightmost

/*---------------------- 2 - Define tasks ---------------------*/
void TaskInitHardware(void *pvParameters);
void TaskMotorTest(void *pvParameters);
void TaskLineFollower(void *pvParameters);

/*---------------------- 3 - Main functions ---------------------*/
void setup()
{
  // init tasks
  // xTaskCreate(TaskMotorTest, "MotorTest", 64, NULL, 2, NULL);
  xTaskCreate(TaskInitHardware, "InitHardware", 64, NULL, 2, NULL);
  xTaskCreate(TaskLineFollower, "LineFollow", 64, NULL, 3, NULL);
}
void loop()
{
  // Empty. Tasks run under FreeRTOS.
}

/*---------------------- 4 - Tasks ---------------------*/
void TaskInitHardware(void *pvParameters)
{
  (void)pvParameters;
  Serial.begin(115200);
  initMotor(MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_RIGHT_IN3, MOTOR_RIGHT_IN4);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  // Stop and delete this task so it doesn't run forever
  vTaskDelete(NULL);
}
void TaskMotorTest(void *pvParameters)
{
  (void)pvParameters;
  uint16_t time = 500;
  Serial.println("Motor single-test: Forward");
  runForward();
  vTaskDelay(time / portTICK_PERIOD_MS);
  Serial.println("Motor single-test: Backward");
  runBackward();
  vTaskDelay(time / portTICK_PERIOD_MS);
  Serial.println("Motor single-test: Left");
  runLeft();
  vTaskDelay(time / portTICK_PERIOD_MS);
  Serial.println("Motor single-test: Right");
  runRight();
  vTaskDelay(time / portTICK_PERIOD_MS);
  stopMotor();
  // Stop and delete this task so it doesn't run forever
  vTaskDelete(NULL);
}
void TaskLineFollower(void *pvParameters)
{
  (void)pvParameters;
  const TickType_t delayMs = 50 / portTICK_PERIOD_MS;
  // Math
  int lastError = 0; // store last seen direction (negative = left, positive = right)
  for (;;)
  {
    int d1 = digitalRead(S1);
    int d2 = digitalRead(S2);
    int d3 = digitalRead(S3);
    int d4 = digitalRead(S4);
    int d5 = digitalRead(S5);
    // Sensors are active LOW (LOW = on line). Map to boolean 1 = on line.
    int v1 = (d1 == LOW) ? 1 : 0;
    int v2 = (d2 == LOW) ? 1 : 0;
    int v3 = (d3 == LOW) ? 1 : 0;
    int v4 = (d4 == LOW) ? 1 : 0;
    int v5 = (d5 == LOW) ? 1 : 0;
    int seen = v1 + v2 + v3 + v4 + v5;
    if (seen == 0)
    {
      // Line lost: perform a short search turn based on lastError instead of stopping
      Serial.println("Line lost -> searching");
      // If unknown direction (lastError == 0) try turning left first
      if (lastError <= 0)
      {
        runLeft(); // gentle left turn
      }
      else
      {
        runRight(); // gentle right turn
      }
      vTaskDelay(120 / portTICK_PERIOD_MS); // short turn then re-check
      stopMotor();
      vTaskDelay(30 / portTICK_PERIOD_MS); // allow sensors to stabilize
      continue;
    }
    // Weighted error: left negative, right positive
    int error = (-2 * v1) + (-1 * v2) + (0 * v3) + (1 * v4) + (2 * v5);
    lastError = error;    // update last seen direction
    if (error == 0 && v3) // centered
    {
      runForward();
      Serial.println("Line centered -> forward");
    }
    else if (error < 0) // line detected on left sensors
    {
      runLeft();
      Serial.print("Turn left, error=");
      Serial.println(error);
    }
    else if (error > 0) // line detected on right sensors
    {
      runRight();
      Serial.print("Turn right, error=");
      Serial.println(error);
    }
    vTaskDelay(delayMs);
  }
}