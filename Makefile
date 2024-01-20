CC = gcc

manual:
	$(CC) -o 2048 play_manual.c

clean:
	rm 2048
