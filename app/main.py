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
import matplotlib.pyplot as plt
import threading, sys

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("PID Plotter - ELEKTRO UPN VETERAN JAKARTA")
        self.columnconfigure(tuple(range(2)), weight=1)
        self.rowconfigure(0, weight=1)
        self.protocol("WM_DELETE_WINDOW",  sys.exit)

        self.statusFrame = tk.Frame(
            self,
            relief=tk.RIDGE,
            bd=2,
            background="white",
            width=100
        )
        self.statusFrame.columnconfigure(tuple(range(3)), weight=1)
        self.statusFrame.rowconfigure(0, weight=30)
        self.statusFrame.rowconfigure(tuple(range(1,8)), weight=1)
        self.statusFrame.grid(row=0,  column=0, rowspan=2,
                             padx=5,  pady=5, sticky="nsew")
        
        self.GraphFrame = tk.Frame(
            self,
            relief=tk.RIDGE,
            bd=2,
            background="white",
            width=100
        )
        self.GraphFrame.columnconfigure(0, weight=1)
        self.GraphFrame.rowconfigure(0, weight=1)
        self.GraphFrame.grid(row=0,  column=1, rowspan=2,
                             padx=5,  pady=5, sticky="nsew")
        
        self.mainTitle()
        self.portTitle()
        self.selectPort()
        self.selectBaudrate()
        self.connectButton()
        self.pidTitle()
        self.pidParameter()
        self.parameterButton()
        self.graph()

        

    def mainTitle(self):
        self.main_title = tk.Label(
            self.statusFrame,
            text="FORCE BALANCE"
            )
        self.main_title.grid(
            row=0, column=0, columnspan=3, padx=5, pady=5, sticky="nswe")
    
    def portTitle(self):
        self.port_title = tk.Label(
            self.statusFrame,
            text="PORT"
            )
        self.port_title.grid(
            row=1, column=0, columnspan=3, padx=5, pady=5, sticky="nswe")


    def selectBaudrate(self):
        self.baudrate = [300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200]
        self.baudrate = tuple(self.baudrate)
        self.baudrate_value = tk.StringVar()
        self.baudrate_value.set("Select baudrate")
        self.choose_baudrate = ttk.Combobox(
            self.statusFrame,
            textvariable=self.baudrate_value)
        self.choose_baudrate['value'] = self.baudrate
        self.choose_baudrate.grid(row=3, column=0, columnspan=3,
                                        padx=5, sticky="nswe")
    
    def selectPort(self):
        ports = []
        ports = tuple(ports)
        self.port_value = tk.StringVar()
        self.port_value.set("Select Ports")
        self.choose_port = ttk.Combobox(
            self.statusFrame,
            textvariable=self.port_value)
        self.choose_port['value'] = ports
        self.choose_port.grid(row=2, column=0, columnspan=3,
                                        padx=5, sticky="nswe")
    
    def connectButton(self):
        self.connect_button = tk.Button(
            self.statusFrame,
            text="Connect",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            bg='#00ff00',
            command=self.choosen_port
        )
        self.connect_button.grid(
            row=4, column=0, columnspan=3,  sticky="nsew", pady=3, padx=(5, 1))
    
    def choosen_port(self):
        self.kp.configure(state='normal')
        self.kd.configure(state='normal')
        self.ki.configure(state='normal')
        self.parameter_button.configure(state='normal', bg='#00ff00')


    def pidTitle(self):
        self.pid_title = tk.Label(
            self.statusFrame,
            text="PID-PARAMETER"
            )
        self.pid_title.grid(
            row=5, column=0, columnspan=3, padx=5, pady=5, sticky="nswe")
    
    def pidParameter(self):
        self.choosen_kp = tk.StringVar()
        self.choosen_ki = tk.StringVar()
        self.choosen_kd = tk.StringVar()

        self.choosen_kp.set('Kp')
        self.choosen_ki.set('Ki')
        self.choosen_kd.set('Kd')

        self.kp = tk.Entry(
            self.statusFrame,
            textvariable=self.choosen_kp,
            state=tk.DISABLED,
            justify='center',
            bg="white"
        )
        self.kp.grid(
            row=6, column=0, padx=5, pady=5, sticky="nswe")
        
        self.ki = tk.Entry(
            self.statusFrame,
            textvariable=self.choosen_ki,
            state=tk.DISABLED,
            justify='center',
            bg="white"
        )
        self.ki.grid(
            row=6, column=1, padx=5, pady=5, sticky="nswe")
        
        self.kd = tk.Entry(
            self.statusFrame,
            textvariable=self.choosen_kd,
            state=tk.DISABLED,
            justify='center',
            bg="white"
        )
        self.kd.grid(
            row=6, column=2, padx=5, pady=5, sticky="nswe")

    def parameterButton(self):
        self.parameter_button = tk.Button(
            self.statusFrame,
            text="Update Parameter",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            state=tk.DISABLED,
            bg='red'
        )
        self.parameter_button.grid(
            row=7, column=0, columnspan=3,  sticky="nsew", pady=3, padx=(5, 1))
    
    def graph(self):
        self.fig, self.ax = plt.subplots()
        self.plot_graph = FigureCanvasTkAgg(self.fig, self.GraphFrame)
        self.plot_graph.get_tk_widget().grid(column=0, row=0, sticky="ns")
        
    def on_closing(self):
        if messagebox.askokcancel("Quit", "Do you want to quit?"):
            self.destroy()
            


if __name__ == '__main__':
    app = App()
    app.mainloop()