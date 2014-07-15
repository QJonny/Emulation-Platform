# distutils: language = c++
# distutils: sources = spin_emu_devin.cpp

from functions cimport *

cdef class PyDevin:
    cdef devin *thisptr      # hold a C++ instance which we're wrapping
    def __cinit__(self):
        self.thisptr = new devin()
    def __dealloc__(self):
        del self.thisptr

    def init(self):
        self.thisptr.spin_devin_init()

    def get_camera(self):
        return self.thisptr.spin_devin_get_camera()

    def send_motor(self, command):
        self.thisptr.spin_devin_send_motor(command)

    def dispose(self):
        self.thisptr.spin_devin_dispose()
