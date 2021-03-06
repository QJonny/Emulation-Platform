// author: Jonny Quarta
// Date: March 19st 2014

#include "BallController.h"


// ball tracking
int x_buffer[16] = {0};
int y_buffer[16] = {0};
int total_sum_x = 0;
int total_sum_y = 0;
int curr_index = 0;
int old_time = -1;
// end of ball tracking


// ball parameters
int x_pos = 0;
int y_pos = 0;
// end of ball parameters

// motors comands
int x_command = 0;
int y_command = 0;
// end of motors commands

int pos_computed = 0;

int state = STATE_UNBALANCED;



// ball tracking

void compute_pos(int x_cur, int y_cur, int sim_time)
{
	if((pos_computed == 0 || norm(x_pos - x_cur, y_pos - y_cur) < 100)) {

		// this is a very efficient way to average 
		// over 16 position samples without any sum
		// or division

		total_sum_x = total_sum_x - x_buffer[curr_index] + x_cur;
		x_buffer[curr_index] = x_cur;
		total_sum_y = total_sum_y - y_buffer[curr_index] + y_cur;
		y_buffer[curr_index] = y_cur;

		x_pos = total_sum_x >> 4; // division by 16
		y_pos = total_sum_y >> 4; // division by 16

		if(pos_computed == 0 && curr_index == 15) {
			pos_computed = 1;
		}

		curr_index = (curr_index + 1) % 16;

		old_time = sim_time;
	}
}


void cameraEvent(){
	uint key = spin_devin_get_camera();

	// raw position extraction
	int y_cur = ((key & 0x7F));
	int x_cur = (((key >> 8) & 0x7F));
	int pol = (key >> 7) & 0x01;
	int check = (key >> 15) & 0x01;

	if(pol == 1) {
		compute_pos(x_cur, y_cur, spin1_get_simulation_time()/10);
	}
}


void update(uint sim_time, uint none)
{
	if(sim_time % 10 == 0) {
		if(state == STATE_UNBALANCED) {
			mfm_();
			// actor network updating and command sending
			update_A( sim_time/10 );
			state = move( sim_time/10 );

			// critic networks update
			updateError(x_pos, y_pos, sim_time/10);
			update_V();
			// end of networks update
		}

		// save step
		if(state == STATE_BALANCED || sim_time/10 % SAVE_STEP == 0) {
			save_();
			state = STATE_SAVED;
			spin1_callback_off(TIMER_TICK);
		}
	} else {
		cameraEvent();
	}
}




void c_main (void)
{		
	// simulation initialization
	coreID = spin1_get_core_id();
	chipID = spin1_get_chip_id();

	if(chipID == 0 && coreID == 1) {
		io_printf(IO_BUF,"Starting balancing...\n");

		spin1_set_timer_tick(TICK_TIME);
		// end of simulation initialization	
	
		spin_devin_init();


		// networks init
		init_network(0);

	
		// events setting
		spin1_callback_on(TIMER_TICK, update, 0);
	}

	spin1_start();
}


