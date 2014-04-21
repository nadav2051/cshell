cshell: main.c  
	gcc main.c iomanip.c prompt.c syscall.c -o cshell -I.
clean:
	rm -rf cshell
	make
