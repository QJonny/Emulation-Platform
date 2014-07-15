import pygame
import sys
import time
import devinManager
        

def draw(x, y):
        global window
        pygame.draw.circle(window, (255, 255, 255), (x, y), 1, 1)


def run():
        global window
	counter = 1
	x_pos = 0
	y_pos = 0

        #create the screen
        window = pygame.display.set_mode((128, 128)) 

        #input handling (somewhat boilerplate code):
        while True: 
	    devinManager.cameraEvent(counter)
	    (x_pos, y_pos) = devinManager.getCamera()
	    window.fill((0,0,0))
	
	    #draw a circle
	    draw(int(64*x_pos + 64), 128 - int(64*y_pos + 64))

	    counter = counter + 1

            #draw it to the screen
            pygame.display.update() 

            for event in pygame.event.get(): 
                if event.type == pygame.QUIT: 
                    pygame.quit()
                    sys.exit(0) 


