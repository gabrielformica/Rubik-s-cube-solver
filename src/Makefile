OBJSM = main.o rubik.o rubikpd.o rubiknode.o utils.o
OBJSRPD = rubikpd.o rubik.o utils.o
CFLAGS = -c
CC = g++

all: main 

main: $(OBJSM)
	$(CC) $(OBJSM) -o main 

rubikpd: $(OBJSRPD)
	$(CC) $(OBJSRPD) -o rubikpd

main.o: rubik.hh rubikpd.hh idastar.hh 
	$(CC) $(CFLAGS) main.cc

rubik.o: rubik.hh 
	$(CC) $(CFLAGS) rubik.cc 

rubiknode.o: rubiknode.hh rubik.hh
	$(CC) $(CFLAGS) rubiknode.cc 

rubikpd.o: rubikpd.hh utils.hh rubik.hh
	$(CC) $(CFLAGS) rubikpd.cc 

utils.o: utils.hh 
	$(CC) $(CFLAGS) utils.cc 

idastar.o: idastar.hh rubik.hh rubiknode.hh rubikpd.hh
	$(CC) $(CFLAGS) idastar.cc

clean:
	rm -f main rubikpd *.o
