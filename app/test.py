import serial
import time
import argparse
import pandas as pd
import threading
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)
parser = argparse.ArgumentParser(description='Script to handle boolean and list values.')

# Add the boolean argument
parser.add_argument('-pid', '--list', nargs='+', type=float, required=True)
#parser.add_argument('-send', '--status', type=str, required=True)
args = parser.parse_args()

pid_values = args.list
#spid_status = args.statusss

serial_port = 'COM6' 
baud_rate = 9600
timeout = 5

data_string = ','.join(str(value) for value in pid_values) + '\n'
excel_file = {"Pitch":[]}

print(data_string)
fig, ax = plt.subplots()

def send_data(ser, data):
    ser.write(data.encode())

def receive_data(ser):
    timeout_duration = 1  # Duration of inactivity (in seconds) before program exit
    last_receive_time = time.time()

    while ser.is_open:
        data = ser.readline().decode().strip()
        if data:
            print("Received:", data)
            excel_file["Pitch"].append(data)
            last_receive_time = time.time()

        # Check if there has been enough inactivity to exit the program
        if time.time() - last_receive_time > timeout_duration:
            print("No data received for", timeout_duration, "seconds. Exiting program.")
            
            ser.close()
            break




if __name__ == '__main__':
    ser = serial.Serial(serial_port, baud_rate, timeout=timeout)
    send_thread = threading.Thread(target=send_data, args=(ser, data_string,))
    receive_thread = threading.Thread(target=receive_data, args=(ser,))
    try:
        send_thread.start()
        time.sleep(0.5)
        receive_thread.start()
        
    except serial.SerialException:
        print("Error in serial communication")

    send_thread.join()
    receive_thread.join()
    pd.DataFrame(excel_file).to_excel(f"Kp_{pid_values[0]}_Ki_{pid_values[1]}_Kd_{pid_values[2]}_.xlsx", index=False)
    df = pd.read_excel(f"Kp_{pid_values[0]}_Ki_{pid_values[1]}_Kd_{pid_values[2]}_.xlsx")
    ax.xaxis.set_major_locator(MultipleLocator(20))
    ax.xaxis.set_major_formatter('{x:.0f}')
    ax.xaxis.set_minor_locator(MultipleLocator(5))
    ax.plot(df.index, df["Pitch"])
    plt.savefig(f"Kp_{pid_values[0]}_Ki_{pid_values[1]}_Kd_{pid_values[2]}_.png")
    plt.show()        