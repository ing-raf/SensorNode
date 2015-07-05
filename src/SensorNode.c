// SensorNode.c
//
// Version: 0.1
//
// Changelog:
//

#include "SensorNode.h"

#include "SensorNodeConfig.h"

Sensor_Node this;

void initNode (void) {
	this.ID = SENSOR_NODE_ID;
	this.num_sensors = SENSOR_NODE_NUMSENSORS;
	this.authentication_key = SENSOR_NODE_KEY;
}

inline uint8_t getID (void) {
	return this.ID;
}

inline uint8_t getNumSensors (void) {
	return this.num_sensors;
}
