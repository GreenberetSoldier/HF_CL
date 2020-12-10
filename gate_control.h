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

#ifndef GATE_CONTROL_H
#define GATE_CONTROL_H

/* PREDEFINED VALUES */
#define MAX_OPENING_TIME (time_t)10         // time limit for opening procedure
#define MAX_CLOSING_TIME (time_t)10         // time limit for closing procedure
#define STOPPING_TIME (time_t)1             // time taking the gate to stop moving, usually according to gate's physical size

// possible gate states
enum state {opened, closed, opening, closing, stuck};

//return values of gate control functions
#define OK_COMPLETED 0
#define IN_PROGRESS 1
#define STUCK 2
#define FUNCTION_ERROR -1

/*
 * Initialize state machine and variables based on input signals
 * 
 * */
void gateInit(void);

/*
 * Start gate opening procedure
 * See return values at definitions
 * */
int gateOpen(void);

/*
 * Start gate closing procedure
 * See return values at definitions
 * */
int gateClose(void);

/*
 * Check if movement finished and set state accordingly
 * See return values at definitions
 * */
int gateCheckFinish(void);

/*
 * Get gate state
 * */
enum state gateGetState(void);

/*
 * Set gate state externally - Please use with caution!
 * */
void gateResolveStuck(void);

#endif