import serial
import numpy as np
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import matplotlib.animation as animation

ser=serial.Serial('COM3', 115200)
class Scope(object):
    def __init__(self, ax, maxt=1, dt=.0005, color='b'):
        self.ax = ax
        self.dt = dt
        self.color=color
        self.maxt = maxt
        self.tdata = [0]
        self.ydata = [0]
        self.line = Line2D(self.tdata, self.ydata)
        self.ax.add_line(self.line)
        self.ax.set_ylim(-2000, 2000)
        self.ax.set_xlim(0, self.maxt)

    def update(self, y):
        lastt = self.tdata[-1]
        if lastt > self.tdata[0] + self.maxt:  # reset the arrays
            self.tdata = [self.tdata[-1]]
            self.ydata = [self.ydata[-1]]
            self.ax.set_xlim(self.tdata[0], self.tdata[0] + self.maxt)
            #self.ax.figure.canvas.draw()

        t = self.tdata[-1] + self.dt
        self.tdata.append(t)
        self.ydata.append(y)
        self.line.set_data(self.tdata, self.ydata)
        self.line.set_color(np.random.rand(3,1))
        return self.line,

def intTest(s):
    try:
        int(s)
        return True
    except ValueError:
        return False


def parse(str):
    returnInts=[]
    str=str.partition(' ')
    str=str[2]
    while(str!=''):
        str=str.partition(' ')
        c=str[0]
        str=str[2]
        if(intTest(c)):
            returnInts.append(int(c))
    return returnInts

def data1():
    intData=0
    while True:
        data=ser.readline(80)
        listInts=parse(data)
        if(len(listInts)==6):
            intData = listInts[0]
        yield intData
def data2():
    intData=0
    while True:
        data=ser.readline(80)
        listInts=parse(data)
        if(len(listInts)==6):
            intData = listInts[1]
        yield intData
def data3():
    intData=0
    while True:
        data=ser.readline(80)
        listInts=parse(data)
        if(len(listInts)==6):
            intData = listInts[2]
        yield intData
def data4():
    intData=0
    while True:
        data=ser.readline(80)
        listInts=parse(data)
        if(len(listInts)==6):
            intData = listInts[3]
        yield intData
def data5():
    intData=0
    while True:
        data=ser.readline(80)
        listInts=parse(data)
        if(len(listInts)==6):
            intData = listInts[4]
        yield intData
def data6():
    intData=0
    while True:
        data=ser.readline(80)
        listInts=parse(data)
        if(len(listInts)==6):
            intData = listInts[5]
        yield intData



fig, ((ax, ax2, ax3), (ax4, ax5, ax6)) = plt.subplots(2, 3, sharey=True)
fig.facecolor='black'
ax.set_title('Accelerometer x data')
ax2.set_title('Accelerometer y data')
ax3.set_title('Accelerometer z data')
ax4.set_title('Magnetometer x data')
ax5.set_title('Magnetometer x data')
ax6.set_title('Magnetometer x data')
scope = Scope(ax,2, .05,'r')
scope2 = Scope(ax2,2, .05, 'g')
scope3 = Scope(ax3,2, .05, 'k')
scope4 = Scope(ax4,2, .05, 'y')
scope5 = Scope(ax5,2, .05, 'c')
scope6 = Scope(ax6,2, .05, 'brown')


#pass a generator in "emitter" to produce data for the update func
ani = animation.FuncAnimation(fig, scope.update, data1, interval=.00001,
                              blit=True)
ani2 = animation.FuncAnimation(fig, scope2.update, data2, interval=.00001,
                              blit=True)
ani3 = animation.FuncAnimation(fig, scope3.update, data3, interval=.00001,
                               blit=True)
ani4 = animation.FuncAnimation(fig, scope4.update, data4, interval=.00001,
                              blit=True)
ani5 = animation.FuncAnimation(fig, scope5.update, data5, interval=.00001,
                              blit=True)
ani6 = animation.FuncAnimation(fig, scope6.update, data6, interval=.00001,
                             blit=True)


plt.show()