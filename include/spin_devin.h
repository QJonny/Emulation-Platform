#ifndef SPIN_EMU_DEVIN_H
#define SPIN_EMU_DEVIN_H

#define SPINNAKER_ADDR "192.168.0.11"
#define SPINNAKER_PORT 17893

#define PC_ADDR "127.0.0.1"
#define PC_PORT 17892

#define MOTOR_LOCATION 0xf5000034
#define CHECK_LOCATION 0xf5000038
#define CAMERA_LOCATION 0xf500003c


int spin_devin_init();

unsigned int spin_devin_get_camera();

void spin_devin_send_motor(unsigned int command);

void spin_devin_dispose();

#endif
