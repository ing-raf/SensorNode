// task.h
//
// Version: 0.1
//
// Changelog:
//

#include "FreeRTOS.h"
#include "SensorNodeConfig.h"

#include "task.h"
#include "ApplicationCommonConfig.h"
#include "GSI.h"
#include "SensorNode.h"

void asyncRequestManage (void *queue) {

	Message message;

	while(1) {

		message.ID = listen (ASE);	//implementato dal livello rete
		message.data= readData(message.ID);
		if(xQueueSend(queue, (void*)&message, portMAX_DELAY) == errQUEUE_FULL){
			//scrive nel file di log che la coda è piena e il pacchetto quindi
			//è andato perduto
		}

	}

}

void syncSensorManage (void *sync_init_ptr) {

	Sync_Init sync_init = *((Sync_Init *)sync_init_ptr);
	//payload del pacchetto proveniente dal livello trasporto
	Message message;
	portTickType lastWakeTime;

	// inizializzo il conteggio del tick corrente per poi eseguire il task
	// periodicamente ogni tot tick
	lastWakeTime = xTaskGetTickCount();

	message.ID=sync_init.ID;

	while(1) {

		message.data = readData(sync_init.ID);
		if (isAlarm(sync_init.ID))
			if (message.data.value < getThreshold (sync_init.ID).LowThreshold || message.data.value > getThreshold (sync_init.ID).HighThreshold)
				//il valore del sensore esce dall'intervallo
				if((xQueueSend(sync_init.max_priority_queue, (void*)&message, portMAX_DELAY)) == errQUEUE_FULL) {
					//scrive nel file di log che la coda è piena e il pacchetto quindi
					//è andato perduto
				}

		else
			// il valore rientra nell'intervallo o il sensore non richiede il controllo
			if((xQueueSend(sync_init.own_queue, (void*)&message, portMAX_DELAY)) == errQUEUE_FULL) {
				//scrive nel file di log che la coda è piena e il pacchetto quindi
				//è andato perduto
			}

		// implementa la periodicità del task
		vTaskDelayUntil(&lastWakeTime, (sync_init.period/portTICK_RATE_MS));
	}

}


void sendOnNetwork (void * queuePtr) {

	xQueueHandle queue[] = (xQueueHandle[]) queuePtr;
	Message *message;
	Packet packet;
	// dichiarazione di packet

	while(1) {

		if(popMessage(message, queue) == True){
			packet = makePacket(message);

			if(isConfidentiality(message->ID)==True)
				packet = encrypt(packet);

			network_send(packet, class(getPriority(message->ID)));

		}
	}
}

void popMessage (Message *message, xQueueHandle queue[]){

	int priority;

	while (uxQueueMessageWaiting(queue(priority)) != 0 &&  priority < NUM_PRIORITIES)
		priority++;

	xQueueReceive(queue(priority), (void*) message, portMAX_DELAY);

}

//definire tipo del pacchetto
Packet makePacket(Message message){
	Packet packet;

	packet.message = message;
	packet.ID_sensor_node = getID();
	packet.priority = getPriority(message.ID);

	return packet;
}


