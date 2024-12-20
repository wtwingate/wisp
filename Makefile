wisp: main.c
	$(CC) main.c mpc.c -lreadline -o wisp -Wall -Wextra -pedantic -std=c99
