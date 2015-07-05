// task.h
//
// Version: 0.1
//
// Changelog:
//


#ifndef TASK_H_
#define TASK_H_

void asyncRequestManage (void *);
void syncSensorManage (void *);
void sendOverNetwork (void *);
void popMessage (Message*, xQueueHandle[]);
Packet makePacket (Message);
//definire tipo del pacchetto

#endif /* TASK_H_ */
