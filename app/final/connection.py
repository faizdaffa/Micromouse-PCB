from pymodbus.client.sync import ModbusSerialClient
from pymodbus.exceptions import ConnectionException
from pymodbus.exceptions import ModbusException
import tkinter as tk
import threading
from tkinter import ttk, filedialog, messagebox
from PIL import Image, ImageTk
import serial
import serial.tools.list_ports

BAUDRATE = [300, 600, 1200, 2400, 4800, 9600,
            14400, 19200, 28800, 38400, 57600, 115200]
PARITY_LIST = ["NONE", "EVEN", "ODD"]
PARITY = ["N", "E", "O"]
DATA_BITS_LIST = ["7 Data bits", "8 Data bits"]
DATA_BITS = [7, 8]
STOP_BITS_LIST = ["1 Stop Bit", "2 Stop Bit"]
STOP_BITS = [1, 2]
CONNECT_STATUS = False


class connectionFrame(tk.Frame):
    def __init__(self, parent, data):
        super().__init__(parent, padx=10, pady=10,
                         relief=tk.RIDGE, borderwidth=5, highlightthickness=2)
        self.rowconfigure(0, weight=1)
        self.rowconfigure(1, weight=3)
        self.rowconfigure(tuple(range(2, 9)), weight=1)
        self.columnconfigure(tuple(range(2)), weight=1)
        self.grid(sticky="nsew")
        self.data = data
        self.connected_status = False
        # Add labels to the child frame
        label = tk.Label(self, text="PID\nPLOTTER",
                         font=("Arial", 20,  "bold"))
        label.grid(row=0, column=0, columnspan=2, sticky="ew")
        self.image = Image.open('logo.png')
        basewidth = 250
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

        # Parity
        self.parity_value = tk.StringVar()
        self.parity_value.set("NONE")
        parity = ttk.Combobox(
            self, textvariable=self.parity_value, state="readonly", values=PARITY_LIST)
        parity.grid(row=3, column=0, columnspan=2, sticky="nsew", pady=(0, 10))

        # Data bits
        self.databits_value = tk.StringVar()
        self.databits_value.set("7 Data bits")
        databits = ttk.Combobox(
            self, textvariable=self.databits_value, state="readonly", values=DATA_BITS_LIST)
        databits.grid(row=4, column=0, columnspan=2,
                      sticky="nsew", pady=(0, 10))

        # Stop bits
        self.stopbits_value = tk.StringVar()
        self.stopbits_value.set("1 Stop Bit")
        stopbits = ttk.Combobox(
            self, textvariable=self.stopbits_value, state="readonly", values=STOP_BITS_LIST)
        stopbits.grid(row=5, column=0, columnspan=2,
                      sticky="nsew", pady=(0, 10))

        # Stop bits
        ports = [str(port.device)
                 for port in serial.tools.list_ports.comports()]
        ports = tuple(ports)
        self.port_value = tk.StringVar()
        self.port_value.set("COM4")
        self.choose_port = ttk.Combobox(self, textvariable=self.port_value)
        self.choose_port['value'] = ports
        self.choose_port.grid(row=6, column=0, padx=(
            0, 10), sticky="nswe", pady=(0, 10))

        # refresh port
        refresh_port_button = tk.Button(
            self, text="Refresh port", command=self.update_ports, activebackground='red', bg='#00ff00')
        refresh_port_button.grid(row=6, column=1, padx=(
            10, 0), sticky="nsew", pady=(0, 10))

        # Connect button
        self.disconnect_button = tk.Button(
            self, text="Disonnect", state=tk.DISABLED, command=self.get_selected_values, activebackground='red', bg='red')
        self.disconnect_button.grid(
            row=7, column=1, sticky="nsew", padx=(10, 0), pady=(0, 10))

        # diconnect button
        self.connect_button = tk.Button(
            self, text="Connect", command=self.get_selected_values, activebackground='red', bg='#00ff00')
        self.connect_button.grid(
            row=7, column=0, sticky="nsew", padx=(0, 10), pady=(0, 10))

    def get_selected_values(self):
        baudrate = self.baudrate_value.get()
        parity = self.parity_value.get()
        bytesize = self.databits_value.get()
        stopbits = self.stopbits_value.get()
        port = self.port_value.get()

        print("Baudrate:", baudrate)
        print("Parity:", parity)
        print("Data Bits:", bytesize)
        print("Stop Bits:", stopbits)
        print("Port:", port)

        try:
            self.connected_status = self.connect_modbus(port, STOP_BITS[STOP_BITS_LIST.index(
                stopbits)],  DATA_BITS[DATA_BITS_LIST.index(bytesize)], PARITY[PARITY_LIST.index(parity)], int(baudrate))
            print(f"{self.connected_status}")

            self.data['connection'] = self.connected_status

            # Access the Frame2 instance through the parent and update the label
            data_frame = self.master.data_frame
            data_frame.title_label.config(
                text=f"Data Frame: {self.connected_status}")

            if not (self.connected_status):
                messagebox.showerror(
                    "Cant connect", "There is an error in the connection")
            else:
                self.connect_button.configure(state=tk.DISABLED, bg='red')
                self.disconnect_button.configure(state="normal", bg='#00ff00')
                messagebox.showinfo("Info", "Modbus is succesfully connected")

        except ConnectionException as ce:
            messagebox.showerror(
                "Cant connect", "There is an error in the connection")

    def update_ports(self):
        ports = [str(port.device)
                 for port in serial.tools.list_ports.comports()]
        ports = tuple(ports)
        self.choose_port['value'] = ports

    def connect_modbus(self, port, stopbits, bytesize, parity, baudrate):
        status = False
        self.client = ModbusSerialClient(
            method='rtu',
            port=port,
            stopbits=stopbits,
            bytesize=bytesize,
            parity=parity,
            baudrate=baudrate
        )

        self.client.connect()
        result = self.client.read_holding_registers(
            address=0x0,
            count=0x20,
            unit=0x1
        )

        if not result.isError():
            status = True
        else:
            status = False

        return status
