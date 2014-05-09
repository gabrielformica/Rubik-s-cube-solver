OBJSM = main.o rubik.o rubikpd.o rubiknode.o utils.o idastar.o
OBJSRPD = loadpdb.o rubikpd.o rubik.o utils.o
CFLAGS = -c
CC = g++

all: main pdb 

main: $(OBJSM)
	$(CC) $(OBJSM) -o main 

pdb: $(OBJSRPD)
	$(CC) $(OBJSRPD) -o pdb

main.o: rubik.hh rubikpd.hh
	$(CC) $(CFLAGS) main.cc

idastar.o: idastar.hh
	$(CC) $(CFLAGS) idastar.cc

rubik.o: rubik.hh 
	$(CC) $(CFLAGS) rubik.cc 

rubiknode.o: rubiknode.hh rubik.hh
	$(CC) $(CFLAGS) rubiknode.cc 

rubikpd.o: rubikpd.hh utils.hh rubik.hh
	$(CC) $(CFLAGS) rubikpd.cc 

utils.o: utils.hh 
	$(CC) $(CFLAGS) utils.cc 

loadpdb.o: rubikpd.hh
	$(CC) $(CFLAGS) loadpdb.cc

clean:
	rm -f main pdb *.o
