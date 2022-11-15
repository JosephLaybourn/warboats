# Macros ========================================

CC=g++
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -O -Wconversion
DIR=gnu/

OBJECTS=$(DIR)driver-sample-test0.o $(DIR)Ocean.o $(DIR)PRNG.o
OBJECTS1=$(DIR)driver-sample-test1.o $(DIR)Ocean.o $(DIR)PRNG.o
OBJECTS2=$(DIR)driver-sample-test2.o $(DIR)Ocean.o $(DIR)PRNG.o
OBJECTS3=$(DIR)driver-sample-test3.o $(DIR)Ocean.o $(DIR)PRNG.o
OBJECTS10x10=$(DIR)driver-big-10x10.o $(DIR)Ocean.o $(DIR)PRNG.o
OBJECTS8x12=$(DIR)driver-big-8x12.o $(DIR)Ocean.o $(DIR)PRNG.o
OBJECTS30x30=$(DIR)driver-big-30x30.o $(DIR)Ocean.o $(DIR)PRNG.o

OBJNODRIVERS=$(DIR)Ocean.o $(DIR)PRNG.o
OBJALLDRIVERS=$(DIR)driver-sample-test0.o $(DIR)driver-sample-test1.o $(DIR)driver-sample-test2.o$(DIR)driver-sample-test3$(DIR)driver-big-10x10.o $(DIR)driver-big-8x12.o $(DIR)driver-big-30x30.o 

EXE=warboats0.exe
EXE1=warboats1.exe
EXE2=warboats2.exe
EXE3=warboats3.exe
EXE10x10=warboats10x10.exe
EXE8x12=warboats8x12.exe
EXE30x30=warboats30x30.exe

# Targets ========================================

$(DIR)$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(DIR)$(EXE)
	$(CC) $(OBJECTS1) -o $(DIR)$(EXE1)
	$(CC) $(OBJECTS2) -o $(DIR)$(EXE2)
	$(CC) $(OBJECTS3) -o $(DIR)$(EXE3)
	$(CC) $(OBJECTS10x10) -o $(DIR)$(EXE10x10)
	$(CC) $(OBJECTS8x12) -o $(DIR)$(EXE8x12)
	$(CC) $(OBJECTS30x30) -o $(DIR)$(EXE30x30)
	$(DIR)$(EXE) > mytest0.txt
	$(DIR)$(EXE1) > mytest1.txt
	$(DIR)$(EXE2) > mytest2.txt
	$(DIR)$(EXE3) > mytest3.txt
	$(DIR)$(EXE10x10) > mytest10x10.txt
	$(DIR)$(EXE8x12) > mytest8x12.txt
	$(DIR)$(EXE30x30) > mytest30x30.txt
	diff mytest0.txt test0.txt --strip-trailing-cr
	diff mytest1.txt test1.txt --strip-trailing-cr
	diff mytest2.txt test2.txt --strip-trailing-cr
	diff mytest3.txt test3.txt --strip-trailing-cr
	diff mytest10x10.txt out-5-10-10-tt.txt --strip-trailing-cr
	diff mytest8x12.txt out-5-8-12-tt.txt --strip-trailing-cr
	diff mytest30x30.txt out-99-30-30-tt.txt --strip-trailing-cr

$(DIR)driver-sample-test0.o : driver-sample-test0.cpp $(DIR)Ocean.o 
	$(CC) $(CFLAGS) -c driver-sample-test0.cpp -o $(DIR)driver-sample-test0.o
	$(CC) $(CFLAGS) -c driver-sample-test1.cpp -o $(DIR)driver-sample-test1.o
	$(CC) $(CFLAGS) -c driver-sample-test2.cpp -o $(DIR)driver-sample-test2.o
	$(CC) $(CFLAGS) -c driver-sample-test3.cpp -o $(DIR)driver-sample-test3.o
	$(CC) $(CFLAGS) -c driver-big-10x10.cpp -o $(DIR)driver-big-10x10.o
	$(CC) $(CFLAGS) -c driver-big-8x12.cpp -o $(DIR)driver-big-8x12.o
	$(CC) $(CFLAGS) -c driver-big-30x30.cpp -o $(DIR)driver-big-30x30.o

$(DIR)Ocean.o : Ocean.cpp 
	$(CC) $(CFLAGS) -c Ocean.cpp -o $(DIR)Ocean.o
	
$(DIR)PRNG.o : PRNG.cpp 
	$(CC) $(CFLAGS) -c PRNG.cpp -o $(DIR)PRNG.o

clean :
	rm $(DIR)$(EXE) $(DIR)$(EXE1) $(DIR)$(EXE2) $(DIR)$(EXE3) $(DIR)$(EXE10x10) $(DIR)$(EXE8x12) $(OBJNODRIVERS) $(OBJALLDRIVERS)

rebuild : 
	$(MAKE) clean
	$(MAKE)

