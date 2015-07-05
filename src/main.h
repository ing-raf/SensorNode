// main.h
//
// Version: 0.1
//
// Changelog:
//

#ifndef MAIN_H_
#define MAIN_H_

#include "FreeRTOS.h"

typedef struct {
	int ID;
	int period;
	xQueueHandle max_priority_queue;
	xQueueHandle own_queue;
} Sync_Init;


#endif /* MAIN_H_ */
