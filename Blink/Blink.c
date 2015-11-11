/* Author: Kizito Nkurikiyeyezu
* Created: 10-Nov-2015
* Compiler:  AVR/GNU C Compiler
* File Version: 0.1
* Status: Initial Release
* Descriptions: 
            FreeRTOS is a popular[1] real-time operating system kernel for embedded devices, 
			that has been ported to 35 microcontrollers. It is distributed under the GPL with an optional exception.
		    The exception permits users' proprietary code to remain closed source while maintaining the kernel itself 
			as open source, thereby facilitating the use of FreeRTOS in proprietary applications.
			(source: https://en.wikipedia.org/wiki/FreeRTOS).
			This repository is a port of the FreeRTOS to the popular ATmega329P microcontroller that is used in Arduino Uno.
  Copyright:
           This program is free software: you can redistribute it and/or modify
           it under the terms of the GNU General Public License as published by
           the Free Software Foundation, either version 3 of the License, or
           (at your option) any later version.
           
           This program is distributed in the hope that it will be useful,
           but WITHOUT ANY WARRANTY; without even the implied warranty of
           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
           GNU General Public License for more details.
           
           You should have received a copy of the GNU General Public License
           along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
*/

#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>
#include <stdbool.h> // For true and false
static void vBlinkLed(void* pvParameters);
#define LED_TASK_PRIORITY   (tskIDLE_PRIORITY)
#define LED_PIN PB0
int main(void)
{
	// Create task.
	xTaskHandle blink_handle;
	xTaskCreate
	(
	vBlinkLed,
	(signed char*)"blink",
	configMINIMAL_STACK_SIZE,
	NULL,
	LED_TASK_PRIORITY,
	&blink_handle
	);

	// Start scheduler.
	vTaskStartScheduler();

	return 0;
}
/*
The idle hook is called repeatedly as long as the idle task is running. 
It is paramount that the idle hook function does not call any API functions that could cause it to block
Note: You may find it useful to disable this method in the FreeRTOSConfig.h file. To do this,
just set the configUSE_IDLE_HOOK to 0
*/
void vApplicationIdleHook(void)
{
   // Do nothing
}

static void vBlinkLed(void* pvParameters)
{
	// Se the LED_PIN an output
	DDRB |= (1<<LED_PIN);
	while(true)
	{
		PORTB ^= (1<<LED_PIN);
		vTaskDelay(500);
	}
}
