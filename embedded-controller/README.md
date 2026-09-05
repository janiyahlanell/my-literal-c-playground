 # FreeRTOS Thermal controller & Fan Simulation

 a real-time embedded C application running on an ESP32 simulator (wokwi) using FreeRTOS to read temperature data and automatically adjusts a fan speed state based on thermal limits.

 My first project playing with hardware simulators. My biggest hurdle was actually knowing where to begin. I know the C language and i wanted to apply it into something i was actually interested in which is hardware. 

 I first found out about FreeRTOS and then learned 3 main concepts: Tasks, Queues / API functions, and Software Timers & Interrupts.
 This led me to use Queues (QueueHandle_t) as opposed to global variables to prevent data corruption when/if 2 tasks try to read the same variable

 I was also able to use vTaskDelay instead of standard while loop to prevent the cpu running 100% thus allowing the cpu to actually rest

## What It Does
* **Sensor Task:** Generates simulated temperature readings and pushes them into FreeRTOS queue every second
* **Fan Task:** Listens to the queue and switches teh fan state to HIGH (100%) if the temperature goes over 40C, or LOW(30%) when it's under.
* **Thread Safety:** uses a FreeRTOS queue ('xQueueSend' / 'xQueueReceive') to pass data cleanly

## Tools used
* **Language:** C
* **Framework:** ESP-IDF
* **RTOS:** FreeRTOS (Tasks & Queues)
* **Simulator:** Wokwi

## Project Layout
- task logic
- queue creation
- application entry point

## How to test
1. open the project in the "wokwi esp-idf simulator: https://wokwi.com/projects/new/esp-idf-esp32
2. past the contents of main into the editor
3. Click **Play** to run the code and check the terminal logs

## Known bugs
- I'm aware that the vscode editor gave errors because a standard laptop doesn't have microcontroller libraries pre-installed
