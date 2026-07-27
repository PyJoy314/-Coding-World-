import turtle as t
from random import*

t.shape("turtle")
t.setx(-200)
t.sety(200)
t.clear()
a = 4

for i in range(a):
    t.forward(100)
    t.right(360/a)
