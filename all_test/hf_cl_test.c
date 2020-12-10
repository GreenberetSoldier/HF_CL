
#include "System.h"
#include "uCUnit-v1.0.h"
#include "gate_control.h"
#include "gate_control.c"


int gpioCloseSensorValue;
int gpioOpenSensorValue;


static void test_gateInit_0(void){

    gpioCloseSensorValue = 0;
    gpioOpenSensorValue = 0;

    UCUNIT_TestcaseBegin("test_gateInit_0");
    UCUNIT_WriteString("Checking Init() for following get_gpio() results:\n");
    UCUNIT_WriteString("get_gpio(pin_sense_closed) == "); UCUNIT_WriteInt(gpioCloseSensorValue); UCUNIT_WriteString("\n");
    UCUNIT_WriteString("get_gpio(pin_sense_open) == ");   UCUNIT_WriteInt(gpioOpenSensorValue);  UCUNIT_WriteString("\n");
    gateInit();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(currentState, stuck);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

static void test_gateInit_1(void){

    gpioCloseSensorValue = 0;
    gpioOpenSensorValue = 1;

    UCUNIT_TestcaseBegin("test_gateInit_1");
    UCUNIT_WriteString("Checking Init() for following get_gpio() results:\n");
    UCUNIT_WriteString("get_gpio(pin_sense_closed) == "); UCUNIT_WriteInt(gpioCloseSensorValue); UCUNIT_WriteString("\n");
    UCUNIT_WriteString("get_gpio(pin_sense_open) == ");   UCUNIT_WriteInt(gpioOpenSensorValue);  UCUNIT_WriteString("\n");
    gateInit();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(currentState, opened);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

static void test_gateInit_2(void){

    gpioCloseSensorValue = 1;
    gpioOpenSensorValue = 0;

    UCUNIT_TestcaseBegin("test_gateInit_2");
    UCUNIT_WriteString("Checking Init() for following get_gpio() results:\n");
    UCUNIT_WriteString("get_gpio(pin_sense_closed) == "); UCUNIT_WriteInt(gpioCloseSensorValue); UCUNIT_WriteString("\n");
    UCUNIT_WriteString("get_gpio(pin_sense_open) == ");   UCUNIT_WriteInt(gpioOpenSensorValue);  UCUNIT_WriteString("\n");
    gateInit();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(gateGetState(), closed);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

static void test_gateInit_3(void){

    gpioCloseSensorValue = 1;
    gpioOpenSensorValue = 1;

    UCUNIT_TestcaseBegin("test_gateInit_3");
    UCUNIT_WriteString("Checking Init() for following get_gpio() results:\n");
    UCUNIT_WriteString("get_gpio(pin_sense_closed) == "); UCUNIT_WriteInt(gpioCloseSensorValue); UCUNIT_WriteString("\n");
    UCUNIT_WriteString("get_gpio(pin_sense_open) == ");   UCUNIT_WriteInt(gpioOpenSensorValue);  UCUNIT_WriteString("\n");
    gateInit();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(currentState, stuck);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

static void test_gateOpen_0(void){

    currentState = closed;
    enum state ret;

    UCUNIT_TestcaseBegin("test_gateOpen_0");
    UCUNIT_WriteString("Checking gateOpen() for currentState == closed\n");
    ret = gateOpen();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(currentState, opening);
    UCUNIT_CheckIsEqual(ret, IN_PROGRESS);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

static void test_gateOpen_1(void){

    currentState = opened;
    enum state ret;

    UCUNIT_TestcaseBegin("test_gateOpen_1");
    UCUNIT_WriteString("Checking gateOpen() for currentState == opened\n");
    ret = gateOpen();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(currentState, opened);
    UCUNIT_CheckIsEqual(ret, OK_COMPLETED);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

static void test_gateOpen_2(void){

    currentState = closing;
    enum state ret;

    UCUNIT_TestcaseBegin("test_gateOpen_2");
    UCUNIT_WriteString("Checking gateOpen() for currentState == closing\n");
    ret = gateOpen();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(currentState, opening);
    UCUNIT_CheckIsEqual(ret, IN_PROGRESS);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

static void test_gateOpen_3(void){

    currentState = opening;
    enum state ret;

    UCUNIT_TestcaseBegin("test_gateOpen_2");
    UCUNIT_WriteString("Checking gateOpen() for currentState == closing\n");
    ret = gateOpen();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(currentState, opening);
    UCUNIT_CheckIsEqual(ret, IN_PROGRESS);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

static void test_gateOpen_4(void){

    currentState = stuck;
    enum state ret;

    UCUNIT_TestcaseBegin("test_gateOpen_2");
    UCUNIT_WriteString("Checking gateOpen() for currentState == closing\n");
    ret = gateOpen();
    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual(currentState, stuck);
    UCUNIT_CheckIsEqual(ret, STUCK);
    UCUNIT_ChecklistEnd();
    UCUNIT_TestcaseEnd();
}

void RunTests(void){
    test_gateInit_0();
    test_gateInit_1();
    test_gateInit_2();
    test_gateInit_3();

    test_gateOpen_0();
    test_gateOpen_1();
    test_gateOpen_2();
    test_gateOpen_3();
    test_gateOpen_4();
    UCUNIT_WriteSummary();
}

int main(void)
{
    //UCUNIT_Init();
    UCUNIT_WriteString("\n**************************************");
    UCUNIT_WriteString("\nName:     ");
    UCUNIT_WriteString("Gate control application");
    UCUNIT_WriteString("\nCompiled: ");
    UCUNIT_WriteString(__DATE__);
    UCUNIT_WriteString("\nTime:     ");
    UCUNIT_WriteString(__TIME__);
    UCUNIT_WriteString("\nVersion:  ");
    UCUNIT_WriteString(UCUNIT_VERSION);
    UCUNIT_WriteString("\n**************************************");
    RunTests();
    //UCUNIT_Shutdown();

    return 0;
}


//overriding external api functions with own implementation for testing purpose

int  get_gpio(int pin){
    if (pin == pin_sense_closed) //closed-sensor
        return gpioCloseSensorValue;
    else                         //opened-sensor
        return gpioOpenSensorValue;
}

void set_gpio(int pin, int val){
    //nothing
}