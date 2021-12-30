#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdlib.h>
#include <time.h>
#include <Servo.h>

#include "header.h"

void setup() {

  /*
     Serial print
  */
  Serial.begin(9600);
  while (!Serial);

  randomSeed(time(0));
  Global_Queue_Target_Type = xQueueCreate(10, sizeof(int));
  Global_Queue_Changes_to_Score = xQueueCreate(10, sizeof(int)); 
  Global_Queue_Curr_Score = xQueueCreate(10, sizeof(int));
  myservo.attach(MOTOR_PIN);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  xTaskCreate(
    target_type,
    "Choose Next Target Type",  // A name just for humans
    512,      // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,     // Parameter to pass to function
    2,        // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &TaskHandle_1);    // Task handle

  xTaskCreate(
    target_appear,
    "..",  // A name just for humans
    512,      // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,     // Parameter to pass to function
    2,        // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &TaskHandle_2);    // Task handle

  xTaskCreate(
    LED_on,
    "Turn on the Target LED",  // A name just for humans
    512,      // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,     // Parameter to pass to function
    2,        // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &TaskHandle_3);

  xTaskCreate(
    human_target,
    "Choose Next Target Type",  // A name just for humans
    512,      // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,     // Parameter to pass to function
    2,        // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &TaskHandle_4);

  xTaskCreate(
    zombie_target,
    "Choose Next Target Type",  // A name just for humans
    512,      // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,     // Parameter to pass to function
    2,        // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &TaskHandle_5);

  xTaskCreate(
    track_score,
    "Keeps Track of Current Score",  // A name just for humans
    512,      // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,     // Parameter to pass to function
    2,        // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    NULL);
  /*
    xTaskCreate(
      test_target_type,
      ".",  // A name just for humans
      512,      // This stack size can be checked & adjusted by reading the Stack Highwater
      NULL,     // Parameter to pass to function
      2,        // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      NULL);*/
}

void loop() {
  // put your main code here, to run repeatedly:

}
