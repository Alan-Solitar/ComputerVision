#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv) {

	if (argc != 6) {
		printf("Usage: %s flag file1 file2 threshold file 3 \n", argv[0]);
		return 0;
	}
	const int flag(stoi(argv[1]));
	const string input_file(argv[2]);
	const string input_file2(argv[3]);
	const int threshold(stoi(argv[4]));
	const string output_file(argv[5]);
	

	Image an_image;
	
	if (!ReadImage(input_file, &an_image)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}
	
	cout << flag  <<endl;
	if(flag==1)
			HoughTransform(true, an_image, input_file2, output_file, threshold);
	else{
			HoughTransform(false, an_image, input_file2, output_file, threshold);

	}

	
	/*
	if (!WriteImage(output_file, an_image)) {
		cout << "Can't write to file " << output_file << endl;
		return 0;
	}
	*/
}