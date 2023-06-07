import tkinter as tk
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.animation import FuncAnimation
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg,
    NavigationToolbar2Tk
)
import threading
from datetime import datetime
from matplotlib.figure import Figure


class graphFrame(tk.Frame):
    def __init__(self, parent):
        super().__init__(parent, padx=10, pady=10,
                         relief=tk.RIDGE, borderwidth=5, highlightthickness=2)
        self.columnconfigure(0, weight=1)
        self.rowconfigure(0, weight=1)
        self.grid(sticky="nsew")

        self.fig = Figure(figsize=(6, 4), dpi=100)
        self.ax = self.fig.add_subplot(111)

        self.canvas = FigureCanvasTkAgg(self.fig, master=self)
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        self.label = ["Yaw", "Pitch"]
        self.data = [[0], [0]]  # Initialize with initial values
        self.timestamps = [0]  # Initialize with initial value
        self.ymin = -5
        self.ymax = 5
        self.ax.set_xlim([0, 1000])

    def update_graph(self, data):
        # Convert current time to milliseconds
        timestamp = datetime.now().timestamp() * 1000
        self.timestamps.append(timestamp)
        self.data[0].append(data[0])
        # self.data[1].append(data[1])

        # Limit the number of data points to the last 100
        if len(self.timestamps) > 100:
            self.timestamps = self.timestamps[-100:]
            self.data[0] = self.data[0][-100:]
            #self.data[1] = self.data[1][-100:]

        self.ax.clear()
        self.ax.grid()

        for i in range(1):
            self.ax.plot(self.timestamps, self.data[i], label=self.label[i])

        self.ax.legend()
        self.ax.set_ylim([self.ymin, self.ymax])
        self.canvas.draw()
