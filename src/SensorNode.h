// SensorNode.h
//
// Version: 0.1
//
// Changelog:
//

#ifndef SENSOR_NODE_H
#define SENSOR_NODE_H

// Particolarizzare
#define UPPER_TRESHOLD 10
#define LOWER_TRESHOLD 0

#include "GSI.h"

typedef struct {
    Value_t LowThreshold;
    Value_t HighThreshold;
} Threshold_Interval;

typedef struct {
	uint8_t				ID;
	uint32_t	  		read_period_ms;
	uint8_t		  		priority;
	Bool 		  		alarm;
	Threshold_Interval	treshold;
	Bool				confidential;
} Sensor;

typedef struct {
	uint16_t ID;
	uint8_t num_sensors;
	int authentication_key;
	Sensor sensor[];
} Sensor_Node; // contiene i fatti di questo nodo sensore


typedef struct {
	uint8_t ID;
	Data data;
} Message;

typedef struct {
	uint8_t priority;
	uint8_t ID_sensor_node;
	Message message;
} Packet;

#endif // SENSOR_NODE_H

void initSensor(Sensor *); // configura il singolo sensore
void setReadPeriod (Sensor *, uint32_t);
uint32_t getReadPeriod (Sensor);
void setPriority (Sensor *, uint8_t);
uint8_t getPriority (Sensor);
void setAlarm (Sensor *, Bool);
Bool isAlarm (Sensor);
void setTreshold (Sensor *, Value_t, Value_t);
Bool verifyTreshold (Sensor *, Value_t);
void setAlarm (Sensor *, Bool);
Bool isAlarm (Sensor);

void initNode(void); // inizializza questo nodo sensore
uint16_t getID(void); // ritorna l' ID di questo nodo sensore
uint8_t getNumSensors(void); // ritorna il numero di sensori del nodo
uint8_t getSensorID (uint8_t); // ritorna l'ID dell'i-esimo sensore della lista
