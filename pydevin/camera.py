import pygame
import sys
import time
import devinManager
import math
from speedManager import *
        

def drawCircle(x, y):
        global window
        pygame.draw.circle(window, (255, 255, 255), (x, y), 1, 1)

def drawLine(x, y):
        global window
        pygame.draw.line(window, (255, 0, 0), (64, 64), (x, y), 1)


def run():
        global window
	counter = 1
	v = SpeedCalculator()
	vsm = Smoother(128)

        #create the screen
        window = pygame.display.set_mode((128, 128)) 

        #input handling (somewhat boilerplate code):
        while True: 
	    devinManager.cameraEvent()
	    (x_pos, y_pos) = devinManager.getCamera()

            (v_x, v_y) = v.getSpeed(x_pos, y_pos)

            vsm.addVector(v_x, v_y)
            (v_x, v_y) = vsm.getVector()

	    window.fill((0,0,0))
	
	    #draw
	    drawLine(int(64*v_x + 64), 128 - int(64*v_y + 64))
	    drawCircle(int(64*x_pos + 64), 128 - int(64*y_pos + 64))

	    counter = counter + 1

            #draw it to the screen
            pygame.display.update() 

            for event in pygame.event.get(): 
                if event.type == pygame.QUIT: 
                    pygame.quit()
                    sys.exit(0) 


