.PHONY: all clean test

all: lab1 test

lab1: lab1.c
	gcc lab1.c -o lab1

test: lab1
	echo "can.cs.nthu.edu.tw/index.php" | ./lab1

clean:
	rm -f lab1
