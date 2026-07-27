import turtle as t

def draw_tree(branch_len):
    if branch_len > 1:
        t.forward(branch_len)
        t.right(20)
        draw_tree(branch_len - 15)
        t.left(40)
        draw_tree(branch_len - 15)
        t.right(20)
        t.backward(branch_len)

t.speed(0)
t.left(90)
t.penup()
t.goto(0, -150)
t.pendown()
t.color("brown")

draw_tree(134)
t.done()
