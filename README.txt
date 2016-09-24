
1. All parts were completed
*My Threshold value is 140 and it is used inside the run in the make file
*My format for the database rows is label xCenter, yCenter, Area, Theta, Min Factor, Max Factor
2. I am recognizing one extra object for many_objects_1.pgm.  I tried a lot of things for recognizing but had many problems with roundess, min factors, max factors and the like not being close enough. I spent many hours on it and was able to get some recognition but it's definitely not robust. Parts 1-3 look good though. Also, it's not really an error, but the dot in the center is hard to see -- it's there though.

3. My program can be run with the accompanying make file.  

Please run Make clean && Make all followed by:

Make runp1
Make runp2
Make runp3
Make runp4a
Make runp4b