########################################
##
## Makefile
## LINUX compilation
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11

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

ALL_OBJ0=image.o s1.o
PROGRAM_0=s1

$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

#Program 1
ALL_OBJ1=image.o s2.o
PROGRAM_1=s2

$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

#Program 2
ALL_OBJ2=image.o s3.o
PROGRAM_2=s3

$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

#Program 3
ALL_OBJ3=image.o s4.o
PROGRAM_3=s4

$(PROGRAM_3): $(ALL_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ3) $(INCLUDES) $(LIBS_ALL)


all:
	make $(PROGRAM_0)
	make $(PROGRAM_1)
	make $(PROGRAM_2)
	make $(PROGRAM_3)

runs1: 	
		./$(PROGRAM_0) sphere0.pgm 110 parameters.txt
runs2: 	
		./$(PROGRAM_1) parameters.txt sphere1.pgm sphere2.pgm sphere3.pgm directions.txt

runs3: 	
		./$(PROGRAM_2) directions.txt object1.pgm object2.pgm object3.pgm 30 150  s3output.pgm

runs4:
		./$(PROGRAM_3) directions.txt object1.pgm object2.pgm object3.pgm 70  s4output.pgm
runs4b: 	
		./$(PROGRAM_3) hough_simple_2.pgm votingarrayb.txt 200 s4outputb.pgm
runs4c: 	
		./$(PROGRAM_3) hough_complex_1.pgm votingarrayc.txt 260 s4outputc.pgm





clean:
	(rm -f *.o;)

(:
