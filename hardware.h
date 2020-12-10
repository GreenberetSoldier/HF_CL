#ifndef HARDWARE_H
#define HARDWARE_H

//set the specified output
void set_gpio(int pin, int value);
//read the specified input
int  get_gpio(int pin);


//actuator pin, closing direction
const int pin_act_close;
//actuator pin, opening direction
const int pin_act_open;


//closed state end-position sensor pin
const int pin_sense_closed = 0x0;
//open state end-position sensor pin
const int pin_sense_open = 0x1;

#endif