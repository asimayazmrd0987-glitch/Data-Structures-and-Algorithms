
import math
import time
import os
import sys

A = 0
B = 0

WIDTH = 80
HEIGHT = 24
CHARS = ".,-~:;=!*#$@"

# Hide cursor for smoother animation
sys.stdout.write("\033[?25l")
sys.stdout.flush()

try:
    while True:
        output = [" "] * (WIDTH * HEIGHT)
        zbuffer = [0] * (WIDTH * HEIGHT)

        cosA, sinA = math.cos(A), math.sin(A)
        cosB, sinB = math.cos(B), math.sin(B)

        theta = 0
        while theta < 2 * math.pi:
            costheta = math.cos(theta)
            sintheta = math.sin(theta)

            phi = 0
            while phi < 2 * math.pi:
                cosphi = math.cos(phi)
                sinphi = math.sin(phi)

                # Donut surface
                circle_x = 2 + costheta
                circle_y = sintheta

                x = circle_x * (
                    cosB * cosphi + sinA * sinB * sinphi
                ) - circle_y * cosA * sinB

                y = circle_x * (
                    sinB * cosphi - sinA * cosB * sinphi
                ) + circle_y * cosA * cosB

                z = 5 + cosA * circle_x * sinphi + circle_y * sinA

                inv_z = 1 / z

                # Project 3D coordinates onto terminal
                xp = int(WIDTH / 2 + 30 * inv_z * x)
                yp = int(HEIGHT / 2 - 15 * inv_z * y)

                # Surface lighting
                L = (
                    cosphi * costheta * sinB
                    - cosA * costheta * sinphi
                    - sinA * sintheta
                    + cosB * (
                        cosA * sintheta - costheta * sinA * sinphi
                    )
                )

                if L > 0 and 0 <= xp < WIDTH and 0 <= yp < HEIGHT:
                    index = xp + WIDTH * yp

                    if inv_z > zbuffer[index]:
                        zbuffer[index] = inv_z
                        brightness = int(L * 8)
                        brightness = max(0, min(11, brightness))
                        output[index] = CHARS[brightness]

                phi += 0.02

            theta += 0.07

        # ANSI clear and redraw without launching an external command
        sys.stdout.write("\033[H")
        for row in range(HEIGHT):
            line = "".join(
                output[row * WIDTH:(row + 1) * WIDTH]
            )
            sys.stdout.write(line + "\n")

        sys.stdout.write("\033[96m      ROTATING ASCII DONUT 🍩\033[0m\n")
        sys.stdout.flush()

        A += 0.04
        B += 0.02
        time.sleep(0.03)

except KeyboardInterrupt:
    pass
finally:
    sys.stdout.write("\033[?25h\033[0m\n")
    sys.stdout.flush()


    #
    #                                     @@@@$@@$@@@@$                                 
    #                                 $$$$$##########$$$$$$                             
    #                              $$###***$$$$$$$$$!!!***###$$                           
    #                           ####**!!!!!!$$$$$$!!$$!!!!**####                         
    #                         *###**!!!!==;:::~$$$~:::;==!!!***###*                       
    #                        @!******!!=;;:~-,,,,,,-~:;;=!!*******                      
    #                      ==@******!==;:~,..       .-~:;==!******!                     
    #                     ==@!*****!!=;:~-.          .-~:;=!!*****!                     
    #                    @@@!!***!!!=;:~,            ,~:;=!!!****!;                  
    #                   ===!!***!!==;~,.           ,~;=!!$!****!!;                    
    #                   =!!*****!!!=;~          ~;==!!!***$$*!!=;                    
    #                   $==!*********!!=        =!!!********!!=:                    
    #                   $:=!!!***#########*!!**#######****!!!=;                     
    #                   $;=!!!**####$$$$$@@$$$$$$####***!!!=;~                     
    #                   -:=!!!***###$$$@@@@@$$$$###**!!!!=;:                      
    #                   ,:;=!!!***###$$$$$$$####**!!!!==:~                       
    #                    ~:;=!!!!*****####****!!!!!=;:~                         
    #                     -~:==!!!*!!!!!!*!!!!!==;:~,                          
    #                      ,-~:;;;========;;;::-,                             
    #                          ,-------~--,.                       