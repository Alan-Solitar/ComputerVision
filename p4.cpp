#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;
using namespace ComputerVisionProjects;




int main(int argc, char **argv) {

	if (argc != 4) {
		printf("Usage: %s file1 file2 file3\n", argv[0]);
		return 0;
	}
	const int gray_level_threshold=120;
	const string input_file(argv[1]);
	const string inputdb_file(argv[2]);
	const string output_image_file(argv[3]);

	string currentdb_file = "p4db.txt";
	Image an_image;
	if (!ReadImage(input_file, &an_image)) {
		cout << "Can't open file " << input_file << endl;
		return 0;
	}
	an_image.ConvertToBinary(gray_level_threshold);
	
	
	vector<ComputerVisionProjects::ImageStats> imgStatVec;
	string line = "";
	ifstream reader;
  	reader.open(inputdb_file);
  	while(getline(reader,line)) {
  		ComputerVisionProjects::ImageStats imgStats;
    	stringstream stream(line);
    	stream >> imgStats.label;
    	stream >> imgStats.xCenter;
    	stream >> imgStats.yCenter;
    	stream >> imgStats.area;
    	stream >> imgStats.theta;
    	stream >> imgStats.minMoment;
    	stream >> imgStats.maxMoment;
    	imgStatVec.push_back(imgStats);
    	
    }
    LabelImage(an_image);
    RecognizeObjects(an_image, imgStatVec); 
    
   if (!WriteImage(output_image_file, an_image)) {
	cout << "Can't write to file " << output_image_file << endl;
	return 0;
	}
 }

	

