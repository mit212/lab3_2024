import serial
from collections import deque

import matplotlib.pyplot as plt 
import matplotlib.animation as animation

# strPort = '/dev/tty.usbserial-A7006Yqh'
strPort = 'COM9'
    
class PathPlot:
    def __init__(self, strPort, maxLen, baudRate = 115200):
        self.serial = serial.Serial(strPort)
        if not self.serial.is_open:
            print("Could not open serial port.")

        self.maxLen = maxLen
      
        self.x = deque()
        self.y = deque()

    def add(self, data):
        if len(self.x) >= self.maxLen:
            self.x.popleft()
            self.y.popleft()
                
        self.x.append(data[0])
        self.y.append(data[1])

    def update(self, frameNum, plot, ax):
        data = [float(val) for val in self.serial.readline().decode().split("")]
        if len(data) == 2:
            self.add(data)
            plot.set_data(self.x, self.y)
        ax.relim()
        ax.autoscale_view()
                
    def close(self):
        self.serial.flush()
        self.serial.close()    

pathPlot = PathPlot(strPort, 100)
        
fig = plt.figure()
ax = plt.axes()
plot = ax.plot([], [])[0] 

anim = animation.FuncAnimation(fig, pathPlot.update, 
                                fargs=[plot, ax], 
                                interval=25)
  
plt.show()

pathPlot.close()
        