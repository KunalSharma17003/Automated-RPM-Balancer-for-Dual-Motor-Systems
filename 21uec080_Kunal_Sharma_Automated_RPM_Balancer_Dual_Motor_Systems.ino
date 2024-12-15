#include "Arduino_FreeRTOS.h"
#include "queue.h"
#define left 10
#define right 11
#define base 35 
TaskHandle_t task1_handler;
TaskHandle_t task2_handler;
TaskHandle_t task3_handler;
TaskHandle_t task4_handler;
QueueHandle_t Queue1;
QueueHandle_t Queue2;

void Enc_Right_Read_Task_1(void* params) {
  // This task takes input from left wheel optical encoder and push the values in queue

  bool prv = false;
  int cnt1 = 0;
  bool value;
  while (1) {
    value = digitalRead(9);
    if ((value == 1) && (value != prv)) {
      cnt1++;
    }
    xQueueSend(Queue1, &cnt1, 0);
    prv = value;
    taskYIELD();  
  }
  
}
void Enc_Left_Read_Task_1(void* params) {
    // This task takes input from left wheel optical encoder and push the values in queue

  bool prv = false;
  int cnt2 = 0;
  bool value;
  while (1) {
    value = digitalRead(8);
    if ((value == 1) && (value != prv)) {
      cnt2++;
    }
    xQueueSend(Queue2, &cnt2, 0);
    prv = value;
    taskYIELD();
  }
}
void button_light_task_3(void* params) {
 /*
    This task check for the obstacle by taking input from IR Proximity sensor.
    if there is obstacle , all the wheels are stopped and other tasks are suspended.
    else 
 */
  bool sus=0;
  while (1) {
    if (digitalRead(5) == 1 && !sus) 
    {
      sus=1;
      vTaskSuspend(task1_handler);
       vTaskSuspend(task2_handler);
        vTaskSuspend(task4_handler);
        analogWrite(11,0);
        analogWrite(10,0);

    } 
    else if(digitalRead(5)==0 && sus)
     {
      sus=0;
      vTaskResume(task1_handler);
      vTaskResume(task2_handler);
      vTaskResume(task4_handler);
    }
    // Serial.print("Task-3:");
    // Serial.println(uxTaskGetStackHighWaterMark(task3_handler));
    taskYIELD();
  }
}

void Motor_Speed_Control_Task_4(void* params) {
   /* This task takes values from the queue and adjust the 
      speed of both motors by adjusting the PWM values
  */
  int temp1, temp2;  // right , left
  while (1) {
    if (xQueueReceive(Queue1, &temp1, portMAX_DELAY) == pdTRUE && xQueueReceive(Queue2, &temp2, portMAX_DELAY) == pdTRUE) {
      // Serial.println(temp1);
      // Serial.println(temp2);
      int d=temp1-temp2; // right-left
      if(temp1 >temp2 ){
        int diff=temp1-temp2;
        analogWrite(left, min(250,base+diff*7));
        analogWrite(right,max(0,base-diff*7));
        // analogWrite(left,35);
      }
      else{
        int diff=temp2-temp1;
        // analogWrite(right,35);
        analogWrite(right, min(250,base+diff*7));
        analogWrite(left,max(0,base-diff*7));
      }
      //Serial.println(d);
    }
    // Serial.print("Task-4:");
    // Serial.println(uxTaskGetStackHighWaterMark(task4_handler));
    taskYIELD();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(13, OUTPUT);
  pinMode(5, INPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  pinMode(10, OUTPUT); // left side
  pinMode(11, OUTPUT); // right side
  analogWrite(10, base);
  analogWrite(11, base);
  Queue1 = xQueueCreate(1, sizeof(int));
  Queue2 = xQueueCreate(1, sizeof(int));
  //  attachInterrupt(digitalPinToInterrupt(8),Enc_Read_Task_1, RISING);
  xTaskCreate(Enc_Right_Read_Task_1, "Task-1", 128, NULL, 1, &task1_handler);
  xTaskCreate(Enc_Left_Read_Task_1, "Task-2", 128, NULL, 1, &task2_handler);
   xTaskCreate(button_light_task_3, "Task-3", 128, NULL, 1, &task3_handler);
  xTaskCreate(Motor_Speed_Control_Task_4, "Task-4", 128, NULL, 1, &task4_handler);

  if (task1_handler != NULL && Queue1 != NULL) {
    Serial.println("Task-1 Created Sucessfully");
  } else {
    Serial.println("Task-1 not Created Sucessfully");
  }

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
}