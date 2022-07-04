import pygame
import socket
import sys

pygame.init()
clock = pygame.time.Clock()
pygame.joystick.init()

# create an INET, STREAMing socket (IPv4, TCP/IP)
try:
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print('Failed to create socket')
    sys.exit()

print('Socket Created')

ROBOT_IP = "192.168.1.166"
ROBOT_PORT = 80
# Connect the socket object to the robot using IP address (string) and port (int)
client.connect((ROBOT_IP, ROBOT_PORT))

print('Socket Connected to ' + ROBOT_IP)


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
    joystick_count = pygame.joystick.get_count()

    for i in range(joystick_count):
        joystick = pygame.joystick.Joystick(i)
        joystick.init()
        name = joystick.get_name()
        axes = joystick.get_numaxes()

    # verilerin çekilmesi # ----------------------------------------------------------------

    joy = [None] * 4
    joy[0] = round(joystick.get_axis(0))+5
    joy[1] = round(joystick.get_axis(1))+5
    joy[2] = round(joystick.get_axis(2))+5
    joy[3] = round(joystick.get_axis(3))+5

    buton = [None] * 8
    buton[0] = joystick.get_button(0)+5
    buton[1] = joystick.get_button(1)+5
    buton[2] = joystick.get_button(2)+5
    buton[3] = joystick.get_button(3)+5
    buton[4] = joystick.get_button(4)+5
    buton[5] = joystick.get_button(5)+5
    buton[6] = joystick.get_button(6)+5
    buton[7] = joystick.get_button(7)+5

    tus = joystick.get_hat(0)
    (tusx,tusy) = tus
    tusx+=5
    tusy+=5

    data1 = str(joy[0])+str(joy[1])+str(joy[2])+str(joy[3])
    data2 = str(buton[0])+str(buton[1])+str(buton[2])+str(buton[3])
    data3 = str(buton[4])+str(buton[5])+str(buton[6])+str(buton[7])
    data4 = str(tusx)+str(tusy)


    # Add ASCII NULL character at the end of the cmd string
    try:
        client.send(bytes(data1+data2+data3+data4, 'ascii'))
        #time.sleep(1)

    except socket.error:
        print('Failed to send data')


    clock.tick(60)
    

# Disconnect from the robot and close the socket object
client.close()
sys.exit()
pygame.quit()

