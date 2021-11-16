#!/usr/bin/env python
# coding: utf-8


# Enable interactive plot
# get_ipython().run_line_magic('matplotlib', 'notebook')

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D
import numpy as np
import math
from matplotlib.animation import FuncAnimation, PillowWriter 

import sys
no_gif = len(sys.argv) >= 2 and sys.argv[1] == "NO_GIF" 

def P1P2():

    def set_object(R, T):
        # drawing
        for oo, mat in zip(objs, data):
            n = len(mat[0])
            # rotation 
            mat = np.dot(R, mat) + np.dot(T, np.ones((1,n)))
            # set the object    
            oo.set_data(mat[0], mat[1])
            oo.set_3d_properties(mat[2])
        
        return objs

    def myMovie(i):
        T = np.array([[xdata[i]], [ydata[i]], [zdata[i]]])
        R = np.eye(3)

        # Add yaw
        theta = -2*math.pi*yawdata[i]/N
        R = np.dot(R, [[ math.cos(theta), -math.sin(theta), 0], 
                    [math.sin(theta), math.cos(theta), 0], 
                    [0,              0,             1]])

        # Add pitch
        theta = 2*math.pi*pitchdata[i]/N
        R = np.dot(R, np.array([[ math.cos(theta), 0, -math.sin(theta)], 
                                [0,              1,             0],
                                [math.sin(theta), 0, math.cos(theta)]]))
        
        
        # Add roll
        theta = 2*math.pi*rolldata[i]/N
        R = np.dot(R, np.array([[1,              0,             0],
                                [0, math.cos(theta), -math.sin(theta)], 
                                [0, math.sin(theta),  math.cos(theta)]]))
        return set_object(R, T)

    # -------------- main program starts here ----------------#
    N = 100
    fig = plt.gcf()
    ax = Axes3D(fig, xlim=(-25, 15), ylim=(-5, 20), zlim=(-5, 20))


    # data matrix

    data = []

    # Right Panel
    data.append(np.array([[1, -1,  -1, -.5, -.5,  0,  .5, 1], 
                        [.5] * 8, 
                        [0,  0, .75, .75,  .5, .5, .75, 0]]))

    # Left Panel
    data.append(np.array([[1, -1,  -1, -.5, -.5,  0,  .5, 1], 
                        [-.5] * 8, 
                        [0,  0, .75, .75,  .5, .5, .75, 0]]))

    # Back Panel
    data.append(np.array([[-1] * 5, 
                        [.5, -.5, -.5,  .5, .5], 
                        [ 0,   0, .75, .75,  0]]))

    # Front Panel
    data.append(np.array([[1, .5, .5, 1, 1],
                        [.5, .5, -.5, -.5, .5], 
                        [0, .75, .75, 0, 0]]))

    # Seat
    data.append(np.array([[0, -.5, -.5, -.5, -.5, 0, 0],
                        [.5]*3 + [-.5]*3 + [.5], 
                        [.25, .25, 1.25, 1.25, .25, .25, .25]]))

    # create 3D objects list
    objs = list(map(lambda x: ax.plot3D(x[0], x[1], x[2])[0], data))


    # Create path
    x = np.array([.0, .0, .0])
    v = np.array([.01, .0, .0])
    g = np.array([.0, .0, .0])
    g_changes = [{500: -.000005, 6500: .00005, 7500: -.00003, 8500: -.00005, 9100: .00002},

                {500: .000005, 2400: -.000005, 4400: 0, 9200: -.00001, 9400: -.00001, 10400: .00001, 11900: 0},

                {500: .000005, 2800: -.000005, 4400: -.0001, 4900: .00008, 5400: .00002,
                6500: .00005, 7000: -.00005, 8500: .00005, 9500: -.0000074}]
    v_changes = [{},
                {4400: 0, 5000: -.0006, 11900: 0},
                {4400: 0}]

    xpath = []
    ypath = []
    zpath = []

    for i in range(12500):
        x += v
        xpath.append(x[0])
        ypath.append(x[1])
        zpath.append(x[2])
        # if (i % 1000 == 0):
        #     ax.scatter(x[0], x[1], x[2])
        v += g
        for k in range(3):
            if (i in g_changes[k]):
                g[k] = g_changes[k][i]
            if (i in v_changes[k]):
                v[k] = v_changes[k][i]

    ax.plot3D(xpath, ypath, zpath)


    # Trajectory data
    xdata = []
    ydata = []
    zdata = []

    cur = 0
    speed = 30
    speed_change = [(1000, 20), (2000, 12), (3000, 8), (4000, 5), (4300, 2), (4480, 50), (5000, 100), (7000, 40), (11000, 30), (11100, 20), (12000, 10)]
    cur_speedchange = 0

    # Rotation data
    yawdata = []
    pitchdata = []
    rolldata = []

    deg = np.array([.0, .0, .0])
    omega = np.array([.0, .0, .0])
    omega_change = [
        [(600, -.3), (2200, -.15), (3800, -.01), (9300, -.3), (9800, -1), (11350, 0)],
        [(600, .2), (2000, .07), (2600, .05), (3000, .03), (3300, -.1), (4480, -2), (5000, 4),
        (5600, 0), (5800, 1.5), (6300, 2), (6700, 2.5), (7400, 1.3), (9000, .6), (10000, -.5), (11100, -.13), (11700, -.02)],
        [(9400, -.5), (10800, .5), (11700, 0)]
    ]
    cur_omegachange = [0, 0, 0]


    while cur < 12500:
        xdata.append(xpath[cur])
        ydata.append(ypath[cur])
        zdata.append(zpath[cur])

        yawdata.append(deg[0])
        pitchdata.append(deg[1])
        rolldata.append(deg[2])

        if cur_speedchange < len(speed_change) and cur >= speed_change[cur_speedchange][0]:
            speed = speed_change[cur_speedchange][1]
            cur_speedchange += 1
        
        for i in range(3):
            if cur_omegachange[i] < len(omega_change[i]) \
            and cur >= omega_change[i][cur_omegachange[i]][0]:
                omega[i] = omega_change[i][cur_omegachange[i]][1]
                cur_omegachange[i] += 1
            
        deg += omega
        cur += speed


    # offset = 440
    # xdata = xdata[offset:]
    # ydata = ydata[offset:]
    # zdata = zdata[offset:]
    # yawdata = yawdata[offset:]
    # pitchdata = pitchdata[offset:]
    # rolldata = rolldata[offset:]

    ani = FuncAnimation(fig, myMovie, frames=len(xdata), interval=33)
    if not no_gif:
        print("Generating P2.gif...")
        # Using imagemagick writer is very slow and it crashes
        ani.save('P2.gif', writer='pillow', fps=30)
    plt.show()


