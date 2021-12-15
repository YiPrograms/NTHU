import numpy as np
import matplotlib.image as img
import matplotlib.pyplot as plt
import math

import random
from copy import deepcopy

import itertools

# Studied here: https://dccg.upc.edu/people/vera/Applet/smallest_enclosing_circle.html#explanation
# Input: points
# Output: Vertices of the farthest-point voronoi diagram
def farthestPointVoronoi(pts):

    # Find the convex hull of the points
    from scipy.spatial import ConvexHull
    ch = list(map(lambda i: pts[i], ConvexHull(pts).vertices))

    vertices = []

    while len(ch) >= 3:
        # Find largest circle formed by consective 3 pts on CH
        cir = ((0, 0), -1, -1)
        for i in range(len(ch)):
            x1, y1 = ch[i-1]
            x2, y2 = ch[i]
            x3, y3 = ch[i+1 if i+1 < len(ch) else 0]

            # Calculate the center and radius
            c = (x1-x2)**2 + (y1-y2)**2
            a = (x2-x3)**2 + (y2-y3)**2
            b = (x3-x1)**2 + (y3-y1)**2
            s = 2*(a*b + b*c + c*a) - (a*a + b*b + c*c) 
            cx = (a*(b+c-a)*x1 + b*(c+a-b)*x2 + c*(a+b-c)*x3) / s
            cy = (a*(b+c-a)*y1 + b*(c+a-b)*y2 + c*(a+b-c)*y3) / s 
            ar = math.sqrt(a)
            br = math.sqrt(b)
            cr = math.sqrt(c)
            r = ar*br*cr / math.sqrt((ar+br+cr)*(-ar+br+cr)*(ar-br+cr)*(ar+br-cr))

            if r > cir[1]:
                # Save the center coordinate, the radius and the point that forms the circle
                cir = ((cx, cy), r, i)

        # The largest circle's center is an vertex on the diagram
        vertices.append(cir[0])
        # Remove the point that forms the circle
        ch.pop(cir[2])
    
    # if len(ch) == 2:
    #     vertices.append(((ch[0][0]+ch[1][0])/2, (ch[0][1]+ch[1][1])/2))
    return vertices

# Using vertices of the farthest-point voronoi diagram to find the minimum enclosing circle
# Input: points, height, width
# Output: center of the enclosing circle,
#         cradius of the enclosing circle,
#         vertices of the farthest-point voronoi diagram
def minimumEnclosingCircle(pts):
    vertices = farthestPointVoronoi(pts)

    # Add the cases that the circle is formed by the diameter of two points
    candidates = vertices[:]
    for a, b in itertools.combinations(pts, 2):
        candidates.append(((a[0]+b[0])/2, (a[1]+b[1])/2))
    
    # Find the enclosing circle with the smallest radius
    # which is the minimum enclosing circle
    min_cir = ((0, 0), 1e20)
    for c in candidates:
        r_sq = max((p[0]-c[0])**2 + (p[1]-c[1])**2 for p in pts)
        if r_sq < min_cir[1]:
            min_cir = (c, r_sq)
    
    radius = math.sqrt(min_cir[1])
    c = min_cir[0]
    return c, radius, vertices
    

## Generate random points and find its minimum enclosing circle
## Input: Number of random points
def drawMinimumEnclosingCircle(n = 10):
    h = w = 500

    points = []
    i = 0
    while i < n:
        x = random.randint(h//4, h//4*3)
        y = random.randint(w//4, w//4*3)
        if (x, y) in points:
            continue
        points.append((x, y))
        i += 1

    figure, axes = plt.subplots(1)
    plt.xlim([0, h])
    plt.ylim([0, w])
    plt.gca().set_aspect('equal', adjustable='box')

    center, radius, vertices = minimumEnclosingCircle(points)

    # Draw points
    xs, ys = zip(*points)
    axes.scatter(xs, ys)

    # Draw vertices
    xs, ys = zip(*vertices)
    axes.scatter(xs, ys)

    # Draw minimum enclosing circle
    x_axis = np.linspace(0, w, 700)
    y_axis = np.linspace(0, h, 700)

    a, b = np.meshgrid(x_axis, y_axis)

    C = (a - center[0])*(a - center[0]) + (b - center[1])*(b - center[1]) - radius*radius
    axes.contour(a, b, C, [0])

    # Draw center
    axes.scatter([center[0]], [center[1]], s=3)

    plt.show()



def countingSort(x):
    n = len(x)
    res = [0] * n
    cnt = [0] * 360
    
    for i in range(n):
        cnt[x[i][2]] += 1

    for i in range(1, 360):
        cnt[i] += cnt[i - 1]

    for i in range(n-1, -1, -1):
        res[cnt[x[i][2]] - 1] = x[i]
        cnt[x[i][2]] -= 1

    for i in range(n):
        x[i] = res[i]

    return x

# For question (4)
# you cannot use x to compute the center and the radius inside this function.
def dataSampling(x):
    xs, ys = list(zip(*x))

    # Calculate the central of gravity
    avgx = sum(xs) / len(xs)
    avgy = sum(ys) / len(ys)

    # Calculate the angle from central of gravity for each point
    # and append the information to the point
    ax = list(map(lambda xi: (*xi, int((math.atan2(xi[1] - avgy, xi[0] - avgx) + math.pi) * 360 // (2*math.pi))), x))

    # For fail safe, if the angle range exceeds normal range
    ax = list(filter(lambda xi: xi[2] >= 0 and xi[2] < 360, ax))

    # Use counting sort to sort the points by angle
    # Complexity: O(n + 360) = O(n)
    ax = countingSort(ax)

    pts = []
    # Function to avoid adding duplicate points
    def addPt(p):
        x, y, ang = p
        if (x, y) not in pts:
            pts.append((x, y))
    
    # Sample 1.5% of points or a minimum of 6 points
    n_sample = max(6, int(len(ax) * 0.015))
    for i in range(n_sample):
        addPt(ax[len(ax) // n_sample * i])

    return pts

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


def main(file, mode="circle", no_sampling=False, draw_sample=False) :
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

    if draw_sample:
        xxx, yyy = zip(*sp)
        axes.scatter(yyy, xxx)

    plt.savefig(file+'.output.png')
    plt.show()
    points = []
    for i in range(h):
        for j in range(w):
            if (all(im1[i,j,:])==0):
                points.append([i, j])
    judge(points)
    print("="*50)

circle_files = ['case1.png', 'case2.png', 'case3.png', 'case4.png', 'case5.png', 'puddle.png', 'x=y.png']
ellipse_files = ['ellipse1.png', "ellipse2.png", "ellipse3.png"]

for f in circle_files :
    main(f, mode="circle")
for f in ellipse_files :
    main(f, mode="ellipse")

for i in range(10, 15):
    drawMinimumEnclosingCircle(i)
