// Include standard c libraries for printing text
#include <stdio.h>

//include FreeRTOS core and task headers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static QueueHandle_t temp_queue = NULL; // creates a global handle that stores the reference address of our queue so both tasks can access it safely


// now we'll focus on the sensor task function
void temp_sensor_task(void *pvParameters){ // all task function is RTOS must accept a generic void pointer
  float simulated_temp = 25.0;
  while (1){ // while true
    simulated_temp += 1.5;
    if(simulated_temp > 50.0){
      simulated_temp = 25.0;
    }
     //drops teh simulated temps into the freertos mailbox(queue)
     xQueueSend(temp_queue, &simulated_temp, portMAX_DELAY);
    // portMAX_DELAY tells FreeRTOS to pause this task indefinietly if the queue ever gets full
    
    // this function pauses thsi specific task because if you don't put a delay in an infinite loop
    // on a microcontroller, teh task will run millions of times per second and lock up 100% of teh rpocessor core
    // calling this function oputs a delay for 1000 milliseconds
     vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


// function signature for our consumer/controller task
void fan_control_task(void *pvParameters){
  float received_temp = 0.0; // empty container

  while(1){
    if(xQueueReceive(temp_queue, &received_temp, portMAX_DELAY)){ // function acts hwne it recieves data
      if(received_temp > 40.0){
        printf("[ALERT] Temp High: %.1f C | Fan state: HIGH(100%%)\n", received_temp);
      }else{
        printf("[OK] Temp Normal: %.1f C | Fan state: LOW (30%%)\n", received_temp);
      }
    }
  }
}

void app_main(void){
  temp_queue = xQueueCreate(5, sizeof(float));

  if(temp_queue != NULL){
    xTaskCreate(temp_sensor_task, "SensorTask", 2048, NULL, 2, NULL);
    xTaskCreate(fan_control_task, "FanTask", 2048, NULL, 1, NULL);
  }
}

  
