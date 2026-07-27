import turtle as t
from random import*

t.shape("turtle")
t.setx(-200)
t.sety(200)
t.clear()
a = int(input("다각형 수 >>"))

for i in range(a):
    t.forward(25)
    t.right(360/a)
