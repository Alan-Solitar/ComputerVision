########################################
##
## Makefile
## LINUX compilation
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11 -Wall

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES) -c $< -o $@


#Including
INCLUDES=  -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib


#Program 0

ALL_OBJ0=image.o p1.o DisjSets.o
PROGRAM_0=p1

$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

#Program 1
ALL_OBJ1=image.o DisjSets.o p2.o
PROGRAM_1=p2

$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

all:
	make $(PROGRAM_0)
	make $(PROGRAM_1)

runp1: 	
		./$(PROGRAM_0) two_objects.pgm 140 p1output.pgm
runp2: 	
		./$(PROGRAM_1) p1output.pgm p2output.pgm




clean:
	(rm -f *.o;)

(:
