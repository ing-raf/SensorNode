// Sensor Node
//
// Version: 0.1
//
// Changelog
//	-> Born file
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#include "GSI.h"
#include "SensorNode.h"
#include "SensorNodeConfig.h"
#include "main.h"

int main(int argc, char* argv[]) {
	int i = 0;	// indice usato per i cicli for
	int n = 0;	// variabile per il numero di sensori
	xQueueHandle queue[NUM_PRIORITIES];
	Sync_Init sync_sensor;

	initNode();

	initSensors();

//	initNetwork();		funzione fornita dal livello rete

	if ( join(getID()) == 0) { 	// supponendo sia questa la firma
		// scrive nel log che si e' verificato un errore di autenticazione
		while(1);
	}

	for (i = 0; i < NUM_PRIORITIES; i++)
		queue[i] = xQueueCreate(MAX_QUEUE_LENGTH, sizeof(Message));

	if (xTaskCreate(asyncRequestManage,// nome della funzione
					"Gestione richieste asincrone",
					configMINIMAL_STACK_SIZE,
					queue(1), // parametri della funzione: queue(1)
					3) != pdTRUE) {
		// scrive nel log che si `e verificato un errore di gestione della memoria
		while(1);
	}

	n = getNumSensors();

	for (i = 0; i < n; i++) {

		if (getPeriod(getSensorID(i)) > 0) {

			sync_sensor.ID = getSensorID(i);
			sync_sensor.period = getPeriod(getSensorID(i));

			if (xTaskCreate(syncSensorManage,// nome della funzione
							"Task di gestione di un sensore sincrono ",
							configMINIMAL_STACK_SIZE,
							(void *)&sync_sensor, // parametri della funzione
							2) != pdTRUE) {
				// scrive nel log che si `e verificato un errore di gestione della memoria
				while(1);
			}

		}
	}

	if (xTaskCreate(sendOverNetwork,// nome della funzione
					"Task per l'invio dei messaggi",
					configMINIMAL_STACK_SIZE,
					(void *)queue, // parametri della funzione
					1) != pdTRUE) {
		// scrive nel log che si `e verificato un errore di gestione della memoria
		while(1);
	}

	vTaskStartScheduler();

	while (1);
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
