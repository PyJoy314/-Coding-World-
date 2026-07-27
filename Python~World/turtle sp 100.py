import turtle as t
import colorsys

#초기 설정
t.bgcolor("black")
t.speed(0)
t.width(2)
n = 70
h = 0

#스피로그래프 그리기

for i in range(n):
    # colorsys를 이용해 화려한 무지개색 생성
    c = colorsys.hsv_to_rgb(h, 1, 1)
    t.pencolor(c)
    h += 1/n

    #도형 그리기 (여기서는 사각형을 활용)
    t.forward(100)
    t.right(90)
    t.left(360/n)
    
# 완성 후 창이 바로 닫리지 않게 설정
t.hideturtle()
