//Writen by Alan Solitar

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

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
	const int step(stoi(argv[5]));
	const int threshold(stoi(argv[6]));
	const string output_image(argv[7]);


	Image an_image,an_image2,an_image3;
	if (!ReadImage(input_image1, &an_image)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}

	double matrix[3][3];

	ifstream reader;
	string line="";
	
	reader.open(input_file);
	int i=0;

	for(int i=0;i<3;i++){
		getline(reader,line);
		stringstream ss(line);
		for(int j =0;j<3;j++){
			ss >> matrix[i][j];
		}
	}
	reader.close();

	for(int i=0;i<3;i++){
		for(int j =0;j<3;j++){
			cout <<  matrix[i][j] << " ";
		}
		cout<<endl;
	}
	
	//compute inverse

	//determinant
	
   	double a = (matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[1][0] * matrix[2][1] * matrix[3][2]) + (matrix[2][0] * matrix[3][1] * matrix[4][2]);
   	double b = (matrix[0][2] * matrix[1][1] * matrix[2][0]) + (matrix[1][2] * matrix[2][1] * matrix[3][0]) + (matrix[2][2] * matrix[3][1] * matrix[4][0]);
   	double determinant = a-b;

   	for(int i=0;i<3;i++){
		for(int j =0;j<3;j++){
			matrix[i][j] = (1/determinant) * matrix[i][j];
		}
	}
	//calcualte intensities

	/*
	if (!WriteImage(output_file, an_image)) {
		cout << "Can't write to file " << output_file << endl;
		return 0;
	}
	*/
}