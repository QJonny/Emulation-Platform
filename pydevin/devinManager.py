from pydevin import *
import math


# ball parameters definitions
BALL_POS_Y_MAX = 115
BALL_POS_Y_MIN = 5
BALL_POS_Y_CENTER = (BALL_POS_Y_MAX + BALL_POS_Y_MIN) / 2.0

BALL_POS_X_MAX = 125
BALL_POS_X_MIN = 20
BALL_POS_X_CENTER = (BALL_POS_X_MAX + BALL_POS_X_MIN) / 2.0


A_X = -1.0/(BALL_POS_X_MAX - BALL_POS_X_CENTER)
B_X = -(A_X)*BALL_POS_X_CENTER
A_Y = -1.0/(BALL_POS_Y_MIN - BALL_POS_Y_CENTER)
B_Y = -(A_Y)*BALL_POS_Y_CENTER


# ball tracking
x_buffer = [ 0 for i in range(16) ]
y_buffer = [ 0 for i in range(16) ]
total_sum_x = 0
total_sum_y = 0
curr_index = 0
# end of ball tracking


# ball parameters
x_pos = 0
y_pos = 0
f_x_pos = 0.0
f_y_pos = 0.0
# end of ball parameters


pos_computed = 0




# motor params
alpha_x = 1 # l=1500, h=2500
beta_x = 0
alpha_y = 1 # l=1500, h=2500
beta_y = 0





pdev = PyDevin()
pdev.init()


def norm(x, y):
	return math.sqrt(x*x + y*y)

def r_range(v, l, h):
	if(v < l):
		return l
	elif(v > h):
		return h

	return v

# ball tracking

# normalizes ball position
def normalize_ball_params():
	global A_X, A_Y, B_X, B_Y, f_x_pos, f_y_pos

	f_x_pos = r_range(A_X*x_pos + B_X, -1.0, 1.0)
	f_y_pos = r_range(A_Y*y_pos + B_Y, -1.0, 1.0)



def compute_pos(x_cur, y_cur):
	global pos_computed, x_pos, y_pos, curr_index, total_sum_x, total_sum_y, x_buffer, y_buffer

	if(pos_computed == 0 or norm(x_pos - x_cur, y_pos - y_cur) < 100):

		# this is a very efficient way to average 
		# over 16 position samples without any sum
		# or division

		total_sum_x = total_sum_x - x_buffer[curr_index] + x_cur
		x_buffer[curr_index] = x_cur
		total_sum_y = total_sum_y - y_buffer[curr_index] + y_cur
		y_buffer[curr_index] = y_cur

		x_pos = total_sum_x >> 4 # division by 16
		y_pos = total_sum_y >> 4
		normalize_ball_params() 

		if(pos_computed == 0 and curr_index == 15):
			pos_computed = 1
		

		curr_index = (curr_index + 1) % 16



def cameraEvent():
	global pdev

	key = pdev.get_camera()

	# raw position extraction
	y_cur = ((key & 0x7F))
	x_cur = (((key >> 8) & 0x7F))
	pol = (key >> 7) & 0x01
	check = (key >> 15) & 0x01

	if(pol == 1):
		compute_pos(x_cur, y_cur)
		normalize_ball_params()


def getCamera():
	global f_x_pos, f_y_pos

	return (f_x_pos, f_y_pos)




def setMotorRange(l, h):
	global alpha_x, beta_x, alpha_y, beta_y

	alpha_x = 1000.0 / (h - l)
	beta_x = 1680.0 - 1000.0*(l/(h-l))

	alpha_y = 1000.0 / (h - l)
	beta_y = 1450.0 - 1000.0*(l/(h-l))


def sendCommand(x, y):
	global alpha_x, beta_x, alpha_y, beta_y

	f_x = alpha_x*x + beta_x
	f_y = alpha_y*y + beta_y
	pdev.send_motor(int(f_y) | (int(f_x) << 16 ))

