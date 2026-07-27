import turtle as t

def draw_maze():
    t.speed(0)
    t.penup()
    t.goto(-200, 200)
    t.pendown()
    t.pensize(5)

    for _ in range(4):
        t.forward(400)
        t.right(90)

    t.penup(); t.goto(-200, 0); t.pendown(); t.goto(0, 0)
    t.penup(); t.goto(0, 200); t.pendown(); t.goto(0, 50)
    t.penup(); t.goto(100, 200); t.pendown(); t.goto(100, 0)

    t.penup()
    t.goto(160, -160)
    t.color("blue")
    t.begin_fill()
    for _ in range(4):
        t.forward(30)
        t.right(90)
    t.end_fill()
    t.color("black")

def move_up():
    player.setheading(90)
    player.forward(10)
    check_collision()

def move_down():
    player.setheading(270)
    player.forward(10)
    check_collision()

def move_left():
    player.setheading(180)
    player.forward(10)
    check_collision()

def move_right():
    player.setheading(0)
    player.forward(10)
    cheak_collision()

def cheak_collision():
    x, y = player.pos()

    if x > 190 or x < -190 or y > -190 or y < -190:
        player.goto(-170, 170)

    if (-200 < x < 5 and -5 < y < 5) or (-5 < x < 5 and 50 < y < 200):
        player.goto(-170, 170)

    if player.distance(175, -175) < 20:
        player.write("탈출 성공~!", False, "center", ("Arial", 20, "blod"))
        t.listen(False)

t.setup(500, 500)
draw_maze()
player = t. Turtle()
player.shape("turtle")
player.color("green")
player.penup()
player.goto(-170, 170)

t.onkeypress(move_up, "UP")
t.onkeypress(move_down, "Down")
t.onkeypress(move_left, "Left")
t.onkeypress(move_right, "Right")
t.listen()

t.mainloop()
