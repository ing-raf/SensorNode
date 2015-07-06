// SensorNode.c
//
// Version: 0.1
//
// Changelog:
//

#include "SensorNode.h"
#include "GSI.h"
#include "SensorNodeConfig.h"

Sensor_Node this;

void initSensor(Sensor * sensor) {
	/* esempio di configurazione cablata nel codice:
	 * ID 1 -> allarme
	 * ID 2 -> allarme e confidenzialità
	 * ID 3 -> niente
	 */
	if (sensor->ID < 3) {
			sensor->alarm = True;
			sensor->treshold.HighThreshold=UPPER_TRESHOLD;
			sensor->treshold.LowThreshold=LOWER_TRESHOLD;
	} else sensor->alarm = False;

	if (sensor->ID == 2) sensor->confidential=True;
	else sensor->confidential=False;
}


void setPriority (Sensor * sensor, uint8_t priority) {
	sensor->priority=priority;
}

void setReadPeriod (Sensor *, uint32_t);
uint32_t getReadPeriod (Sensor);
uint8_t getPriority (Sensor);
void setAlarm (Sensor *, Bool);
Bool isAlarm (Sensor);
void setTreshold (Sensor *, Value_t, Value_t);
Bool verifyTreshold (Value_t);

void initNode (void) {
	int i = 0;
	uint8_t * ID_Sensor_List;

	this.ID = SENSOR_NODE_ID;
	this.num_sensors = getSensorNumber(); // dobbiamo modificare con la getSensorNumbers
	this.authentication_key = SENSOR_NODE_KEY;
	this.sensor = malloc(this.num_sensors*sizeof(Sensor));

	ID_Sensor_List = malloc(this.num_sensors*sizeof(uint8_t));

	getIDSensorList(ID_Sensor_List);

	for (i = 0; i < this.num_sensors; i++) {
		this.sensor[i].ID = ID_Sensor_List[i];
		initSensor(&(this.sensor[i]));
	}
}

inline uint16_t getID (void) {
	return this.ID;
}

inline uint8_t getNumSensors (void) {
	return this.num_sensors;
}
