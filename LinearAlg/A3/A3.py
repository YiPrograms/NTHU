import numpy as np
import matplotlib.image as img
import matplotlib.pyplot as plt
import math

import random

# For question (4)
# you cannot use x to compute the center and the radius inside this function.
def dataSampling(x):
    return x
    # xs = list(map(lambda p: p[0], x))
    # ys = list(map(lambda p: p[1], x))

    # x_avg, y_avg = np.average(x, axis=0)
    # x_std, y_std = np.std(x, axis=0)

    # print(x_avg, y_avg, x_std, y_std)


    # xs = list(filter(lambda x: abs(x - x_avg) < 2*x_std, xs))
    # ys = list(filter(lambda x: abs(x - x_avg) < 2*y_std, ys))

    # max_x = max(xs)
    # min_x = min(xs)

    # max_y = max(ys)
    # min_y = min(ys)

    # tar_x = [(max_x * i + min_x * (5-i)) // 5 for i in range(1, 6)]
    # tar_y = [(max_y * i + min_y * (5-i)) // 5 for i in range(1, 6)]

    # print(tar_x, tar_y)

    # for xx in tar_x:
    #     plt.plot([xx, xx], [min_y, max_y])

    # for yy in tar_y:
    #     plt.plot([min_x, max_x], [yy, yy])


    # pts = list(filter(lambda p: p[0] in tar_x or p[1] in tar_y, x))
    # print(pts)
    # plt.scatter(*list(zip(*pts)))
    # return pts



def circle(sp) :
    n=len(sp)
    A = np.zeros((n, 3))
    b = np.zeros((n))
    for i in range(n):
        pt = sp[i]
        A[i, :] = [2.*pt[0], 2.*pt[1], 1]
        b[i] = pt[0]*pt[0]+pt[1]*pt[1]
    return A, b

def draw_circle(x, h, w) :
    center = [x[0], x[1]]
    radius = math.sqrt(x[2]+x[0]*x[0]+x[1]*x[1])

    x_axis = np.linspace(0, w, 700)
    y_axis = np.linspace(0, h, 700)

    a, b = np.meshgrid(x_axis, y_axis)

    C = (a - x[0])*(a - x[0]) + (b - x[1])*(b - x[1]) - radius*radius
    return a, b, C

def eclipse(sp) :
    n=len(sp)
    # TODO: How many variable should use?
    A = np.zeros((n, 5))
    b = np.ones((n))
    for i in range(n):
        pt = sp[i]
        x = pt[0]
        y = pt[1]
        # TODO: eclipse formula here.
        A[i, :] = [x*x, x*y, y*y, x, y]

    return A, b

def draw_eclipse(x, h, w) :
    # plot the drawing and the fitted circle
    x_axis = np.linspace(0, w, 700)
    y_axis = np.linspace(0, h, 700)

    a, b = np.meshgrid(x_axis, y_axis)

    # TODO: eclipse formula here.
    C = x[0]*a*a + x[1]*a*b + x[2]*b*b + x[3]*a + x[4]*b - 1

    return a, b, C

"""# DO NOT MODIFY THE JUDGE CODE!!!"""

def judge_overlapping(points) :
    # calculate all sample point circle.
    A, b = circle(points)
    sol1 = np.linalg.lstsq(A, b, rcond=None)[0]
    x1 = sol1[0]
    y1 = sol1[1]
    r1 = math.sqrt(sol1[2]+x1**2+y1**2)

    sp = dataSampling(points)
    A, b = circle(sp)
    sol2 = np.linalg.lstsq(A, b, rcond=None)[0]
    x2 = sol2[0]
    y2 = sol2[1]
    r2 = math.sqrt(sol2[2]+x2**2+y2**2)

    d = math.sqrt((x1-x2)**2 + (y1-y2)**2)

    if r1+r2 <= d :
        # 1 point or no point
        return 0
    elif min(r1, r2) + d <= max(r1, r2) :
        # inner circle
        return (min(r1, r2)**2) / (max(r1, r2)**2)
   
    alpha = math.acos((r1**2 + d**2 - r2**2) / (2 * r1 * d))
    beta = math.acos((r2**2 + d**2 - r1**2) / (2 * r2 * d))

    overlapping = alpha * (r1**2) + beta * (r2**2) - (r1**2) * math.cos(alpha) * math.sin(alpha) - (r2**2) * math.cos(beta) * math.sin(beta)

    return overlapping / (max(r1**2, r2**2)*np.pi)

def judge_sampling(points) :
    all_point = len(points)
    sp = dataSampling(points)
    sp_len = 0
    for p in sp :
        for ss in points :
            if ss[0] == p[0] and ss[1] == p[1] :
                sp_len += 1

    return (all_point - sp_len) / all_point


def judge(points) :
    overlap = judge_overlapping(points)
    sample = judge_sampling(points)

    print("The score of this question is : ")
    print("20 * (0.3 * ? (Efficiency, need your report) + 0.3 * {:f} (correctness) + 0.4 * {:f} (sampling) ) =  ? + {:f}".format(overlap, sample, 20 * (0.3 * overlap + 0.4 * sample)))

def myNormalEquation(A, b):
    lhs = np.matmul(A.T, A)
    rhs = np.matmul(A.T, b)

    # x: Solution of the least square problem using normal equation
    x = np.linalg.solve(lhs, rhs)

    # r: Sum of squared residuals, sum((y_i - f(x_i))^2)
    r = sum(map(lambda x: x*x, b - np.dot(A, x)))
    return x, r

def main(file, mode="circle") :
    # read image and get circle points
    #im1 = img.imread('puddle.png')
    figure, axes = plt.subplots(1)
    im1 = img.imread(file)
    [h, w, c] = np.array(im1).shape
    points = []
    for i in range(h):
        for j in range(w):
            if (all(im1[i,j,:])==0):
                points.append([i, j])


    # sampling data
    sp = dataSampling(points)

    if mode == "circle":
        # create matrix for fitting
        A, b = circle(sp)
        print(A, b)

        xx, rr = myNormalEquation(A, b)
        print(xx, rr)

        # solve the least square problem
        [x, r, rank] = np.linalg.lstsq(A, b, rcond=None)[0:3]
        print(x, r)
        print(rank)

        a, b, C = draw_circle(x, h, w)
    elif mode == "eclipse":
        # create matrix for fitting
        A, b = eclipse(sp)

        # solve the least square problem
        [x, r, rank] = np.linalg.lstsq(A, b, rcond=None)[0:3]

        a, b, C = draw_eclipse(x, h, w)

    plt.imshow(im1) 
    axes.contour(b, a, C, [0])
    axes.set_aspect(1)
    plt.show()
    plt.savefig(file+'.output.png')
    # judge(points)
    print("="*50)

#for f in files :
#    main('/content/drive/My Drive/' + f, mode="circle")
main('3.png', mode="eclipse")
main('x=y.png', mode="circle")
# main('/content/drive/My Drive/eclipse.png', mode="eclipse")
