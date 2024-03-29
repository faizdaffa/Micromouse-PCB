import tkinter as tk
from table import *
from plotting import *
from connection import *
from tkinter import ttk, filedialog, messagebox
import sys


class App(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        self.title("PID Plotter - UPN Veteran Jakarta")
        self.state('zoomed')
        self.columnconfigure(0, weight=1)
        self.columnconfigure(1, weight=19)
        self.rowconfigure(0, weight=8)
        self.rowconfigure(1, weight=1)
        self.protocol("WM_DELETE_WINDOW", self.closeWindow)
        self.iconbitmap('icon.ico')

        self.data = {}
        self.create_menu()
        self.create_child_frames()
        self.get_data()
        self.count = 0

    def create_menu(self):
        menubar = tk.Menu(self)
        filemenu = tk.Menu(menubar, tearoff=0)
        filemenu.add_command(label="Save", command=self.save_file)
        filemenu.add_separator()
        filemenu.add_command(label="Exit", command=self.closeWindow)
        menubar.add_cascade(label="File", menu=filemenu)
        self.config(menu=menubar)

    def create_child_frames(self):
        self.connection_frame = connectionFrame(self, self.data)
        self.graph_frame = graphFrame(self)
        self.table_frame = tableFrame(self)

        # Assign grid positions to the child frames
        self.connection_frame.grid(
            row=0, column=0, sticky="nsew", padx=(10, 10), pady=(10, 10))
        self.table_frame.grid(
            row=1, column=0, columnspan=2, sticky="nsew", padx=(10, 10), pady=(10, 10))
        self.graph_frame.grid(
            row=0, column=1, sticky="nsew", padx=(10, 10), pady=(10, 10))

    def save_file(self):
        file_path = filedialog.asksaveasfilename(
            defaultextension=".txt", filetypes=[("Text Files", "*.txt")])
        if file_path:
            with open(file_path, 'w') as file:
                file.write(self.data_frame.title_label['text'])
                messagebox.showinfo(
                    "File Saved", "Data frame saved successfully!")

    def closeWindow(self):
        self.connection_frame.connected_status = False
        self.connection_frame.measure_status = False
        self.connection_frame.serials.close()
        if messagebox.askyesnocancel("Quit?", "Do you sure you want to quit?"):
            self.quit()
            self.destroy()
            sys.exit()

    def check_same_items(self, lst):
        if len(lst) < 2:  # If the list has less than 2 items, all items are the same
            return True

        first_item = lst[0]
        for item in lst[1:]:
            if item != first_item:
                return False

        return True

    def get_data(self):
        if ((self.connection_frame.connected_status) and (self.connection_frame.measure_status)):
            try:
                temp = self.connection_frame.serials.readline().decode().rstrip()
                val = [i for i in temp.split(",")]
                if len(val) > 2:
                    self.table_frame.insert_data(data=val)
                    # self.graph_frame.update_graph(val)
            except:
                pass

        self.after(1, self.get_data)


if __name__ == "__main__":
    app = App()
    app.mainloop()
