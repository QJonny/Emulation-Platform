import math


class Smoother:
	avg = 8

	# ball tracking
	x_buffer = -1
	y_buffer = -1
	total_sum_x = 0.0
	total_sum_y = 0.0
	curr_index = 0
	# end of ball tracking


	# ball parameters
	x_pos = 0.0
	y_pos = 0.0
	x_speed = 0.0
	y_speed = 0.0
	# end of ball parameters


	def __init__(self, avg):
		self.avg = avg
		self.x_buffer = [ 0.0 for i in range(self.avg) ]
		self.y_buffer = [ 0.0 for i in range(self.avg) ]


	def addVector(self, x_cur, y_cur):
		# this is a very efficient way to average 
		# over 16 position samples without any sum
		# or division

		self.total_sum_x = self.total_sum_x - self.x_buffer[self.curr_index] + x_cur
		self.x_buffer[self.curr_index] = x_cur
		self.total_sum_y = self.total_sum_y - self.y_buffer[self.curr_index] + y_cur
		self.y_buffer[self.curr_index] = y_cur

		self.x_pos = self.total_sum_x / (self.avg*1.0)
		self.y_pos = self.total_sum_y / (self.avg*1.0)		

		self.curr_index = (self.curr_index + 1) % self.avg



	def getVector(self):
		return (self.x_pos, self.y_pos)




class SpeedCalculator:
	old_x = 0
	old_y = 0
	nb_samples = 0
	nb_smoothers = 0

	sm = -1

	def __init__(self, smoothers = 20, samples = 32):
		self.nb_samples = samples
		self.nb_smoothers = smoothers
		self.sm = [Smoother(self.nb_samples) for i in range(self.nb_smoothers)]

	def normalize(self, x, y):
		norm = math.sqrt(x*x + y*y)
		if(norm > 0):
			return (x/norm, y/norm)
		else:
			return (0.0, 0.0)

	def getSpeed(self, x, y):
		temp_x = x
		temp_y = y

		for i in range(self.nb_smoothers):
			self.sm[i].addVector(temp_x, temp_y)
			(temp_x, temp_y) = self.sm[i].getVector()

		x_pos = temp_x
		y_pos = temp_y
		v_x = x_pos - self.old_x
		v_y = y_pos - self.old_y

		self.old_x = x_pos
		self.old_y = y_pos

		return self.normalize(v_x, v_y)




