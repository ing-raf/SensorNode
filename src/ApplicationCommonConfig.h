// ApplicationCommonConfig.h
//
// Version: 0.1
//
// Changelog:
//

#ifndef APPLICATIONCOMMONCONFIG_H_
#define APPLICATIONCOMMONCONFIG_H_


typedef enum {
	Best_Effort = 0,
	Assured_Forwarding,
    Real_Time,
} Service_Class;

//-------- Known ports to Protocols Mapping ----------

#define ASE 1 //Asyncronous Syncronous Exchange

//-------- Priorities to Service Classes Mapped -----------

Service_Class class[] = {
		Assured_Forwarding, 	// Service Class for priority level 0
        Real_Time				// Service Class for priority level 1
};

//--------- User mustn't modify from this point --------//

const int MAPPED_PRIORITIES = sizeof(class)/sizeof(class[0]);

Service_Class getClass (priority) {

    if (priority < MAPPED_PRIORITIES)
        return class[priority];
    else
    	return Best_Effort;
}

#endif /* APPLICATIONCOMMONCONFIG_H_ */
