//Writen by Alan Solitar

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>


using namespace std;
using namespace ComputerVisionProjects;



int main(int argc, char **argv) {

	if (argc != 8) {
		printf("Usage: %s inputfile inputimage1 inputimage2 inputimage3 step threshold outputimage\n", argv[0]);
		return 0;
	}
	
	const string input_file(argv[1]);
	const string input_image1(argv[2]);
	const string input_image2(argv[3]);
	const string input_image3(argv[4]);
	const int threshold(stoi(argv[5]));
	const string output_image(argv[6]);

	Image an_image1,an_image2,an_image3, needle_map_image;
	if (!ReadImage(input_image1, &an_image1)) {
		cout << "Can't open file " << input_image1 << endl;
		return 0;
	}
	
	if (!ReadImage(input_image2, &an_image2)) {
		cout << "Can't open file " << input_image2 << endl;
		return 0;
	}
	if (!ReadImage(input_image3, &an_image3)) {
		cout << "Can't open file " << input_image2 << endl;
		return 0;
	}
}
/*
void CalculateStuff(Image &an_image1,Image &an_image2,Image &an_image3,int step, int threshold, map<pair<int,int>,double[3]> &normals, double matrix[3][3]){

	const int num_rows = an_image1.num_rows();
	const int num_columns = an_image1.num_columns();
	int current_step=step;
	for (size_t i = 0; i < num_rows; ++i) {
    	for (size_t j = 0; j < num_columns; ++j) {
    		if(current_step%step==0){
    			//cout << i <<" " <<j<<endl;
      			int value1 = an_image1.GetPixel(i,j);
      			int value2 = an_image2.GetPixel(i,j);
      			int value3 = an_image3.GetPixel(i,j);

      			if(value1 > threshold && value2 > threshold && value3 >threshold){
      				pair<int,int> pt{i,j};
      				double resultMatrix[3];
      				int intensities[3] = {value1,value2,value3};
      				MatrixMultiplication(matrix,intensities,resultMatrix);
      				normals[pt][0] = resultMatrix[0];
      				normals[pt][1] = resultMatrix[1];
      				normals[pt][2] = resultMatrix[2];
      			}
      		}
      		current_step++;
   		 }
	}
}
 
*/