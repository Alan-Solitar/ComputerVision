//Writen by Alan Solitar

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

std::vector<double> NormalComputations(Image an_image,pair<double,double> centroid,double radius) {
	pair<double,double> brightPt = FindBrightestPixel(an_image);
	vector<double> normal  = CalculateNormal(an_image,centroid,radius,brightPt);
	return normal;
}
void NormalizeAndWrite(std::vector<Image> images,pair<double,double> centroid, double radius, string output_file){
	ofstream writer;
	writer.open(output_file);

	for(auto image:images){

		vector<double> normal = NormalComputations(image,centroid,radius);
		for(auto n:normal){
			writer <<n << " ";
		}
		writer << endl;
	}

}
int main(int argc, char **argv) {

	if (argc != 3) {
		printf("Usage: %s inputfile1 inputimage1 inputimag2 inputimage3 outputfile\n", argv[0]);
		return 0;
	}
	const string input_file(argv[1]);
	const string input_image1(argv[2]);
	const string input_image2(argv[3]);
	const string input_image3(argv[4]);
	const string output_file(argv[5]);



	double radius;
	std:: pair<double,double> centroid;

	//read text file
	ifstream reader;
	reader.open(input_file);
	reader >>centroid.first;
	reader >> centroid.second;
	reader >> radius;

	Image an_image1, an_image2, an_image3;
	if (!ReadImage(input_image1, &an_image1)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}
	if (!ReadImage(input_image2, &an_image2)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}
	if (!ReadImage(input_image3, &an_image3)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}
	

}