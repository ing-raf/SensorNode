// ApplicationCommonConfig.h
//
// Version: 0.1
//
// Changelog:
//

#ifndef APPLICATIONCOMMONCONFIG_H_
#define APPLICATIONCOMMONCONFIG_H_

#include "TL_API.h"

//-------- Known ports to Protocols Mapping ----------

#define JOIN 0 //
#define ASE 1 //Asyncronous Syncronous Exchange

//-------- Priorities to Service Types Mapped -----------

ServiceType class[] = {
		Guaranteed, 	// Service Type for priority level 0
        Real_Time		// Service Type for priority level 1
};

//--------- User mustn't modify from this point --------//

const int MAPPED_PRIORITIES = sizeof(class)/sizeof(class[0]);

ServiceType getClass (priority) {

    if (priority < MAPPED_PRIORITIES)
        return class[priority];
    else
    	return Best_Effort;
}

#endif /* APPLICATIONCOMMONCONFIG_H_ */
