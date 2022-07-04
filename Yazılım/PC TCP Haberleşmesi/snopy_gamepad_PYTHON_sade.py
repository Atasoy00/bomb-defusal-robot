import pygame

pygame.init()
clock = pygame.time.Clock()
pygame.joystick.init()

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
    joy[0] = joystick.get_axis(0)
    joy[1] = joystick.get_axis(1)
    joy[2] = joystick.get_axis(2)
    joy[3] = joystick.get_axis(3)

    buton = [None] * 8
    buton[0] = joystick.get_button(0)
    buton[1] = joystick.get_button(1)
    buton[2] = joystick.get_button(2)
    buton[3] = joystick.get_button(3)
    buton[4] = joystick.get_button(4)
    buton[5] = joystick.get_button(5)
    buton[6] = joystick.get_button(6)
    buton[7] = joystick.get_button(7)

    tus = joystick.get_hat(0)
    (tusx,tusy) = tus

    print(tus)

    clock.tick(60)
pygame.quit()