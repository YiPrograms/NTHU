import random
import sys
from subprocess import Popen, PIPE, STDOUT
import math
m = int(1e9 + 7)

fib = [1, 1, 1]

for i in range(3, 10000000000):
    fib.append((fib[i-1] + fib[i-2]) % m)

print("Start")

for a in range(1000, 5000):
    p = Popen(["./a.out"], stdout=PIPE, stdin=PIPE, stderr=STDOUT);
    k, _ = p.communicate(input="{}\n".format(a).encode())
    k = int(k)
    ans = fib[a] % m
    if k != ans:
        print(a, k, ans, file=sys.stderr)
    p.terminate()
