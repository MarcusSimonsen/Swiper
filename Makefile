CC = gcc

manual:
	$(CC) -o game 2048/play_manual.c

clean:
	rm game
