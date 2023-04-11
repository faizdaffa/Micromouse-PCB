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
from matplotlib.ticker import MaxNLocator
import matplotlib.pyplot as plt
import threading
import pandas as pd
import sys

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.count = 0

        self.title("PID Plotter - ELEKTRO UPN VETERAN JAKARTA")
        self.columnconfigure(tuple(range(2)), weight=1)
        self.rowconfigure(0, weight=1)
        self.protocol("WM_DELETE_WINDOW",  self.on_closing)

        self.statusFrame = tk.Frame(
            self,
            relief=tk.RIDGE,
            bd=2,
            background="white",
            width=100
        )
        
        self.df = {
            "N" : [],
            "gyroZ" : []
        }
        self.statusFrame.columnconfigure(tuple(range(3)), weight=1)
        self.statusFrame.rowconfigure(0, weight=30)
        self.statusFrame.rowconfigure(tuple(range(1,9)), weight=1)
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
        self.GraphFrame.rowconfigure(0, weight=100)
        self.GraphFrame.rowconfigure(1, weight=1)
        self.GraphFrame.grid(row=0,  column=1, rowspan=2,
                             padx=5,  pady=5, sticky="nsew")
        
        self.fig, self.ax = plt.subplots()
        self.plot_graph = FigureCanvasTkAgg(self.fig, self.GraphFrame)
        self.plot_graph.get_tk_widget().grid(column=0, row=0, sticky="ns")
        
        self.mainTitle()
        self.portTitle()
        self.selectPort()
        self.selectBaudrate()
        self.connectButton()
        self.pidTitle()
        self.pidParameter()
        self.parameterButton()
        self.refreshButton()
        self.startButton()
        self.pauseButton()
        self.clearButton()
        self.downloadButton()
        

    def mainTitle(self):
        self.image = Image.open('logo.png')
        basewidth = 300
        wpercent = (basewidth/float(self.image.size[0]))
        hsize = int((float(self.image.size[1])*float(wpercent)))
        self.image = self.image.resize((basewidth, hsize), Image.Resampling.LANCZOS)
        self.image = ImageTk.PhotoImage(self.image)
        self.canvas = tk.Label(self.statusFrame, image=self.image)
        self.canvas.grid(
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
        self.ports = []
        self.ports = tuple(self.ports)
        self.port_value = tk.StringVar()
        self.port_value.set("Select Ports")
        self.choose_port = ttk.Combobox(
            self.statusFrame,
            textvariable=self.port_value)
        self.choose_port['value'] = self.ports
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
            row=4, column=0, columnspan=2,  sticky="nsew", pady=3, padx=(5, 1))

    def refreshButton(self):
        self.refresh_button = tk.Button(
            self.statusFrame,
            text="Refresh",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            bg='yellow',
            command=self.update_port
        )
        self.refresh_button.grid(
            row=4, column=2,  sticky="nsew", pady=3, padx=(5, 1))
    
    def update_port(self):
        self.ports = [str(port.device) for port in serial.tools.list_ports.comports()]
        self.choose_port.configure(values=self.ports)
    
    def choosen_port(self):
        try:
            print(f"port : {self.port_value.get()}, baudrate : {self.baudrate_value.get()}")
            self.serial_arduino = serial.Serial(self.port_value.get(), baudrate=self.baudrate_value.get(), timeout=0)
            self.kp.configure(state='normal')
            self.kd.configure(state='normal')
            self.ki.configure(state='normal')
            self.parameter_button.configure(state='normal', bg='#00ff00')
            self.start_button.configure(state='normal', bg='#00ff00')
            self.pause_button.configure(state='normal', bg='yellow')
            self.clear_button.configure(state='normal', bg='red', fg='white')
                
        except:
            tk.messagebox.showerror(
                title="Device not Connected", 
                message="yang bener milih portnya blok!"
                )


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
            command=self.sendPID,
            bg='red'
        )
        self.parameter_button.grid(
            row=7, column=0, columnspan=3,  sticky="nsew", pady=3, padx=(5, 1))
    
    def sendPID(self, *args):
        self.choosen_kd=self.kd.get()
        self.choosen_ki=self.ki.get()
        self.choosen_kp=self.kp.get()
        self.serial_arduino.flushInput() 
        threading.Thread(target = self.arduinoWrite, args=["kontol"]).start()
        # self.serial_arduino.write(f"{self.kp.get()},{self.ki.get()},{self.kd.get()}".encode('utf-8'))


    def arduinoWrite(self, text):
        self.serial_arduino.write(text.encode('utf-8'))

    def plot(self):
        self.ax.clear()
        self.ax.plot(self.df["N"], self.df["gyroZ"], linewidth=1)
        self.ax.yaxis.set_major_locator(MaxNLocator(prune='lower'))
        self.ax.set_title("PID graph")
        self.plot_graph.draw()


    def startButton(self):
        self.start_button = tk.Button(
            self.statusFrame,
            text="START",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            state=tk.DISABLED,
            command=self.startMeasure,
            bg='red'
        )
        self.start_button.grid(
            row=8, column=0,  sticky="nsew", pady=3, padx=(5, 1))
    
    def pauseButton(self):
        self.pause_button = tk.Button(
            self.statusFrame,
            text="PAUSE",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            state=tk.DISABLED,
            command=self.stopMeasure,
            bg='red'
        )
        self.pause_button.grid(
            row=8, column=1,  sticky="nsew", pady=3, padx=(5, 1))
    
    def clearButton(self):
        self.clear_button = tk.Button(
            self.statusFrame,
            text="CLEAR",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            state=tk.DISABLED,
            command=self.clearMeasure,
            bg='red'
        )
        self.clear_button.grid(
            row=8, column=2,  sticky="nsew", pady=3, padx=(5, 1))
    
    def downloadButton(self):
        self.download_button = tk.Button(
            self.GraphFrame,
            text="DOWNLOAD DATA",
            relief="groove",
            highlightbackground="black",
            activebackground='red',
            command=self.donwloadedData,
            bg='#00ff00'
        )
        self.download_button.grid(
            row=1, column=0,  sticky="nsew", pady=3, padx=(5, 1))
        
    def donwloadedData(self):
        temp = pd.DataFrame(self.df)
        temp.to_excel("data.xlsx", index=False)

    def startMeasure(self):
        self.isRead = True
        threading.Thread(target=self.readSerial).start()
    
    def stopMeasure(self):
        self.isRead = False
        threading.Thread(target=self.readSerial).start()

    def clearMeasure(self):
        self.count = 0
        self.df = {
            "N" : [],
            "gyroZ" : []
        }

    def readSerial(self):
        while self.isRead:
            if self.serial_arduino.isOpen():
                val = self.serial_arduino.readline()
                while not '\\n' in str(val):
                    time.sleep(.001)
                    temp = self.serial_arduino.readline()
                    if not not temp.decode():
                        val = (val.decode()+temp.decode()).encode()
                val = val.decode().rstrip().split(',')
                if ((len(val[0]) != 0) and (len(val) != 0)):
                    self.count += 1
                    print(val)
                    self.df["gyroZ"].append(float(val[0]))
                    self.df["N"].append(self.count)
                    print(self.df["N"])
                    self.plot()
                else:
                    continue

    def on_closing(self):
        if messagebox.askokcancel("Cabut!?", "najis beneran cabut"):
            sys.exit()
            


if __name__ == '__main__':
    app = App()
    app.mainloop()