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

void ReadInput(double matrix[3][3], string input_file);
double CalculateDeterminant(double matrix[3][3]);
void InvertMatrix(double matrix[3][3]);
double CalculateIntensity(Image &an_image);
void MatrixMultiplication(double matrix[3][3], int intensities[3], double resultMatrix[3]);
void ThresholdImage(Image &an_image, int threshold);
void CalculateStuff(Image &an_image1,Image &an_image2,Image &an_image3,int step, int threshold, map<pair<int,int>,double[3]> &normals, double matrix[3][3]);


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
	const int num_rows = an_image1.num_rows();
	const int num_columns = an_image1.num_columns();
	needle_map_image.AllocateSpaceAndSetSize(num_rows, num_columns);
  	needle_map_image.SetNumberGrayLevels(an_image1.num_gray_levels());
	

	double matrix[3][3];
	double resMatrix[3][1];
	ReadInput(matrix,input_file);
		for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout << matrix[i][j] <<" ";
		}
		cout<<endl;
	}
	
	InvertMatrix(matrix);
		for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
			cout << matrix[i][j] <<" ";
		}
		cout<<endl;
	}
	

	int distance =10;
	map<pair<int,int>,double[3]> normals;
	CalculateStuff(an_image1,an_image2,an_image3,step,threshold,normals,matrix);
	for(auto entry:normals){
		int x = entry.first.first;
		int y  = entry.first.second;
		int xEnd  = x + entry.second[0]*distance;
		int yEnd  = y + entry.second[1]*distance;
		if(x<20 && y<20)
		cout << entry.first.first << " "<<entry.first.second << ": "<< entry.second[0] <<" "<<entry.second[1] << " "<<entry.second[2]<<" "<<xEnd << " "<<yEnd <<endl;

		if(xEnd < num_rows && yEnd <num_columns && xEnd > 0 && yEnd >0)
			DrawLine(x,y,xEnd,yEnd,255,&an_image1);
	}

	if (!WriteImage(output_image, an_image1)) {
		cout << "Can't write to file " << output_image << endl;
		return 0;
	}

}
void ReadInput(double matrix[3][3], string input_file){

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


}
double CalculateDeterminant(double matrix[3][3]){


	double a = matrix[0][0]*matrix[1][1]*matrix[2][2];
	double b = matrix[1][0]*matrix[2][1]*matrix[0][2];
	double c = matrix[2][0]*matrix[0][1]*matrix[1][2];
	double d = matrix[0][0]*matrix[2][1]*matrix[1][2];
	double e = matrix[2][0]*matrix[1][1]*matrix[0][2];
	double f = matrix[1][0]*matrix[0][1]*matrix[2][2];

	return a+b+c-d-e-f;

}
void InvertMatrix(double matrix[3][3]) {

	double determinant = CalculateDeterminant(matrix);
	cout <<determinant<<endl;


		
	//double x = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]);
	//cout <<x<<endl;
	double i0j0 = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])/determinant;
	double i1j0 = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2])/determinant;
	double i2j0 = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])/determinant;
	double i0j1 = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2])/determinant;
	double i1j1 = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0])/determinant;
	double i2j1 = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1])/determinant;
	double i0j2 = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1])/determinant;
	double i1j2 = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2])/determinant;
	double i2j2 = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0])/determinant;


	 matrix[0][0] = i0j0 ;
	 matrix[1][0] = i1j0 ;
	 matrix[2][0] = i2j0 ;
	 matrix[0][1] = i0j1 ;
	 matrix[1][1] = i1j1 ;
	 matrix[2][1] = i2j1 ;
	 matrix[0][2] = i0j2 ;
	 matrix[1][2] = i1j2 ;
	 matrix[2][2] = i2j2 ;

}
double CalculateIntensity(Image &an_image){
	vector<double> intensities;

		auto brightPt = FindBrightestPixel(an_image);
		return an_image.GetPixel(brightPt.first,brightPt.second);
}
void MatrixMultiplication(double matrix[3][3], int intensities[3], double resultMatrix[3]) {
	for(int i=0;i<3;i++){
		for(int j =0;j<3;j++){
			
			resultMatrix[i]+=matrix[i][j]*intensities[j];
		}
	}


	double magnitude=0;
	for(int i=0;i<3;i++){
			magnitude+=pow(resultMatrix[i],2);
	}
		magnitude = sqrt(magnitude);
	for(int i=0;i<3;i++){
		resultMatrix[i] = resultMatrix[i]/magnitude;
	}
	
}

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
