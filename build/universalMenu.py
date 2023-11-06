import tkinter as tk
from tkinter import filedialog
import subprocess
import os

x = 50
rectangle = 0
rectangle_list = []

def open_file():
    global x, rectangle
    if rectangle < 5:
        file_path = filedialog.askopenfilename()
        if file_path:
            canvas_center_y = canvas.winfo_reqheight() / 2
            frame = tk.Frame(canvas, bg="white", width=250, height=250)

            start_x = x

            canvas.create_window(start_x + 125, canvas_center_y, window=frame)
            canvas.create_rectangle(
                start_x, canvas_center_y - 125,
                start_x + 250, canvas_center_y + 125,
                fill="white",
                tags=("rectangle", file_path)
            )
            label = tk.Label(frame, text=file_path, width=20)
            label.pack()
            rectangle_list.append(file_path)
            rectangle += 1
            x += 360

def execute_path(event):

    clicked_item = canvas.find_withtag(tk.CURRENT)
    if clicked_item:
        file_path = canvas.gettags(clicked_item[0])[1]
        file_path2 = "./r-type_server"
        print("Executing path:", file_path)
    os.system(f'{file_path} &')
    os.system(f'{file_path2} &')
    exit()

# Créer la fenêtre principale
root = tk.Tk()
root.geometry("1920x1080")
root.title("Universal Menu")
root.configure(pady=200)


# Créer un canvas pour le carrousel
canvas = tk.Canvas(root, width=1920, height=500, bg="systemTransparent")
canvas.pack()

# Bouton pour ajouter un fichier
add_button = tk.Button(root, text="Ajouter un fichier", command=open_file)
add_button.pack()

canvas.tag_bind("rectangle", "<Button-1>", execute_path)

root.mainloop()
