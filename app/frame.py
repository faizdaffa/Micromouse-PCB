import serial.tools.list_ports
import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import os, time
import customtkinter 
from tkinter import ttk
from PIL import Image, ImageTk
from matplotlib.animation import FuncAnimation
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg,
    NavigationToolbar2Tk
)
from threading import Event
from matplotlib.ticker import MaxNLocator
import matplotlib.pyplot as plt
import threading
import pandas as pd
import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--kp', type=float, default=0, required=False)
parser.add_argument('--kd', type=float, default=0, required=False)
parser.add_argument('--ki', type=float, default=0, required=False)

class App(tk.Tk):
    def __init__(self, port_value, baudrate_value, parameter_pid):
        super().__init__()
        self.count = 0
        self.baudrate_value = baudrate_value
        self.port_value = port_value
        self.parameter_pid = parameter_pid

        print(parameter_pid)
        print(f"{self.baudrate_value}, {self.port_value}")

        try:
            self.serial_arduino = serial.Serial(self.port_value, baudrate=self.baudrate_value, timeout=0)
        except:
            pass
        
        self.title("PID Plotter - ELEKTRO UPN VETERAN JAKARTA")
        self.columnconfigure(tuple(range(4)), weight=1)
        self.rowconfigure(0, weight=30)
        self.rowconfigure(1, weight=1)
        self.rowconfigure(2, weight=1)
        self.protocol("WM_DELETE_WINDOW",  self.on_closing)

        self.df = {
            "N" : [],
            "gyroZ" : []
        }
        self.count = 0

        self.fig, self.ax = plt.subplots()
        self.plot_graph = FigureCanvasTkAgg(self.fig)
        self.plot_graph.get_tk_widget().grid(column=0, row=0, columnspan=4, sticky="nsew")

        self.startButton()
        self.pauseButton()
        self.clearButton()
        self.downloadButton()
        self.serialText()
        self.reconnectButton()


    def plot(self):
        self.ax.clear()
        self.ax.plot(self.df["N"], self.df["gyroZ"], linewidth=1)
        self.ax.yaxis.set_major_locator(MaxNLocator(prune='lower'))
        self.ax.set_title("PID graph")
        self.plot_graph.draw()

    def startButton(self):
        self.start_button = tk.Button(
            text="START",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            command=self.startMeasure,
            bg='#00ff00'
        )
        self.start_button.grid(
            row=1, column=0,  sticky="nsew", pady=3, padx=(5, 1))
    
    def pauseButton(self):
        self.pause_button = tk.Button(
            text="PAUSE",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            command=self.stopMeasure,
            bg='yellow'
        )
        self.pause_button.grid(
            row=1, column=1,  sticky="nsew", pady=3, padx=(5, 1))
    
    def clearButton(self):
        self.clear_button = tk.Button(
            text="CLEAR",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            command=self.clearMeasure,
            bg='red'
        )
        self.clear_button.grid(
            row=1, column=2,  sticky="nsew", pady=3, padx=(5, 1))
    
    def downloadButton(self):
        self.download_button = tk.Button(
            text="DOWNLOAD DATA",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            command=self.donwloadedData,
            bg='#00ff00'
        )
        self.download_button.grid(
            row=1, column=3,  sticky="nsew", pady=3, padx=(5, 1))
        
    def donwloadedData(self):
        temp = pd.DataFrame(self.df)
        temp.to_excel("data.xlsx", index=False)

    def startMeasure(self):
        self.isRead = True
        self.start_measure = threading.Thread(target=self.readSerial)
        self.start_measure.setDaemon(True)
        self.start_measure.start()
    
    def stopMeasure(self):
        self.isRead = False
        self.stop_measure = threading.Thread(target=self.readSerial)
        self.stop_measure.setDaemon(True)
        self.stop_measure.start()

    def clearMeasure(self):
        self.count = 0
        self.df = {
            "N" : [],
            "gyroZ" : []
        }

    def readSerial(self):
        print("kontol")
        while self.isRead:
            if self.serial_arduino.isOpen():
                self.serial_arduino.flushInput()
                val = self.serial_arduino.readline(self.serial_arduino.inWaiting())
                print(val)
        #             # self.count += 1
        #             # self.df["gyroZ"].append(float(val[0]))
        #             # self.df["N"].append(self.count)
        #             # self.plot()

    
    def reconnectButton(self):
        self.reconnect_button = tk.Button(
            text="RECONNECT",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            command=self.reconnect,
            bg='#00ff00'
        )
        self.reconnect_button.grid(
            row=2, column=3,  sticky="nsew", pady=3, padx=(5, 1))

    def reconnect(self):
        try:
            self.serial_arduino = serial.Serial(self.port_value, baudrate=self.baudrate_value, timeout=0)
        except:
            print("kontol")
            messagebox.askokcancel("blom konek", "gak konek")

    def serialText(self):
        self.serial_text = tk.Text(
            height=1,
            width=25,
            bg="white"
        )
        self.serial_text.grid(
            row=2, column=0, columnspan=3, padx=5, sticky="ew")

    def on_closing(self):
        if messagebox.askokcancel("Cabut!?", "najis beneran cabut"):
            sys.exit()                                                            

if __name__ == '__main__':
    args = parser.parse_args()
    app = App("COM7", "9600",f"{args.kp},{args.kd},{args.kd}")
    app.mainloop()