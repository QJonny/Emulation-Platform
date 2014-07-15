cdef extern from "spin_devin.h":
    cdef cppclass devin:
        devin()
        int spin_devin_init()
        unsigned int spin_devin_get_camera()
        void spin_devin_send_motor(unsigned int command)
        void spin_devin_dispose()