def P3():

    def set_object(R, T):
        # drawing
        for oo, mat in zip(objs, data):
            n = len(mat[0])
            # rotation 
            mat = np.dot(R, mat) + np.dot(T, np.ones((1,n)))
            # set the object    
            oo.set_data(mat[0], mat[1])
            oo.set_3d_properties(mat[2])
        
        return objs

    def myMovie(i):
        T = np.array([[xdata[i]], [ydata[i]], [zdata[i]]])
        R = np.eye(3)

        # In P3, we add the pitch first, and then the yaw

        # Add pitch
        theta = 2*math.pi*pitchdata[i]/N
        R = np.dot(R, np.array([[ math.cos(theta), 0, -math.sin(theta)], 
                                [0,              1,             0],
                                [math.sin(theta), 0, math.cos(theta)]]))

        # Add yaw
        theta = -2*math.pi*yawdata[i]/N
        R = np.dot(R, [[ math.cos(theta), -math.sin(theta), 0], 
                    [math.sin(theta), math.cos(theta), 0], 
                    [0,              0,             1]])

        
        # Add roll
        theta = 2*math.pi*rolldata[i]/N
        R = np.dot(R, np.array([[1,              0,             0],
                                [0, math.cos(theta), -math.sin(theta)], 
                                [0, math.sin(theta),  math.cos(theta)]]))
        return set_object(R, T)

    # -------------- main program starts here ----------------#
    N = 100
    fig = plt.gcf()
    ax = Axes3D(fig, xlim=(-25, 15), ylim=(-5, 20), zlim=(-5, 20))


    # data matrix

    data = []

    # Right Panel
    data.append(np.array([[1, -1,  -1, -.5, -.5,  0,  .5, 1], 
                        [.5] * 8, 
                        [0,  0, .75, .75,  .5, .5, .75, 0]]))

    # Left Panel
    data.append(np.array([[1, -1,  -1, -.5, -.5,  0,  .5, 1], 
                        [-.5] * 8, 
                        [0,  0, .75, .75,  .5, .5, .75, 0]]))

    # Back Panel
    data.append(np.array([[-1] * 5, 
                        [.5, -.5, -.5,  .5, .5], 
                        [ 0,   0, .75, .75,  0]]))

    # Front Panel
    data.append(np.array([[1, .5, .5, 1, 1],
                        [.5, .5, -.5, -.5, .5], 
                        [0, .75, .75, 0, 0]]))

    # Seat
    data.append(np.array([[0, -.5, -.5, -.5, -.5, 0, 0],
                        [.5]*3 + [-.5]*3 + [.5], 
                        [.25, .25, 1.25, 1.25, .25, .25, .25]]))

    # create 3D objects list
    objs = list(map(lambda x: ax.plot3D(x[0], x[1], x[2])[0], data))


    # Create path
    x = np.array([.0, .0, .0])
    v = np.array([.01, .0, .0])
    g = np.array([.0, .0, .0])
    g_changes = [{500: -.000005, 6500: .00005, 7500: -.00003, 8500: -.00005, 9100: .00002},

                {500: .000005, 2400: -.000005, 4400: 0, 9200: -.00001, 9400: -.00001, 10400: .00001, 11900: 0},

                {500: .000005, 2800: -.000005, 4400: -.0001, 4900: .00008, 5400: .00002,
                6500: .00005, 7000: -.00005, 8500: .00005, 9500: -.0000074}]
    v_changes = [{},
                {4400: 0, 5000: -.0006, 11900: 0},
                {4400: 0}]

    xpath = []
    ypath = []
    zpath = []

    for i in range(12500):
        x += v
        xpath.append(x[0])
        ypath.append(x[1])
        zpath.append(x[2])
        # if (i % 1000 == 0):
        #     ax.scatter(x[0], x[1], x[2])
        v += g
        for k in range(3):
            if (i in g_changes[k]):
                g[k] = g_changes[k][i]
            if (i in v_changes[k]):
                v[k] = v_changes[k][i]

    ax.plot3D(xpath, ypath, zpath)


    # Trajectory data
    xdata = []
    ydata = []
    zdata = []

    cur = 0
    speed = 30
    speed_change = [(1000, 20), (2000, 12), (3000, 8), (4000, 5), (4300, 2), (4480, 50), (5000, 100), (7000, 40), (11000, 30), (11100, 20), (12000, 10)]
    cur_speedchange = 0

    # Rotation data
    yawdata = []
    pitchdata = []
    rolldata = []

    deg = np.array([.0, .0, .0])
    omega = np.array([.0, .0, .0])
    omega_change = [
        [(600, -.3), (2200, -.15), (3800, -.01), (9300, -.3), (9800, -1), (11350, 0)],
        [(600, .2), (2000, .07), (2600, .05), (3000, .03), (3300, -.1), (4480, -2), (5000, 4),
        (5600, 0), (5800, 1.5), (6300, 2), (6700, 2.5), (7400, 1.3), (9000, .6), (10000, -.5), (11100, -.13), (11700, -.02)],
        [(9400, -.5), (10800, .5), (11700, 0)]
    ]
    cur_omegachange = [0, 0, 0]


    while cur < 12500:
        xdata.append(xpath[cur])
        ydata.append(ypath[cur])
        zdata.append(zpath[cur])

        yawdata.append(deg[0])
        pitchdata.append(deg[1])
        rolldata.append(deg[2])

        if cur_speedchange < len(speed_change) and cur >= speed_change[cur_speedchange][0]:
            speed = speed_change[cur_speedchange][1]
            cur_speedchange += 1
        
        for i in range(3):
            if cur_omegachange[i] < len(omega_change[i]) \
            and cur >= omega_change[i][cur_omegachange[i]][0]:
                omega[i] = omega_change[i][cur_omegachange[i]][1]
                cur_omegachange[i] += 1
            
        deg += omega
        cur += speed


    # offset = 440
    # xdata = xdata[offset:]
    # ydata = ydata[offset:]
    # zdata = zdata[offset:]
    # yawdata = yawdata[offset:]
    # pitchdata = pitchdata[offset:]
    # rolldata = rolldata[offset:]

    ani = FuncAnimation(fig, myMovie, frames=len(xdata), interval=33)
    if not no_gif:
        print("Generating P3.gif...")
        # Using imagemagick writer is very slow and it crashes
        ani.save('P3.gif', writer='pillow', fps=30)
    plt.show()


