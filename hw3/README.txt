//Written by Alan Solitar

1. I completed all parts of the assignment. The written part is in the same directory as written_part.txt -- I also included a pdf version just in case

I picked different threshold values for each image.

//Threshold for edge detection
hough_simple_1 = 30
hough_simple_2 = 18
hough_complex_1 = 15

//Vote threshold
hough_simple_1 = 350
hough_simple_2 = 200
hough_complex_1 = 260

2. Not really a bug but I will say that I had some issues with the centroid approach.  In comparison
the local max approach worked very well.

I ended up using an 11x11 area for the local max
because it gave the best results

The results are good for the simple images, but the algorithm didn't detect as many lines for the complex image.

3. My program can be run with the accompanying make file.

I have included the different runs in the makefile.
They are labeled by program name and by a letter a,b, or c.

a is for hough_simple_1
b is for hough_simple_2
c is for hough_complex_1

The runs are:

runh1a: 	
runh1b: 	
runh1c: 	
runh2a: 	
runh2b: 	
runh2c: 	
runh3a: 	
runh3b: 	
runh3c: 	
runh4a: 	
runh4b: 	
runh4c: 	
		

4. All files produced by any of the programs are labeled similar by program and by also use the same
letter explained in the previous part above
	
	outputfiles:
	h1outputa.pgm
	h1outputb.pgm
	h1outputc.pgm

	h2outputa.pgm 
	h2outputb.pgm
	h2outputc.pgm
	
	h3outputa.pgm
	h3outputb.pgm
	h3outputc.pgm

	h4outputa.pgm 
	h4outputb.pgm
	h4outputc.pgm

	votingarraya.txt
	votingarrayb.txt
	votingarrayc.txt

	input files:
	hough_simple_1
	hough_simple_2
	hough_complex_1

