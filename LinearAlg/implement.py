#!/usr/bin/env python
# coding: utf-8

import numpy as np

def EnumerateAll(mlist, m, n):
    ''' Enumerate all the n-tuple from mlist.
        where mlist contains m numbers.
        We assume m >= n.
    ''' 

    res = []
    now = []

    def dfs(idx):
        if len(now) == n:
            res.append(now[:])
        else:
            for i in range(idx, m):
                now.append(mlist[i])
                dfs(i + 1)
                now.pop()
    
    dfs(0)
    return res

def SolveLP(A, b, G):
    '''Solve the linear programming problem
        Max G(x)
        st. Ax <= b
             x >= 0
    '''
    # step 0: initialization
    maxg = 0
    
    # step 1a: enumuate all combinations
    [m, n] = A.shape
    lst = EnumerateAll(np.arange(m), m, n)
    
    # step 1b: compute all the intersection points
    points = []
    for idx in lst:
        Ai = A[idx, :]
        bi = b[idx]
        feasible = 1
        try: 
            xi = np.linalg.solve(Ai, bi)
        except np.linalg.LinAlgError:
            # Ai is singular or not square.
            feasible = 0

        # step 2: check the feasibility of the intersection point
        if feasible == 1:
            for i in range(m):
                # if np.dot(A[i,:], xi) < b[i]: # violate a constraints
                if np.dot(A[i,:], xi) - b[i] < -1e-8: # Floating point truncation: 1e-8 as tolerance
                    feasible = 0
        if feasible == 1:            # only add the feasible point
            points.append(xi)
        
    # step 3: evaluate the G function for all intersection points
    values = []
    for ptx in points:
        values.append(np.dot(G[0:n], ptx)+G[-1])
    
    # step 4: find the point with the largest value as the result
    print("Possible candidates: ", list(zip(points, values)))

    maxg = min(values)
    maxidx = values.index(maxg)
    x = points[maxidx]
    
    return x, maxg
    
#-------------------------------#
# main program starts from here.#
#-------------------------------#
# Put all the coefficients of the constrains into a matrix A and a vector b

# Ax >= b
# Note that I've changed the constrants to the form >=
# and edited line 56 that checks feasibility of an intersection
A = np.array([[ 1, 0, 0, 0, 0],
              [ 0, 1, 0, 0, 0],
              [-2, 1, 0, 0, 0],
              [ 4,-1, 0, 0, 0],
              [ 0, 0, 1, 0, 0],
              [ 0, 0, 0, 1, 0],
              [-150, -20, -1, -4, 10],
              ])
b = np.array([ 8, 12, 0, 0, 310, 500, 0])

# Minimize Gx
# Since my problem is to minimize G
# I edited line 69's max to min to find the minimum solution
G = np.array([1500, 300, 10, 40, 10, 0])

# solve this problem
[x, ming] = SolveLP(A, b, G)
print("Minimized Variables: ", x)
print("Minimized Result: {:.3f}".format(ming))


