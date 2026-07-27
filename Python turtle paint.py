import turtle
import tkinter as tk
from tkinter import simpledialog, filedialog

# 기본 설정
screen = turtle.Screen()
screen.title("Turtle Paint")
screen.bgcolor("white")

canvas = screen.getcanvas()

pen = turtle.Turtle()
pen.shape("turtle")
pen.speed(0)
pen.width(3)

drawing = True
mouse_mode = False  # 🖱 마우스 모드

MOVE = 20

# =========================
# 🎮 이동
# =========================
def move_up():
    pen.setheading(90)
    pen.forward(MOVE)

def move_down():
    pen.setheading(270)
    pen.forward(MOVE)

def move_left():
    pen.setheading(180)
    pen.forward(MOVE)

def move_right():
    pen.setheading(0)
    pen.forward(MOVE)

# =========================
# ✏️ 펜 ON/OFF
# =========================
def toggle_pen():
    global drawing
    if drawing:
        pen.penup()
        drawing = False
    else:
        pen.pendown()
        drawing = True

# =========================
# 🎨 색 변경
# =========================
def change_color():
    root = tk.Tk()
    root.withdraw()

    try:
        r = simpledialog.askinteger("RGB", "R 값 (0~255):", minvalue=0, maxvalue=255)
        g = simpledialog.askinteger("RGB", "G 값 (0~255):", minvalue=0, maxvalue=255)
        b = simpledialog.askinteger("RGB", "B 값 (0~255):", minvalue=0, maxvalue=255)

        if r is not None and g is not None and b is not None:
            turtle.colormode(255)
            pen.color(r, g, b)
    except:
        pass

    root.destroy()

# =========================
# 💾 저장
# =========================
def save_drawing():
    root = tk.Tk()
    root.withdraw()

    file_path = filedialog.asksaveasfilename(defaultextension=".png")

    if file_path:
        # PostScript로 저장 후 PNG 변환 (기본 turtle 방식)
        canvas.postscript(file="temp.ps")
        try:
            from PIL import Image
            img = Image.open("temp.ps")
            img.save(file_path, "png")
        except:
            print("PIL 필요: pip install pillow")

    root.destroy()

# =========================
# ↩️ 실행 취소
# =========================
def undo():
    try:
        pen.undo()
    except:
        pass

# =========================
# 🖱 마우스 드로잉
# =========================
def toggle_mouse():
    global mouse_mode
    mouse_mode = not mouse_mode

    if mouse_mode:
        pen.penup()
        screen.onscreenclick(draw_with_mouse)
    else:
        screen.onscreenclick(None)

def draw_with_mouse(x, y):
    pen.goto(x, y)
    if drawing:
        pen.pendown()
    else:
        pen.penup()

# =========================
# 🎮 키 바인딩
# =========================
screen.listen()

screen.onkey(move_up, "Up")
screen.onkey(move_down, "Down")
screen.onkey(move_left, "Left")
screen.onkey(move_right, "Right")

screen.onkey(toggle_pen, "o")
screen.onkey(toggle_pen, "O")

screen.onkey(change_color, "c")
screen.onkey(change_color, "C")

screen.onkey(save_drawing, "s")  # 💾 저장
screen.onkey(undo, "z")          # ↩️ 실행취소
screen.onkey(toggle_mouse, "m")  # 🖱 마우스 모드

# 시작
turtle.done()