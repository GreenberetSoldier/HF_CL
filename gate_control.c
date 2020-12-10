/********************************************************************
 * 
 * File:        gate_control.h
 * Author:      Will Gabor
 * Date:        2020.12.08.
 * Project:     Embedded gate control application in C
 * Description: Program is written as part of job applying procedure
 * version:     1.0
 *
 *******************************************************************/

#include <stdio.h>       // for NULL definition
#include <unistd.h>      // for sleep function
#include <time.h>        // for time functions
#include "gate_control.h"
#include "hardware.h"

/* GLOBAL VARIABLES */
enum state currentState;
time_t start;


/* GATE CONTROL FUNCTIONS */

void gateInit(void){
    set_gpio(pin_act_close, 0);
    set_gpio(pin_act_open, 0);    
    
    if (get_gpio(pin_sense_closed) && !get_gpio(pin_sense_open))
        currentState = closed;

    else if (get_gpio(pin_sense_open) && !get_gpio(pin_sense_closed))
        currentState = opened;
    
    else
        // if inconsistent sensor state (1,1) or halfway (0,0) we assume stuck state
        // an attempt to resolve stuck state should be initiated by program
        currentState = stuck;
}

int gateOpen(void){
    
    switch (currentState){
        case opened:
            return OK_COMPLETED;
            
        case opening:
            return IN_PROGRESS;
            
        case closing:
            set_gpio(pin_act_close, 0);
            sleep(STOPPING_TIME);

        case closed:
            set_gpio(pin_act_open, 1);
            start = time(NULL);
            currentState = opening;
            return IN_PROGRESS;

        case stuck:
            return STUCK;
            
        default:
            // unforeseen state, unknown error - should not occur
            return FUNCTION_ERROR;
    }
}

int gateClose(void){

    switch (currentState){
        case closed:
            return OK_COMPLETED; 
            
        case closing:
            return IN_PROGRESS;
            
        case opening:
            set_gpio(pin_act_open, 0);
            sleep(STOPPING_TIME);

        case opened:
            set_gpio(pin_act_close, 1);
            start = time(NULL);
            currentState = closing;
            return IN_PROGRESS;

        case stuck:
            return STUCK;
            
        default:
            // unforeseen state, unknown error - should not occur
            return FUNCTION_ERROR;  
    }
}

int gateCheckFinish(void){
  
    switch (currentState){
        case closed:
        case opened:
            return OK_COMPLETED;
            
        case closing:

            if (get_gpio(pin_sense_closed)){
                set_gpio(pin_act_close, 0);
                currentState = closed;
                return OK_COMPLETED;
            }
            else if ((time(NULL) - start) > MAX_CLOSING_TIME){
                set_gpio(pin_act_close, 0);
                currentState = stuck;
                return STUCK;
            }
            else
                //closing in progress, within time limit
                return IN_PROGRESS;
        
        case opening:

            if (get_gpio(pin_sense_open)){
                set_gpio(pin_act_open, 0);
                currentState = opened;
                return OK_COMPLETED;
            }
            else if ((time(NULL) - start) > MAX_OPENING_TIME){
                set_gpio(pin_act_open, 0);
                currentState = stuck;
                return STUCK;
            }
            else
                //opening in progress, within time limit
                return IN_PROGRESS;
        
        case stuck:
                return STUCK;
            
        default:
            // unforeseen state, unknown error        
            return FUNCTION_ERROR;
    }
}

enum state gateGetState(void){
    return currentState;
}

void gateResolveStuck(void){
    // for resolving stuck state we currently try to close
    // if this doesn't help, state will become stuck again after MAX_CLOSING_TIME

    set_gpio(pin_act_open, 0);
    set_gpio(pin_act_close, 0);
    sleep(STOPPING_TIME);
    currentState = opened;
    gateClose();

}