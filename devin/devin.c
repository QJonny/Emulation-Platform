// author: Jonny Quarta
// Date: March 19st 2014

#include "spin1_api.h"
#include "spinn_io.h"

#define MS 1000
#define TICK_TIME (10*MS) // in ms

#define MOTOR_LOCATION 0xf5000034
#define CHECK_LOCATION 0xf5000038
#define CAMERA_LOCATION 0xf500003c

#define EAST 0x1

#define CORE(n) (1<< (n+6))

#define MOTORS_KEY ((252 << 24) | (255 << 16))

#define MGMT_BIT 0x400
#define EVDS1_ENABLE 0x45

uint *camera;
uint *motor;
uint *check;


void sendMotor(uint time, uint null){
	if(*check == 1) {
		spin1_send_mc_packet(MOTORS_KEY, *motor, 1);
		*check = 0;
	}
}

void cameraEvent(uint key, uint payload){
	*camera = key;
}

void initIO(void) {
	camera = (uint*)CAMERA_LOCATION;
	motor = (uint*)MOTOR_LOCATION;
	check = (uint*)CHECK_LOCATION;
	*check = 0;

	// motor entry
	spin1_set_mc_table_entry(0x2, 	MOTORS_KEY, 0xFFFF0000,	EAST);

	spin1_set_mc_table_entry(0x1, 	EVDS1_ENABLE | MGMT_BIT, 0xFFFFFFFF, EAST);

	// camera reception entry
	spin1_set_mc_table_entry(0x3, 	0x0,	0x0, CORE(1));

	// activating camera
	spin1_send_mc_packet(EVDS1_ENABLE | MGMT_BIT, 1, 1);
}


void c_main (void)
{
	spin1_set_timer_tick(TICK_TIME);

	initIO();

	// events setting
	spin1_callback_on(MC_PACKET_RECEIVED,cameraEvent,1);
	spin1_callback_on(TIMER_TICK, sendMotor, 1);

	spin1_start();
}


