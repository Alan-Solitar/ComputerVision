//Writen by Alan Solitar

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;
using namespace ComputerVisionProjects;

std::vector<double> NormalComputations(Image an_image,pair<double,double> centroid,double radius) {
	pair<double,double> brightPt = FindBrightestPixel(an_image);
	vector<double> normal  = CalculateNormal(an_image,centroid,radius,brightPt);
	return normal;
}
double CalculateMagnitude(std::vector<double> normal) {
	int sum =0;
	for(auto i: normal){
		sum+=(i*i);
	}
	return sqrt(sum);
}
int main(int argc, char **argv) {

	if (argc != 6) {
		printf("Usage: %s inputfile1 inputimage1 inputimage2 inputimage3 outputfile\n", argv[0]);
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
	reader.close();
	cout<< radius << " "<<centroid.first<< " "<<centroid.second<<endl;

	
	Image an_image1,an_image2,an_image3;
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

	pair<double,double> brightPt1 = FindBrightestPixel(an_image1);
	vector<double> normal1  = CalculateNormal(an_image1,centroid,radius,brightPt1);
	double magnitude1 = CalculateMagnitude(normal1);
	ofstream writer;
	writer.open(output_file);

	for(auto n:normal1){
		double component = n*an_image1.GetPixel(brightPt1.first,brightPt1.second)/magnitude1;
		writer <<component << " ";
	}
	writer<<endl;

	pair<double,double> brightPt2 = FindBrightestPixel(an_image2);
	vector<double> normal2  = CalculateNormal(an_image2,centroid,radius,brightPt2);
	double magnitude2 = CalculateMagnitude(normal2);
	for(auto n:normal2){
		double component = n*an_image2.GetPixel(brightPt2.first,brightPt2.second)/magnitude2;
		writer <<component << " ";
	}
	writer<<endl;

	pair<double,double> brightPt3 = FindBrightestPixel(an_image3);
	vector<double> normal3  = CalculateNormal(an_image3,centroid,radius,brightPt3);
	double magnitude3 = CalculateMagnitude(normal3);
	
	
	for(auto n:normal3){
		double component = n*an_image3.GetPixel(brightPt3.first,brightPt3.second)/magnitude3;
		writer <<component<< " ";
	}

	
	

}