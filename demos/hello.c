#include "spin1_api.h"
#include "spinn_io.h"
#include "spinn_sdp.h"
#include "spin_devin.h"

void upd(uint sim, uint none) {
	io_printf(IO_BUF, "Updating!\n");
}


void c_main (void)
{
  uint coreID = spin1_get_core_id();
  uint chipID = spin1_get_chip_id();

  if(chipID == 0 && coreID == 1) {
	  io_printf (IO_STD, "Hello world! (via SDP)\n");

	  io_printf (IO_BUF, "Hello world! (via the terminal)\n");

	  if(spin_devin_init() == 0) {
		io_printf(IO_BUF, "Error: could not connect to the SpiNNaker!\n");
	  }

	  spin_devin_send_motor(2000 << 16 | 2000);
	  uint cam = spin_devin_get_camera();
	  io_printf(IO_BUF, "camera: %08x\n", cam);

	  spin1_set_timer_tick(10000);
	  spin1_callback_on(TIMER_TICK, upd, 0);

	  spin_devin_dispose();
  }

  spin1_start();
}
