import socket
import time
import sys
import keyboard

# create an INET, STREAMing socket (IPv4, TCP/IP)
try:
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print('Failed to create socket')
    sys.exit()

print('Socket Created')

ROBOT_IP = "192.168.1.65"
ROBOT_PORT = 80
# Connect the socket object to the robot using IP address (string) and port (int)
client.connect((ROBOT_IP, ROBOT_PORT))

print('Socket Connected to ' + ROBOT_IP)

Mode_Flag = True

while True:

    ch1 = 1500
    ch2 = 1500
    ch3 = 1234
    ch4 = 1234
    ch5 = 1234
    ch6 = 1000
    ch7 = 1000
    ch8 = 1000
    ch9 = 1000
    ch0 = 1000

    if keyboard.read_key() == "5":
        print("You pressed 5")
        ch1 = 1500
        ch2 = 1500
    elif keyboard.read_key() == "8":
        print("You pressed 8")
        ch1 = 1500
        ch2 = 2000
    elif keyboard.read_key() == "2":
        print("You pressed 2")
        ch1 = 1500
        ch2 = 1000
    elif keyboard.read_key() == "4":
        print("You pressed 4")
        ch1 = 2000
        ch2 = 1500
    elif keyboard.read_key() == "6":
        print("You pressed 6")
        ch1 = 1000
        ch2 = 1500
    elif keyboard.read_key() == "7":
        print("You pressed 7")
        ch1 = 2000
        ch2 = 2000
    elif keyboard.read_key() == "9":
        print("You pressed 9")
        ch1 = 1000
        ch2 = 2000
    elif keyboard.read_key() == "1":
        print("You pressed 1")
        ch1 = 2000
        ch2 = 1000
    elif keyboard.read_key() == "3":
        print("You pressed 3")
        ch1 = 1000
        ch2 = 1000

    ch1 = str(ch1)
    ch2 = str(ch2)
    ch3 = str(ch3)
    ch4 = str(ch4)
    ch5 = str(ch5)
    ch6 = str(ch6)
    ch7 = str(ch7)
    ch8 = str(ch8)
    ch9 = str(ch9)
    ch0 = str(ch0)

    # Add ASCII NULL character at the end of the cmd string
    try:
        client.send(bytes(ch1+ch2+ch3+ch4+ch5+ch6+ch7+ch8+ch9+ch0, 'ascii'))
        #time.sleep(1)

    except socket.error:
        print('Failed to send data')

# Disconnect from the robot and close the socket object
client.close()
sys.exit()