/*
===============================================================================
 Name        : main.c
 Author      : Carlos Miguens
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// TODO: insert other include files here
/*Includes del FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"

/*Includes de la C-API*/
#include "GPIO.h"
#include "lpc_176X_PinNames.h"
#include "lpc_176X_PeriphNames.h"


GPIO led;
GPIO pulsador;

xQueueHandle cola;

enum debounceStates {
		NO_OPRIMIDO,
		ANTIRREBOTE,
		VALIDAR,
		OPRIMIDO
};


portTickType contadorTiempoOprimido = -1, contadorTiempoEncendido = -1, time = -1;
volatile portTickType tiempoOprimido;

void taskPulsador(void * pvParameters)
{
	uint8_t state = NO_OPRIMIDO;

	while(1)
	{
		switch(state)
		{
			case NO_OPRIMIDO:
				if(isActivo(&pulsador))
				{
					contadorTiempoOprimido = 0;
					state = ANTIRREBOTE;
					vTaskDelay(20/portTICK_RATE_MS);
				}
				else
				{
					vTaskDelay(100/portTICK_RATE_MS);
				}
				break;
			case ANTIRREBOTE:
				if(isActivo(&pulsador))
				{
					state = OPRIMIDO;
				}
				else
				{
					state = NO_OPRIMIDO;
				}
				break;
			case OPRIMIDO:
				if(!isActivo(&pulsador))
				{
					tiempoOprimido = contadorTiempoOprimido;
					xQueueSend( cola, tiempoOprimido, portMAX_DELAY);
					state = NO_OPRIMIDO;
				}
				break;
			default:
				break;
		}
	}
}
int main(void)
{

	xQueueCreate(10, sizeof(portTickType));
	//Creación de las tareas
	xTaskCreate(	taskPulsador,
					(const signed char * const)"taskPulsador",
					configMINIMAL_STACK_SIZE,
					NULL,
					tskIDLE_PRIORITY+1,
					NULL );

	//Inicio el Scheduler
	vTaskStartScheduler();

	while(1);
}

void vApplicationTickHook ( void )
{
	portBASE_TYPE xTaskWokenByReceive = pdFALSE;

	if(contadorTiempoOprimido >= 0)
		contadorTiempoOprimido++;


	if (xQueueReceiveFromISR(cola, &time, &xTaskWokenByReceive))
	{
		contadorTiempoEncendido = time;
		Activar(&led);
	}

	if(contadorTiempoEncendido > 0)
	{
		contadorTiempoEncendido--;
	} else {
		Pasivar(&led);
	}

}

void vApplicationIdleHook ( void )
{
	__ASM volatile ("wfi");
}



