all: clean keygrabber

clean:
	rm -f *.o keygrabber

keygrabber: keygrabber.c
	gcc -o $@ $< -ldl -lpthread

keygrabber-solution: keygrabber-solution.c
	gcc -o $@ $< -ldl -lpthread

	
