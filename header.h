#define MOTOR_PIN   9;
#define LED_R_PIN   8;
#define LED_G_PIN   7;
#define LED_B_PIN   6;
#define SENSOR_PIN  A0;
#define HIT_TARGET  700;
#define TARGET_UP   90;
#define TARGET_DOWN 0;

enum TARGET {
  HUMAN, ZOMBIE
};

static QueueHandle_t Global_Queue_Target_Type;
static QueueHandle_t Global_Queue_Changes_to_Score;
static QueueHandle_t Global_Queue_Curr_Score;

TaskHandle_t TaskHandle_1; //target_type
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3; 
TaskHandle_t TaskHandle_4;
TaskHandle_t TaskHandle_5;
Servo myservo;


void target_type(void *pvParameters);
void target_appear(void *pvParameters);
void LED_on(void *pvParameters);
void human_target(void *pvParameters);
void zombie_target(void *pvParameters);
void track_score(void *pvParameters);
