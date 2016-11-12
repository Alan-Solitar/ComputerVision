1. I have completed s1,s2, but am having problems with the inverse for s3,s4

The formula I used to compute the normals was deltaZ = r^2 - (deltaX)^2 - (deltaY)^2 

2.I am having issues with the inverse and thus my needle map is incorrect

3.My program can be run with the accompanying make file using the command:

make clean && make all

I have include some runs that can be run with make runsx

make runs1
make runs2
make runs3
make runs4


4.
input files:

input for s1: sphere0.pgm
input for s2: parameters.txt sphere1.pgm,sphere2.pgm,sphere3.pgm
input for s3: directions.txt object1.pgm object2.pgm object3.pgm
input for s4: directions.txt object1.pgm object2.pgm object3.pgm

output for s1: parameters.txt
output for s2: directions.txt
output for s3: s3output.pgm
output for s4: s4output.pgm

