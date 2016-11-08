//Writen by Alan Solitar

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

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


	Image an_image;
	if (!ReadImage(input_image1, &an_image)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}

	/*
	if (!WriteImage(output_file, an_image)) {
		cout << "Can't write to file " << output_file << endl;
		return 0;
	}
	*/
}