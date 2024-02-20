import serial
from collections import deque

import matplotlib.pyplot as plt 
import matplotlib.animation as animation

# strPort = '/dev/tty.usbserial-A7006Yqh'
strPort = 'COM15'
varNames = ["setpoint", "filtered velocity", "control effort"]
    
class LinePlot:
    def __init__(self, strPort, maxLen, varNames, baudRate = 115200):
        self.serial = serial.Serial(strPort)
        if not self.serial.is_open:
            print("Could not open serial port.")

        self.maxLen = maxLen
        self.varNames = varNames
        assert(len(varNames) >= 1)
      
        self.time = deque()
        self.vars = [deque() for _ in varNames]

    def add(self, data):
        if len(self.time) >= self.maxLen:
            self.time.popleft()
            for i in range(len(self.varNames)):
                self.vars[i].popleft()
                
        self.time.append(data[0])
        for i in range(len(self.varNames)):
            self.vars[i].append(data[i+1])

    def update(self, frameNum, plots, ax):
        assert(len(plots) == len(self.varNames))
        data = [float(val) for val in self.serial.readline().decode().split()]
        if len(data) == len(self.varNames) + 1:
            self.add(data)
            for i in range(len(plots)):
                plots[i].set_data(self.time, self.vars[i])
        ax.relim()
        ax.autoscale_view()
                
    def close(self):
        self.serial.flush()
        self.serial.close()    

linePlot = LinePlot(strPort, 100, varNames)
        
fig = plt.figure()
ax = plt.axes()
plots = [ax.plot([], [], label=name)[0] for name in varNames]
ax.legend(loc='upper left')

anim = animation.FuncAnimation(fig, linePlot.update, 
                                fargs=[plots, ax], 
                                interval=25)
  
plt.show()

linePlot.close()
        