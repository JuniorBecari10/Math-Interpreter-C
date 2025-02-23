all:
	gcc src/*.c -I src/include -Wall -Wextra -o interpreter -O3
