//Writen by Alan Solitar

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv) {

	if (argc != 4) {
		printf("Usage: %s inputfile threshold outputfile\n", argv[0]);
		return 0;
	}
	const string input_file(argv[1]);
	const int threshold(stoi(argv[2]));
	const string output_file(argv[3]);


	Image an_image;
	if (!ReadImage(input_file, &an_image)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}

	//convert image to binary
	an_image.ConvertToBinary(threshold);
	auto centroid = CalculateCentroid(an_image);
	cout <<centroid.first << " "<<centroid.second<<endl;
	auto radius  = CalculateRadius(an_image);
	cout << radius<<endl;

	//write to text file
	ifstream writer(output_file);

	double x = centroid.first;
	double y =centroid.second;

	string space = " ";
	writer >> centroid.first >>space >>centroid.second >> space >>radius;

	writer.close();
	/*
	if (!WriteImage(output_file, an_image)) {
		cout << "Can't write to file " << output_file << endl;
		return 0;
	}
	*/
	
}