import tkinter as tk
import threading
from tkinter import ttk, filedialog, messagebox
from PIL import Image, ImageTk
import serial
import time
import serial.tools.list_ports

BAUDRATE = [300, 600, 1200, 2400, 4800, 9600,
            14400, 19200, 28800, 38400, 57600, 115200]
CONNECT_STATUS = False


class connectionFrame(tk.Frame):
    def __init__(self, parent, data):
        super().__init__(parent, padx=10, pady=10,
                         relief=tk.RIDGE, borderwidth=5, highlightthickness=2)
        self.rowconfigure(0, weight=1)
        self.rowconfigure(1, weight=3)
        self.rowconfigure(tuple(range(2, 7)), weight=1)
        self.columnconfigure(tuple(range(2)), weight=1)
        self.grid(sticky="nsew")
        self.data = data
        self.connected_status = False
        self.measure_status = False
        # Add labels to the child frame
        label = tk.Label(self, text="PID\nPLOTTER",
                         font=("Arial", 20,  "bold"))
        label.grid(row=0, column=0, columnspan=2, sticky="ew")
        self.image = Image.open('logo.png')
        basewidth = 100
        wpercent = (basewidth/float(self.image.size[0]))
        hsize = int((float(self.image.size[1])*float(wpercent)))
        self.image = self.image.resize(
            (basewidth, hsize), Image.Resampling.LANCZOS)
        self.image = ImageTk.PhotoImage(self.image)
        self.canvas = tk.Label(self, image=self.image)
        self.canvas.grid(
            row=1, column=0, columnspan=3, padx=5, pady=5, sticky="nswe")

        # Baudrate
        self.baudrate_value = tk.StringVar()
        self.baudrate_value.set("9600")
        baud = ttk.Combobox(self, textvariable=self.baudrate_value,
                            state="readonly", values=BAUDRATE)
        baud.grid(row=2, column=0, columnspan=2, sticky="nsew", pady=(0, 10))

        # Ports
        ports = [str(port.device)
                 for port in serial.tools.list_ports.comports()]
        ports = tuple(ports)
        self.port_value = tk.StringVar()
        self.port_value.set("COM4")
        self.choose_port = ttk.Combobox(self, textvariable=self.port_value)
        self.choose_port['value'] = ports
        self.choose_port.grid(row=3, column=0, padx=(
            0, 10), sticky="nswe", pady=(0, 10))

        # refresh port
        refresh_port_button = tk.Button(
            self, text="Refresh port", command=self.update_ports, activebackground='red', bg='#00ff00')
        refresh_port_button.grid(row=3, column=1, padx=(
            10, 0), sticky="nsew", pady=(0, 10))

        # diconnect button
        self.disconnect_button = tk.Button(
            self, text="Disconnect", state=tk.DISABLED, command=self.disconnect_serial, activebackground='red', bg='red')
        self.disconnect_button.grid(
            row=4, column=1, sticky="nsew", padx=(10, 0), pady=(0, 10))

        # Connect button
        self.connect_button = tk.Button(
            self, text="Connect", command=self.get_selected_values, activebackground='red', bg='#00ff00')
        self.connect_button.grid(
            row=4, column=0, sticky="nsew", padx=(0, 10), pady=(0, 10))

        # Collect data
        self.collect_data_button = tk.Button(
            self, text="Collect data", command=self.start_measure, activebackground='red', bg='#00ff00')
        self.collect_data_button.grid(
            row=5, column=0, sticky="nsew", padx=(0, 10), pady=(0, 10))

        # Pause collect data
        self.pause_collect_data_button = tk.Button(
            self, text="Stop", command=self.stop_measure, activebackground='red', bg='#00ff00')
        self.pause_collect_data_button.grid(
            row=5, column=1, sticky="nsew", padx=(10, 0), pady=(0, 10))

        # Clear data
        self.clear_data_button = tk.Button(
            self, text="Clear data", state=tk.DISABLED, command=self.get_selected_values, activebackground='red', bg='red')
        self.clear_data_button.grid(
            row=6, column=0, columnspan=2, sticky="nsew", padx=(0, 0), pady=(0, 10))

    def get_selected_values(self):
        baudrate = self.baudrate_value.get()
        port = self.port_value.get()

        print("Baudrate:", baudrate)
        print("Port:", port)

        # try:
        self.connected_status = self.connect_serial(port, int(baudrate))
        print(f"{self.connected_status}")

        if not (self.connected_status):
            messagebox.showerror(
                "Cant connect", "There is an error in the connection")
        else:
            self.connect_button.configure(state=tk.DISABLED, bg='red')
            self.disconnect_button.configure(state="normal", bg='#00ff00')
            messagebox.showinfo("Info", "Serial is succesfully connected")

        # except:
        #     messagebox.showerror(
        #         "Cant connect", "There is an error in the connection")

    def update_ports(self):
        ports = [str(port.device)
                 for port in serial.tools.list_ports.comports()]
        ports = tuple(ports)
        self.choose_port['value'] = ports

    def connect_serial(self, port, baudrate):
        status = False
        print(port)
        self.serials = serial.Serial(
            port=port, baudrate=baudrate, timeout=1)
        if self.serials.isOpen():
            status = True
        else:
            self.serials.close()
            status = False
        return status

    def disconnect_serial(self):
        self.connected_status = False
        self.measure_status = False
        self.serials.close()
        self.connect_button.configure(state="normal", bg='#00ff00')
        self.disconnect_button.configure(state=tk.DISABLED, bg='red')
        self.collect_data_button.configure(state="normal", bg='#00ff00')
        self.pause_collect_data_button.configure(state=tk.DISABLED, bg='red')
        messagebox.showinfo("Info", "Disconnected serial")

    def start_measure(self):
        if self.connected_status:
            self.measure_status = True
            self.pause_collect_data_button.configure(
                state="normal", bg='#00ff00')
            self.collect_data_button.configure(state=tk.DISABLED, bg='red')
        else:
            messagebox.showerror(
                "Cant connect", "Connect to serial first, before collecting data")

    def stop_measure(self):
        self.measure_status = False
        self.collect_data_button.configure(state="normal", bg='#00ff00')
        self.pause_collect_data_button.configure(state=tk.DISABLED, bg='red')
