#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv) {

	if (argc != 4) {
		printf("Usage: %s file1 file2 file3\n", argv[0]);
		return 0;
	}
	const string input_file(argv[1]);
	const string output_file(argv[2]);
	const string output_image_file(argv[3]);


	Image an_image;
	if (!ReadImage(input_file, &an_image)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}
	CalculateArea(an_image, output_file);
	
	if (!WriteImage(output_image_file, an_image)) {
		cout << "Can't write to file " << output_image_file << endl;
		return 0;
	}
	

}