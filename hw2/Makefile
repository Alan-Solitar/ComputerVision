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

ALL_OBJ0=image.o p1.o
PROGRAM_0=p1

$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

#Program 1
ALL_OBJ1=image.o p2.o
PROGRAM_1=p2

$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

#Program 2
ALL_OBJ2=image.o p3.o
PROGRAM_2=p3

$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

#Program 3
ALL_OBJ3=image.o p4.o
PROGRAM_3=p4

$(PROGRAM_3): $(ALL_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ3) $(INCLUDES) $(LIBS_ALL)

all:
	make $(PROGRAM_0)
	make $(PROGRAM_1)
	make $(PROGRAM_2)
	make $(PROGRAM_3)



runp1: 	
		./$(PROGRAM_0) two_objects.pgm 140 p1output.pgm
runp2: 	
		./$(PROGRAM_1) p1output.pgm p2output.pgm
runp3: 	
		./$(PROGRAM_2) p2output.pgm db.txt p3output.pgm
runp4a: 	
		./$(PROGRAM_3) many_objects_1.pgm db.txt p4aoutput.pgm
runp4b: 	
		./$(PROGRAM_3) many_objects_2.pgm db.txt p4boutput.pgm





clean:
	(rm -f *.o;)

(:
