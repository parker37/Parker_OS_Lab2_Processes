prog1: main.c
	gcc main.c -o prog1

prog2: main2.c
	gcc main2.c -o prog2

prog3: twoChild.c
	gcc twoChild.c -o prog3