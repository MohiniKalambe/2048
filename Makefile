aaa: graphics.o graph.o
	cc graphics.o graph.o -o aaa -lncurses
graph.o: graph.c graph.h
	cc -Wall-c  graph.c 
graphics.o: graphics.c graph.h	
	cc  -Wall -c graphics.c 


