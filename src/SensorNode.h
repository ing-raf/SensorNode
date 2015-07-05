// SensorNode.h
//
// Version: 0.1
//
// Changelog:
//

#ifndef SENSOR_NODE_H
#define SENSOR_NODE_H

#include "GSI.h"

typedef struct {
	uint8_t ID;
	uint8_t num_sensors; // dobbiamo modificare con la getSensorNumber
	int authentication_key;
} Sensor_Node; // contiene i fatti di questo nodo sensore

typedef struct {
	int ID;
	Data data;
} Message;

typedef struct {
	int priority;
	int ID_sensor_node;
	Message message;
} Packet;

#endif // SENSOR_NODE_H

void initNode(void); // inizializza questo nodo sensore
uint8_t getID(void); // ritorna l' ID di questo nodo sensore
uint8_t getNumSensors(void); // ritorna il numero di sensori del nodo
