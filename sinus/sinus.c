// author: Jonny Quarta
// Date: March 19st 2014

#include "sinus.h"

#define MC_PAYLOAD 15




void sendMotorCommand(uint motor_x, uint motor_y) {
	spin_devin_send_motor(motor_y | (motor_x << 16 ));
}


void update(uint sim_time, uint none)
{
	if(sim_time % 2 == 0) {
		float rad = 2.0*3.1415*(sim_time % 360)/360.0;

		float s = sin(rad);

		int coord = (int)(500*(s) + 2000);

		sendMotorCommand(2000, coord);
		//io_printf(IO_BUF,"coord is %d\n", coord);
	}
}


// The idea is to set a communication system whose purpose
// is to exchange data from a virtual master node (situated
// at core 0, chip 0) and all the other cores situated on all
// the other chips. From master node to other nodes we use multicast
// messages, whereas from a node to master node we use sdp messages.
void c_main (void)
{		
	// simulation initialization
	coreID = spin1_get_core_id();
	chipID = spin1_get_chip_id();

	if(chipID == 0 && coreID == 1) {
		io_printf(IO_BUF,"CoreID is %u, ChipID is %u\n",coreID, chipID);

		spin1_set_timer_tick(TICK_TIME);
		// end of simulation initialization

		spin1_callback_on(TIMER_TICK, update, 1);
		spin_devin_init();
	}

	spin1_start();
}


