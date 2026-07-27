import tkinter as tk
from tkinter import filedialog, colorchooser
from PIL import Image, ImageDraw, ImageTk

class Paint:
    def __init__(self, root):
        self.root = root
        self.root.title("Advanced Paint")

        self.tool = "brush"
        self.color = "black"
        self.size = 5
        self.start_x = None
        self.start_y = None

        self.history = []

        # 캔버스
        self.canvas = tk.Canvas(root, bg="white", width=900, height=600)
        self.canvas.pack()

        self.image = Image.new("RGB", (900, 600), "white")
        self.draw = ImageDraw.Draw(self.image)

        # 툴바
        frame = tk.Frame(root)
        frame.pack()

        tools = ["brush", "line", "rect", "oval", "text", "eraser"]
        for t in tools:
            tk.Button(frame, text=t, command=lambda t=t: self.set_tool(t)).pack(side="left")

        tk.Button(frame, text="색", command=self.pick_color).pack(side="left")
        tk.Button(frame, text="저장", command=self.save).pack(side="left")
        tk.Button(frame, text="열기", command=self.open).pack(side="left")
        tk.Button(frame, text="Undo", command=self.undo).pack(side="left")
        tk.Button(frame, text="Clear", command=self.clear).pack(side="left")

        self.size_slider = tk.Scale(frame, from_=1, to=20, orient="horizontal")
        self.size_slider.set(5)
        self.size_slider.pack(side="left")

        # 이벤트
        self.canvas.bind("<Button-1>", self.start)
        self.canvas.bind("<B1-Motion>", self.paint)
        self.canvas.bind("<ButtonRelease-1>", self.stop)

    def set_tool(self, tool):
        self.tool = tool

    def pick_color(self):
        color = colorchooser.askcolor()[1]
        if color:
            self.color = color

    def start(self, e):
        self.start_x, self.start_y = e.x, e.y
        self.history.append(self.image.copy())

    def paint(self, e):
        if self.tool == "brush":
            self.canvas.create_line(self.start_x, self.start_y, e.x, e.y,
                                    fill=self.color, width=self.size_slider.get(), capstyle=tk.ROUND)
            self.draw.line([self.start_x, self.start_y, e.x, e.y],
                           fill=self.color, width=self.size_slider.get())
            self.start_x, self.start_y = e.x, e.y

        elif self.tool == "eraser":
            self.canvas.create_line(self.start_x, self.start_y, e.x, e.y,
                                    fill="white", width=self.size_slider.get())
            self.draw.line([self.start_x, self.start_y, e.x, e.y],
                           fill="white", width=self.size_slider.get())
            self.start_x, self.start_y = e.x, e.y

    def stop(self, e):
        if self.tool == "line":
            self.canvas.create_line(self.start_x, self.start_y, e.x, e.y,
                                    fill=self.color, width=self.size_slider.get())
            self.draw.line([self.start_x, self.start_y, e.x, e.y],
                           fill=self.color, width=self.size_slider.get())

        elif self.tool == "rect":
            self.canvas.create_rectangle(self.start_x, self.start_y, e.x, e.y,
                                         outline=self.color, width=self.size_slider.get())
            self.draw.rectangle([self.start_x, self.start_y, e.x, e.y],
                                outline=self.color, width=self.size_slider.get())

        elif self.tool == "oval":
            self.canvas.create_oval(self.start_x, self.start_y, e.x, e.y,
                                    outline=self.color, width=self.size_slider.get())
            self.draw.ellipse([self.start_x, self.start_y, e.x, e.y],
                              outline=self.color, width=self.size_slider.get())

        elif self.tool == "text":
            text = tk.simpledialog.askstring("텍스트", "입력:")
            if text:
                self.canvas.create_text(e.x, e.y, text=text, fill=self.color)
                self.draw.text((e.x, e.y), text, fill=self.color)

    def save(self):
        file = filedialog.asksaveasfilename(defaultextension=".png")
        if file:
            self.image.save(file)

    def open(self):
        file = filedialog.askopenfilename()
        if file:
            img = Image.open(file)
            img = img.resize((900, 600))
            self.image = img
            self.draw = ImageDraw.Draw(self.image)
            self.tk_img = ImageTk.PhotoImage(img)
            self.canvas.create_image(0, 0, anchor="nw", image=self.tk_img)

    def undo(self):
        if self.history:
            self.image = self.history.pop()
            self.draw = ImageDraw.Draw(self.image)
            self.tk_img = ImageTk.PhotoImage(self.image)
            self.canvas.create_image(0, 0, anchor="nw", image=self.tk_img)

    def clear(self):
        self.canvas.delete("all")
        self.image = Image.new("RGB", (900, 600), "white")
        self.draw = ImageDraw.Draw(self.image)

root = tk.Tk()
app = Paint(root)
root.mainloop()