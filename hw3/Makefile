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

ALL_OBJ0=image.o h1.o
PROGRAM_0=p1

$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

#Program 1
ALL_OBJ1=image.o h2.o
PROGRAM_1=h2

$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

#Program 2
ALL_OBJ2=image.o h3.o
PROGRAM_2=h3

$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

#Program 3
ALL_OBJ3=image.o h4.o
PROGRAM_3=h4

$(PROGRAM_3): $(ALL_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ3) $(INCLUDES) $(LIBS_ALL)


all:
	make $(PROGRAM_0)
	make $(PROGRAM_1)
	make $(PROGRAM_2)
	make $(PROGRAM_3)



runh1a: 	
		./$(PROGRAM_0) hough_simple_1.pgm h1outputa.pgm
runh1b: 	
		./$(PROGRAM_0) hough_simple_2.pgm h1outputb.pgm
runh1c: 	
		./$(PROGRAM_0) hough_complex_1.pgm h1outputc.pgm
runh2a: 	
		./$(PROGRAM_1) h1outputa.pgm 30 h2outputa.pgm
runh2b: 	
		./$(PROGRAM_1) h1outputb.pgm 18 h2outputb.pgm
runh2c: 	
		./$(PROGRAM_1) h1outputc.pgm 10 h2outputc.pgm
runh3a: 	
		./$(PROGRAM_2) h2outputa.pgm h3outputa.pgm votingarraya.txt
runh3b: 	
		./$(PROGRAM_2) h2outputb.pgm h3outputb.pgm votingarrayb.txt
runh3c: 	
		./$(PROGRAM_2) h2outputc.pgm h3outputc.pgm votingarrayc.txt
runh4a: 	
		./$(PROGRAM_3) 1 hough_simple_1.pgm votingarraya.txt 350 h4outputa.pgm
runh4b: 	
		./$(PROGRAM_3) 1 hough_simple_2.pgm votingarrayb.txt 200 h4outputb.pgm
runh4c: 	
		./$(PROGRAM_3) 1 hough_complex_1.pgm votingarrayc.txt 350 h4outputc.pgm





clean:
	(rm -f *.o;)

(:
