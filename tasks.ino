// 1st queue to keep track of player score
// 2nd queue to choose human/zombie

// 1. decide whether human/zombie
// 2. program reads the queue and do the following tasks
//    for both:
//      use servo motor to make the target visiable 0 -> 90
//      light up led light
//    if human:
//      - green light
//      -
//    if zombie
//      - red light


/* this function chooses whether the next target will be a
  human or a zombie. It creates a random integer between 0-4and if
  it's 0 the target will be human, otherwise, zombie.

  After it determines the target type, the function will queue the
  data
*/
void target_type(void *pvParameters) {
  enum TARGET next_target;
  int random_num;

  while (1) {
    random_num = random(5);

    if (random_num == 0) {
      next_target = HUMAN;
    } else {
      next_target = ZOMBIE;
    }

    xQueueSendToBack(Global_Queue_Target_Type, &next_target, 0);
    vTaskSuspend(NULL);
  }
}

void target_appear(void *pvParameters) {
  while (1) {
    myservo.write(TARGET_UP);
    vTaskSuspend(NULL);
  }
}

void target_disappear(void *pvParameters) {
  while (1) {
    myservo.write(TARGET_DOWN);
    vTaskSuspend(NULL);
  }
}

void LED_on(void *pvParameters) {
  enum TARGET target;
  while (1) {
    if (xQueueRecieve(Global_Queue_Target_Type, &target, 10)) {
      vTaskResume(TaskHandle_2);
      if (target == HUMAN) {
        // green light
        RGB_color(0, 255, 0);
        vTaskResume(TaskHandle_4);
      } else {//when the target is a zombie
        // the red led would turn on
        RGB_color(255, 0, 0);
        vTaskResume(TaskHandle_5);
      }
    }
  }
}

void human_target(void *pvParameters) {
  int points_earned;
  while (1) {
    if (analogRead(SENSOR_PIN) > HIT_TARGET) {
      points_earned = -3; //player lose 3 points
      // sends the score change to the queue
      xQueueSendToBack(Global_Queue_Changes_to_Score, &points_earned, 0);
    } else {
      // rest for 3 seconds
      // if the target is not hit, earn 1 point
    }
  }

}

void zombie_target(void *pvParameters) {
  while (1) {

    // time = mili()
    // photoresistor will read the instensity of the light
    // if this value goes above some value -> it means that the player hit target
    //   - read the current score from the queue
    //   - increment the score by one
    //
    //  if the player doesnt hit the target (wait 1 for like 1 second) (if time > 1000)
    //    -player will lose 1 point
    //

    // for both cases:
    //   - update the score to the queue
    //   - put target down
  }
}

// this takes a score earned/lost values from human_target
// or zombie_target tasks and update the current score
void track_score(void *pvParameters) {
  static int score;
  int changes;
  while (1) {
    if (xQueueRecieve(Global_Queue_Changes_to_Score, &changes, 10)) {
      score += changes;
      xQueueSendToBack(Global_Queue_Curr_Score, &points_earned, 0);
    }
  }
}

/*
  void display_score(void *pvParameters) {

  }
*/

/*
   This funtion tests whether target_type generates random number
   each time it is called.
  void test_target_type(void *pvParameters) {
  enum TARGET next_target;
  while (1) {
    if (xQueueReceive(Global_Queue_Target_Type, &next_target, 0)) {
      Serial.println(next_target);
      vTaskResume(TaskHandle_1);
    }
  }
  }*/
