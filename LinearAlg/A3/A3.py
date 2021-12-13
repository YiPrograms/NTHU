import numpy as np
import matplotlib.image as img
import matplotlib.pyplot as plt
import math

import random
from copy import deepcopy
	

def radixSort(x, col):
    a = np.array(x)[:,col]
    digits = int(math.log10(max(a))) + 1
    
    for d in range(digits):
        n = len(a)
        res = [0] * n
        cnt = [0] * 10

        for i in range(n):
            cnt[(a[i]//(10**d))%10] += 1

        for i in range(1, 10):
            cnt[i] += cnt[i - 1]

        for i in range(n-1, -1, -1):
            res[cnt[(a[i]//(10**d))%10] - 1] = x[i]
            cnt[(a[i]//(10**d))%10] -= 1

        for i in range(n):
            a[i] = res[i][col]
            x[i] = res[i]

    return x


# For question (4)
# you cannot use x to compute the center and the radius inside this function.
def dataSampling(x):
    xs = radixSort(deepcopy(x), 0)
    ys = radixSort(deepcopy(x), 1)
    mid_x = xs[len(xs)//2][0]
    mid_y = ys[len(ys)//2][1]

    low_x = xs[len(xs)//5][0]
    high_x = xs[len(xs)//5*4][0]

    pts = []
    for p in xs:
        if (p[0] >= mid_x and p[1] <= mid_y):
            if (p not in pts):
                pts.append(p)
            break
    for p in xs:
        if (p[0] >= mid_x and p[1] > mid_y):
            if (p not in pts):
                pts.append(p)
            break
    for p in xs:
        if (p[0] >= low_x and p[1] <= mid_y):
            if (p not in pts):
                pts.append(p)
            break
    for p in xs:
        if (p[0] >= low_x and p[1] > mid_y):
            if (p not in pts):
                pts.append(p)
            break
    for p in xs:
        if (p[0] >= high_x and p[1] <= mid_y):
            if (p not in pts):
                pts.append(p)
            break
    for p in xs:
        if (p[0] >= high_x and p[1] > mid_y):
            if (p not in pts):
                pts.append(p)
            break
    for p in ys:
        if (p[1] >= mid_y and p[0] <= mid_x):
            if (p not in pts):
                pts.append(p)
            break
    for p in ys:
        if (p[1] >= mid_y and p[0] > mid_x):
            if (p not in pts):
                pts.append(p)
            break
    return pts
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

def myNormalEquation(A, b):
    lhs = np.matmul(A.T, A)
    rhs = np.matmul(A.T, b)

    # x: Solution of the least square problem using normal equation
    x = np.linalg.solve(lhs, rhs)

    # r: Sum of squared residuals, sum((y_i - f(x_i))^2)
    r = sum(map(lambda x: x*x, b - np.dot(A, x)))
    return x, r

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

def ellipse(sp) :
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

def draw_ellipse(x, h, w) :
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

    return overlapping / (max(r1**2, r2**2) * np.pi)

def judge_sampling(points) :
    old_points = list(points)
    all_point = len(points)
    sp = dataSampling(points)
    sp_len = 0
    for p in sp :
        for ss in old_points :
            if ss[0] == p[0] and ss[1] == p[1] :
                sp_len += 1
    
    if (old_points != points) :
        return 0

    return (all_point - sp_len) / all_point


def judge(points) :
    sample = judge_sampling(points)
    overlap = judge_overlapping(points)

    print("The score of this question is : ")
    print("20 * (0.3 * ? (Efficiency, need your report) + 0.3 * {:f} (correctness) + 0.4 * {:f} (sampling) ) =  ? + {:f}".format(overlap, sample, 20 * (0.3 * overlap + 0.4 * sample)))



def main(file, mode="circle", no_sampling=False) :
    # read image and get circle points
    #im1 = img.imread('puddle.png')
    im1 = img.imread(file)
    [h, w, c] = np.array(im1).shape
    points = []
    for i in range(h):
        for j in range(w):
            if (all(im1[i,j,:])==0):
                points.append([i, j])


    # sampling data
    if no_sampling:
        sp = points
    else:
        sp = dataSampling(points)

    if mode == "circle":
        # create matrix for fitting
        A, b = circle(sp)

        # solve the least square problem
        [x, r, rank] = np.linalg.lstsq(A, b, rcond=None)[0:3]

        a, b, C = draw_circle(x, h, w)
    elif mode == "ellipse":
        # create matrix for fitting
        A, b = ellipse(sp)

        # solve the least square problem
        [x, r, rank] = np.linalg.lstsq(A, b, rcond=None)[0:3]

        a, b, C = draw_ellipse(x, h, w)
    elif mode == "normal_eq":
        # create matrix for fitting
        A, b = circle(sp)

        # solve the least square problem
        # Using my own normal equation implemention
        [x, r] = myNormalEquation(A, b)

        a, b, C = draw_circle(x, h, w)

    figure, axes = plt.subplots(1)
    plt.imshow(im1)
    axes.contour(b, a, C, [0])
    axes.set_aspect(1)

    # xxx, yyy = zip(*sp)
    # axes.scatter(yyy, xxx)

    # from scipy.spatial import Voronoi, voronoi_plot_2d
    # vor = Voronoi(list(zip(yyy, xxx)))
    # vor_far = Voronoi(list(zip(yyy, xxx)), True)
    # vx, vy = zip(*vor.vertices)
    # axes.scatter(vy, vx)
    # voronoi_plot_2d(vor, ax=axes)
    # voronoi_plot_2d(vor_far, ax=axes)

    # print([x[0], x[1]])
    # axes.scatter(x[0], x[1])
    # print(vor.vertices)
    

    plt.savefig(file+'.output.png')
    plt.show()
    points = []
    for i in range(h):
        for j in range(w):
            if (all(im1[i,j,:])==0):
                points.append([i, j])
    judge(points)
    print("="*50)

# circle_files = ['circle6.png', '1.png', '2.png', '3.png', 'case1.png', 'case2.png', 'case3.png', 'case4.png', 'case5.png', 'puddle.png', 'x=y.png']
# circle_files = ["1.png", "circle1.png", "circle2.png", "circle3.png"]
ellipse_files = ['ellipse1.png', "ellipse2.png", "3.png"]

# for f in circle_files :
#     main(f, mode="normal_eq", no_sampling=True)
for f in ellipse_files :
    main(f, mode="ellipse", no_sampling=True)

# main('x=y.png', mode="circle")
# main('2.png', mode="circle")
# main('3.png', mode="circle")
# main('x=y.png', mode="circle")
