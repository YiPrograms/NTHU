import random
import sys
from subprocess import Popen, PIPE, STDOUT
for a in range(1, 100):
    for b in range(0, 100):
        for m in range(1, 100):
            p = Popen(["./a.out"], stdout=PIPE, stdin=PIPE, stderr=STDOUT);
            k, _ = p.communicate(input="{} {} {}\n".format(a, b, m).encode())
            k = int(k)
            ans = pow(a, b, m)
            if k != ans:
                print(a, b, m, k, ans, file=sys.stderr)