def P5():

    def set_object(R):
        # drawing
        for oo, mat in zip(objs, data):
            n = len(mat[0])
            # rotation 
            mat = np.dot(R, mat)
            # set the object    
            oo.set_data(mat[0], mat[1])
            oo.set_3d_properties(mat[2])
        return objs


    def myMovie(i):
        R = np.eye(3)
        # Add yaw
        theta = 2*math.pi*yawdata[i]/180
        R = np.dot(R, [[ math.cos(theta), -math.sin(theta), 0], 
                    [math.sin(theta), math.cos(theta), 0], 
                    [0,              0,             1]])

        # Add pitch
        theta = 2*math.pi*pitchdata[i]/180
        R = np.dot(R, np.array([[ math.cos(theta), 0, -math.sin(theta)], 
                                [0,              1,             0],
                                [math.sin(theta), 0, math.cos(theta)]]))
        
        # Add roll
        theta = 2*math.pi*rolldata[i]/180
        R = np.dot(R, np.array([[1,              0,             0],
                                [0, math.cos(theta), -math.sin(theta)], 
                                [0, math.sin(theta),  math.cos(theta)]]))
        return set_object(R)

    # -------------- main program starts here ----------------#
    N = 100
    fig = plt.gcf()
    ax = Axes3D(fig, xlim=(-3, 3), ylim=(-3, 3), zlim=(-3, 3))

    # data matrix

    data = []

    # Right Panel
    data.append(np.array([[1, -1,  -1, -.5, -.5,  0,  .5, 1], 
                        [.5] * 8, 
                        [0,  0, .75, .75,  .5, .5, .75, 0]]))

    # Left Panel
    data.append(np.array([[1, -1,  -1, -.5, -.5,  0,  .5, 1], 
                        [-.5] * 8, 
                        [0,  0, .75, .75,  .5, .5, .75, 0]]))

    # Back Panel
    data.append(np.array([[-1] * 5, 
                        [.5, -.5, -.5,  .5, .5], 
                        [ 0,   0, .75, .75,  0]]))

    # Front Panel
    data.append(np.array([[1, .5, .5, 1, 1],
                        [.5, .5, -.5, -.5, .5], 
                        [0, .75, .75, 0, 0]]))

    # Seat
    data.append(np.array([[0, -.5, -.5, -.5, -.5, 0, 0],
                        [.5]*3 + [-.5]*3 + [.5], 
                        [.25, .25, 1.25, 1.25, .25, .25, .25]]))

    # create 3D objects list
    objs = list(map(lambda x: ax.plot3D(x[0], x[1], x[2])[0], data))


    # Rotation data
    yawdata = []
    pitchdata = []
    rolldata = []

    deg = np.array([.0, .0, .0])
    omega = np.array([.0, .0, .0])
    # omega_change = [
    #     [(230, 1), (230+90, 0), (230+110, -1), (230+200, 0),
    #      (810, 1), (810+90, 0), (810+110, -1), (810+200, 0)],

    #     [(0, .5), (90, 0), (110, -.5), (200, 0),
    #      (690, .5), (690+90, 0)],

    #     [(460, 1), (460+90, 0), (460+110, -1), (460+200, 0),
    #      (1050, 1), (1050+90, 0), (1050+110, -1), (1050+200, 0)]
    # ]
    omega_change = [
        [(150, 1), (150+180, 0),
         (590, 1), (590+180, 0)],

        [(0, 1), (45, 0), (100, -1), (145, 0),
         (590, 1), (590+45, 0), (590+100, -1), (590+145, 0)],

        [(360, 1), (360+180, 0),
         (590, 1), (590+180, 0)]
    ]
    cur_omegachange = [0, 0, 0]


    for cur in range(800):
        yawdata.append(deg[0])
        pitchdata.append(deg[1])
        rolldata.append(deg[2])
        
        for i in range(3):
            if cur_omegachange[i] < len(omega_change[i]) \
            and cur >= omega_change[i][cur_omegachange[i]][0]:
                omega[i] = omega_change[i][cur_omegachange[i]][1]
                cur_omegachange[i] += 1
            
        deg += omega

    # offset = 680
    # yawdata = yawdata[offset:]
    # pitchdata = pitchdata[offset:]
    # rolldata = rolldata[offset:]


    ani = FuncAnimation(fig, myMovie, frames=len(yawdata), interval=3)
    if not no_gif:
        print("Generating P5.gif...")
        ani.save('P5.gif', writer='pillow', fps=30)
    plt.show()


if __name__ == "__main__":
    P1P2()
    P3()
    P5()

