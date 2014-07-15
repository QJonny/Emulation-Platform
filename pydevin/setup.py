from distutils.core import setup
from Cython.Build import cythonize

setup(ext_modules = cythonize(
           "pydevin.pyx",              		# our Cython source
           sources=["spin_emu_devin.cpp"],  	# additional source file(s)
           language="c++",             		# generate C++ code
      ))
