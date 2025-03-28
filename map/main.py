import tkintermapview
import tkinter as tk
import threading
import serial
import time
from csv_handler import *

from math import radians, sin, cos, sqrt, atan2

def haversine(lat1, lon1, lat2, lon2):
    return 6371 * (2 * atan2(sqrt(a := sin((dlat := radians(lat2 - lat1)) / 2)**2 + cos(radians(lat1)) * cos(radians(lat2)) * sin((dlon := radians(lon2 - lon1)) / 2)**2), sqrt(1 - a)))

#sigma constants
TEMPERATURE = 0x00
PRESSURE = 0x01
LATITUDE = 0x02
LONGITUDE = 0x03
ACCELERATION_X = 0x04
ACCELERATION_Y = 0x05
ACCELERATION_Z = 0x06
GYRO_X = 0x07
GYRO_Y = 0x08
GYRO_Z = 0x09
LIGHT = 0x0A
BASEB = 0x0B
GSLAT = 0x0C
GSLON = 0x0D



#sigma main class
class Win:

    def PrintData(self) -> None:
        print("temperature:", self.rawdata[TEMPERATURE])
        print("pressure:", self.rawdata[PRESSURE])
        print("latitude:", self.rawdata[LATITUDE])
        print("longitude:", self.rawdata[LONGITUDE])
        print("acceleration_x:", self.rawdata[ACCELERATION_X])
        print("acceleration_y:", self.rawdata[ACCELERATION_Y])
        print("acceleration_z:", self.rawdata[ACCELERATION_Z])
        print("gyro_x:", self.rawdata[GYRO_X])
        print("gyro_y:", self.rawdata[GYRO_Y])
        print("gyro_z:", self.rawdata[GYRO_Z])
        print("light:", self.rawdata[LIGHT])
        print("baseb:", self.rawdata[BASEB])



    #new skibidi update function
    def update(self) -> None:
        for widget in self.data_frame.winfo_children():
            widget.destroy()
        self.write_data()
        # self.PrintData()
        self.root.after(1000, self.update)

    #sigma data
    def write_data(self) -> None:

        for i in range(len(self.datanames)):
            label = tk.Label(self.data_frame, text=f"{self.datanames[i]}{self.rawdata[i]}", font=("Arial", 12), bg="lightgrey")
            label.pack(anchor="nw")
        
        distance = round(haversine(self.rawdata[2], self.rawdata[3], self.rawdata[12], self.rawdata[13]), 6)
        label = tk.Label(self.data_frame, text=f"distance:{distance*1000}", font=("Arial", 12), bg="lightgrey")
        label.pack(anchor="nw")
        # for name, value in self.data.items(): 
        #     label = tk.Label(self.data_frame, text=f"{name}:{value}", font=("Arial", 12), bg="lightgrey")
        #     label.pack(side="top", anchor="nw")
        self.marker_of_prediction.set_position(self.rawdata[LATITUDE], self.rawdata[LONGITUDE])
        self.GS_marker.set_position(self.rawdata[GSLAT], self.rawdata[GSLON])


    def __init__(self) -> None:
        #create sigma window
        self.root = tk.Tk()
        self.root.title("Sigma fish map")
        self.root.geometry("1920x1080")  
        self.timer = time.time()
        self.ser = serial.Serial('/dev/ttyUSB0', baudrate=115200, timeout=1)
        data = self.ser.readline().decode('utf-8').strip()
    
        self.datanames = [
            "Temperature:",
            "Pressure:",
            "Latitude:",
            "Longitude:",
            "Accel X:",
            "Accel Y:",
            "Accel Z:",
            "Gyro X:",
            "Gyro Y:",
            "Gyro Z:",
            "Light:",
            "Base Pressure:",
            "GS latitude",
            "GS longitude",
            "RSSI:"
        ]


        self.rawdata = [
            0.0, #Temperature
            0.0, #Pressure
            63.0, #Latitude
            0, #Longitude
            0, #accel X
            0, #accel Y
            0, #accel Z
            0, #Gyro X
            0, #Gyro Y
            0, #Gyro Z
            0, #Light 
            0, #Base p
            0, #GS latitude
            0, #GS longitude/
            0, #RSSI
            0, #BASESERVOANGLE
            0, #ANTENNASRVOANGLE
        ]

        self.rawdatatimestpams = [
            0.0, #Temperature
            0.0, #Pressure
            63.0, #Latitude
            0, #Longitude
            0, #accel X
            0, #accel Y
            0, #accel Z
            0, #Gyro X
            0, #Gyro Y
            0, #Gyro Z
            0, #Light 
            0, #Base p
            0, #GS latitude
            0,  #GS longitude
            0,
            0,
            0,
        ]



        self.dir = str(init_csv())+"/"

        self.zoom = 15
        #coordinates 
        self.start_latitude, self.start_longitude = 63.094227, 21.608214
        #create sigma Frames 
        self.map_frame = tk.Frame(self.root, width=600, height=600)
        self.data_frame = tk.Frame(self.root, width=400, height=600, bg="lightgrey")
        self.marker_latitude, self.marker_longitude = 63.094227, 21.608214

        #some settings that I found in google that allow window to scale properly
        self.root.grid_rowconfigure(0, weight=1)
        self.root.grid_columnconfigure(0, weight=1)
        self.root.grid_columnconfigure(1, weight=0)


        #assign sigma frames to sigma grids
        self.map_frame.grid(row=0, column=0, sticky="nsew")
        self.data_frame.grid(row=0, column=1, sticky="nsew")

        #create sigma map
        self.map_widget = tkintermapview.TkinterMapView(self.map_frame, width=600, height=600)
        self.map_widget.pack(fill="both", expand=True)
        self.map_widget.set_position(self.start_latitude, self.start_longitude)  
        self.map_widget.set_zoom(self.zoom)

        self.marker_of_prediction = self.map_widget.set_marker(0,0)
        self.GS_marker = self.map_widget.set_marker(0,0)
        
        self.thread = threading.Thread(target=self.ReadSerial, args=(), daemon=True)
        self.thread.start()

        self.root.after(100, self.update)
        self.root.mainloop()
    
    def ReadSerial(self):
        while True:
            data = self.ser.readline().decode('utf-8').strip()
            if data:
                try:
                    arr = data.split(" ")
                    if (len(arr) != 3): continue
                    if (int(arr[0]) != 15 and int(arr[0]) != 16):print(data)
                    self.rawdata[int(arr[0])] = float(arr[2])
                    self.rawdatatimestpams[int(arr[0])] = int(arr[1])
                    write_to_csv(self.dir, int(arr[0]), float(arr[1]), float(arr[2]))
                except:
                    pass






if __name__ == "__main__":
    window = Win()
    


