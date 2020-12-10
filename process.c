#include "gate_control.h"
#include <stdio.h>
#include <time.h>

#define REPAIR_PERIOD (2*(MAX_CLOSING_TIME));   // time interval between repair attempts

//operation request flags
volatile char request_open;
volatile char request_close;


int main(){

    request_open = 0;
    request_close = 0;
    time_t repairStart = 0;   //initial zero value will cause immediate resolve attempt in the main loop if gate is stuck after init

    gateInit();

    while (1){

        if (gateGetState() == opening || gateGetState() == closing)
            gateCheckFinish();

        if (request_open){
            gateOpen();
            request_open = 0;
        }
        
        if (request_close){
            gateClose();
            request_close = 0;
        }
        
        if ((gateGetState() == stuck) && ((time(NULL) - repairStart) > REPAIR_PERIOD)) {
            repairStart = time(NULL);
            gateResolveStuck();
        }
    }

    return 0;
}
