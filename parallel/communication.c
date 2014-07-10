#include "communication.h"



void initIO(uint chipID, uint coreID) {
	if(chipID == 0) { // 0, 0
		// from master to nodes
		spin1_set_mc_table_entry(0x6, 	ERROR_MSG,	 0xF0000000, NORTH|N_EAST|EAST|ALL_NODES_MASTER_CHIP);
		// froms nodes to master
		spin1_set_mc_table_entry(0x7, 	UPD_MSG,	 0xC0000000, MASTER_CORE);
	}	
	else if(chipID == 1) { // 0, 1
		spin1_set_mc_table_entry(0x6, 	ERROR_MSG,	 0xF0000000, ALL_NODES_NO_MASTER_CHIP); // to nodes
		spin1_set_mc_table_entry(0x7, 	UPD_MSG,	 0xC0000000, SOUTH); // to master
	}
	else if(chipID == 256) { // 1, 0
		spin1_set_mc_table_entry(0x6, 	ERROR_MSG,	 0xF0000000, ALL_NODES_NO_MASTER_CHIP); // to nodes
		spin1_set_mc_table_entry(0x7, 	UPD_MSG,	 0xC0000000, WEST); // to master
	}
	else if(chipID == 257) { // 1, 1
		spin1_set_mc_table_entry(0x6, 	ERROR_MSG,	 0xF0000000, ALL_NODES_NO_MASTER_CHIP); // to nodes
		spin1_set_mc_table_entry(0x7, 	UPD_MSG,	 0xC0000000, S_WEST); // to master
	}
}


void sendMotorCommand(uint motor_x, uint motor_y) {
	spin_devin_send_motor(motor_y | (motor_x << 16 ));
}


void sendNormMotorCommand(float x, float y) {
	sendMotorCommand((int)(x*MOTOR_DELTA) + MOTOR_X_CENTER, (int)(y*MOTOR_DELTA) + MOTOR_Y_CENTER);
}
