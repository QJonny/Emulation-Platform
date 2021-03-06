#ifndef SINUS_H
#define SINUS_H

#include "spin1_api.h"
#include "spinn_io.h"
#include "spinn_sdp.h"
#include "spin_devin.h"
#include <math.h>

// simulation constants
#define PRINT_DLY          200
#define MS 1000
#define TICK_TIME (100*MS) // in ms


typedef short int16_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;



#define M 15

#define NUMBER_OF_XCHIPS 2
#define NUMBER_OF_YCHIPS 2


#define MOTOR_MIN 1500
#define MOTOR_MAX 2500

#define MOTOR_X_CENTER	2110
#define MOTOR_Y_CENTER	1970



uint coreID;
uint chipID;






#endif
