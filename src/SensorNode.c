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
			setAlarm(sensor, True);
			setTreshold(sensor, UPPER_TRESHOLD, LOWER_TRESHOLD);
	} else setAlarm(sensor, False);

	if (sensor->ID == 2) sensor->confidential=True;
	else sensor->confidential=False;
}


inline void setPriority (Sensor * sensor, uint8_t priority) {
	sensor->priority=priority;
}

inline uint8_t getPriority (Sensor sensor) {
	return sensor.priority;
}

void setReadPeriod (Sensor * sensor, uint32_t read_period) {
	uint32_t physical_period = 0;

	if (getPeriod(sensor->ID, &physical_period) != OP_OK) {
		// scrive sul log che c'è stato un accesso errato in lettura
	}

	// il controllo si deve fare solo per sensori SINCRONI
	if (physical_period > 0 && read_period < physical_period)
		sensor->read_period_ms = physical_period;
	else sensor->read_period_ms = read_period;
}

inline uint32_t getReadPeriod (Sensor sensor) {
	return sensor.read_period_ms;
}

inline void setAlarm (Sensor * sensor, Bool alarm) {
	sensor->alarm = alarm;
}

inline Bool isAlarm (Sensor sensor) {
	return sensor->alarm;
}

inline void setTreshold (Sensor * sensor, Value_t upper, Value_t lower) {
	sensor->treshold.HighThreshold = upper;
	sensor->treshold.LowThreshold = lower;
}

inline Bool verifyTreshold (Sensor * sensor, Value_t value) {
	if ( value >= sensor->treshold.LowThreshold &&
			value <= sensor->treshold.HighThreshold) return True;
	else return False;
}

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

inline uint8_t getSensorID (uint8_t index) {
	return this.sensor[index]->ID;
}
