import turtle as t
import random

# 1. 화면 설정
screen = t.Screen()
screen.setup(width=500, height=400)
screen.title("흥미진진 태민이의 거북이 경주!")

# 2. 경주에 참가할 거북이 색상 리스트
colors = ["red", "orange", "yellow", "green", "blue", "purple"]
all_turtles = []

#3. 거북이들 생성 빛 출발선 배치
for i in range(len(colors)):
    new_turtle = t.Turtle(shape="turtle")
    new_turtle.color(colors[i])
    new_turtle.penup()
    #거북이들을 세로로 나란히 배치 (-150부터 50씩 간격)
    new_turtle.goto(x=-230, y=-120 + (i * 50))
    all_turtles.append(new_turtle)

#4. 결승선 그리기
line = t.Turtle()
line.penup()
line.goto(200, 160)
line.pendown()
line.goto(200, -140)
line.hideturtle()

#5.게임 시작
is_race_on = True

while is_race_on:
    for turtle in all_turtles:
        #각 거북이가 0~10 사이의 랜덤한 거리만큼 이동
        distance = random.randint(0, 10)
        turtle.forward(distance)

        if turtle.xcor > 200:
            is_race_on = False
            winning_color = turtle.pencolor()

            t.penup()
            t.goto(-100, 0)
            t.write(f"승리자 : {winning_color} 태민이!", font=("Arial", 20, "bold"))
t.done()
