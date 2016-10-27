
// Class for representing a 2D gray-scale image,
// with support for reading/writing pgm images.
// To be used in Computer Vision class.

#include "image.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <vector>
#include "DisjSets.h"
#include <math.h>
#include <fstream>


using namespace std;

namespace ComputerVisionProjects {

Image::Image(const Image &an_image){
  AllocateSpaceAndSetSize(an_image.num_rows(), an_image.num_columns());
  SetNumberGrayLevels(an_image.num_gray_levels());

  for (size_t i = 0; i < num_rows(); ++i)
    for (size_t j = 0; j < num_columns(); ++j){
      SetPixel(i,j, an_image.GetPixel(i,j));
    }
}

Image::~Image(){
  DeallocateSpace();
}

void
Image::AllocateSpaceAndSetSize(size_t num_rows, size_t num_columns) {
  if (pixels_ != nullptr) DeallocateSpace();
  pixels_ = new int*[num_rows];
  for (size_t i = 0; i < num_rows; ++i)
    pixels_[i] = new int[num_columns];

  num_rows_ = num_rows;
  num_columns_ = num_columns;
}


void Image:: ConvertToBinary(int threshold) {
	for (int i = 0; i < num_rows_; ++i) {
		for (int j = 0; j < num_columns_; ++j) {
			if (GetPixel(i, j) >= threshold) {
				SetPixel(i, j, 255);
      }
			else {
				SetPixel(i, j, 0);
      }
		}
	}
}


void
Image::DeallocateSpace() {
  for (size_t i = 0; i < num_rows_; i++)
    delete pixels_[i];
  delete pixels_;
  pixels_ = nullptr;
  num_rows_ = 0;
  num_columns_ = 0;
}

bool ReadImage(const string &filename, Image *an_image) {  
  if (an_image == nullptr) abort();
  FILE *input = fopen(filename.c_str(),"rb");
  if (input == 0) {
    cout << "ReadImage: Cannot open file" << endl;
    return false;
  }
  
  // Check for the right "magic number".
  char line[1024];
  if (fread(line, 1, 3, input) != 3 || strncmp(line,"P5\n",3)) {
    fclose(input);
    cout << "ReadImage: Expected .pgm file" << endl;
    return false;
  }
  
  // Skip comments.
  do
    fgets(line, sizeof line, input);
  while(*line == '#');
  
  // Read the width and height.
  int num_columns,num_rows;
  sscanf(line,"%d %d\n", &num_columns, &num_rows);
  an_image->AllocateSpaceAndSetSize(num_rows, num_columns);
  

  // Read # of gray levels.
  fgets(line, sizeof line, input);
  int levels;
  sscanf(line,"%d\n", &levels);
  an_image->SetNumberGrayLevels(levels);

  // read pixel row by row.
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0;j < num_columns; ++j) {
      const int byte=fgetc(input);
      if (byte == EOF) {
        fclose(input);
        cout << "ReadImage: short file" << endl;
        return false;
      }
      an_image->SetPixel(i, j, byte);
    }
  }
  
  fclose(input);
  return true; 
}

bool WriteImage(const string &filename, const Image &an_image) {  
  FILE *output = fopen(filename.c_str(), "w");
  if (output == 0) {
    cout << "WriteImage: cannot open file" << endl;
    return false;
  }
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();
  const int colors = an_image.num_gray_levels();

  // Write the header.
  fprintf(output, "P5\n"); // Magic number.
  fprintf(output, "#\n");  // Empty comment.
  fprintf(output, "%d %d\n%03d\n", num_columns, num_rows, colors);

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_columns; ++j) {
      const int byte = an_image.GetPixel(i , j);
      if (fputc(byte,output) == EOF) {
	    fclose(output);
            cout << "WriteImage: could not write" << endl;
	    return false;
      }
    }
  }

  fclose(output);
  return true; 
}

// Implements the Bresenham's incremental midpoint algorithm;
// (adapted from J.D.Foley, A. van Dam, S.K.Feiner, J.F.Hughes
// "Computer Graphics. Principles and practice", 
// 2nd ed., 1990, section 3.2.2);  
void
DrawLine(int x0, int y0, int x1, int y1, int color,
	 Image *an_image) {  
  if (an_image == nullptr) abort();

#ifdef SWAP
#undef SWAP
#endif
#define SWAP(a,b) {a^=b; b^=a; a^=b;}

  const int DIR_X = 0;
  const int DIR_Y = 1;
  
  // Increments: East, North-East, South, South-East, North.
  int incrE,
    incrNE,
    incrS,
    incrSE,
    incrN;     
  int d;         /* the D */
  int x,y;       /* running coordinates */
  int mpCase;    /* midpoint algorithm's case */
  int done;      /* set to 1 when done */
  
  int xmin = x0;
  int xmax = x1;
  int ymin = y0;
  int ymax = y1;
  
  int dx = xmax - xmin;
  int dy = ymax - ymin;
  int dir;

  if (dx * dx > dy * dy) {  // Horizontal scan.
    dir=DIR_X;
    if (xmax < xmin) {
      SWAP(xmin, xmax);
      SWAP(ymin , ymax);
    } 
    dx = xmax - xmin;
    dy = ymax - ymin;

    if (dy >= 0) {
      mpCase = 1;
      d = 2 * dy - dx;      
    } else {
      mpCase = 2;
      d = 2 * dy + dx;      
    }

    incrNE = 2 * (dy - dx);
    incrE = 2 * dy;
    incrSE = 2 * (dy + dx);
  } else {// vertical scan.
    dir = DIR_Y;
    if (ymax < ymin) {
      SWAP(xmin, xmax);
      SWAP(ymin, ymax);
    }
    dx = xmax - xmin;
    dy = ymax-ymin;    

    if (dx >=0 ) {
      mpCase = 1;
      d = 2 * dx - dy;      
    } else {
      mpCase = 2;
      d = 2 * dx + dy;      
    }

    incrNE = 2 * (dx - dy);
    incrE = 2 * dx;
    incrSE = 2 * (dx + dy);
  }
  
  /// Start the scan.
  x = xmin;
  y = ymin;
  done = 0;

  while (!done) {
    an_image->SetPixel(x,y,color);
  
    // Move to the next point.
    switch(dir) {
    case DIR_X: 
      if (x < xmax) {
	      switch(mpCase) {
	      case 1:
		if (d <= 0) {
		  d += incrE;  
		  x++;
		} else {
		  d += incrNE; 
		  x++; 
		  y++;
		}
		break;
  
            case 2:
              if (d <= 0) {
                d += incrSE; 
		x++; 
		y--;
              } else {
                d += incrE;  
		x++;
              }
	      break;
	      } 
      } else {
	done=1;
      }     
      break;

    case DIR_Y: 
        if (y < ymax) {
          switch(mpCase) {
	  case 1:
	    if (d <= 0) {
	      d += incrE;  
	      y++;
	    } else {
	      d += incrNE; 
	      y++; 
	      x++;
	    }
            break;
  
	  case 2:
	    if (d <= 0) {
                d += incrSE; 
		y++; 
		x--;
              } else {
                d += incrE;  
		y++;
	    }
            break;
	  } // mpCase
        } // y < ymin 
        else {
	  done=1;
	}
	break;    
    }
  }
}

void LabelImage( Image &an_image) {


  const double pi = 3.1415926535897;
  int current_label = 0;
  int current_Grey_Scale= 10;
  int num_sets=10000;
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();
  const int colors = an_image.num_gray_levels();
  vector<vector<int>> objectOfPixel(num_rows,vector<int>(num_columns,0));
  unordered_map<int, int> labels;

  DisjointSets labelSet(num_sets);
  unordered_map<int,int> colorsMap;

  for (size_t i = 0; i < num_rows; ++i) {
    for (size_t j = 0; j < num_columns; ++j) {
        if(an_image.GetPixel(i,j)==0) continue;  

          if(i==0 && j==0) {
            objectOfPixel[i][j]=++current_label;
            continue;
            //labelSet.unionSets(current_label,current_label);
          } 
          if(i==0) {
            objectOfPixel[i][j] = objectOfPixel[i][j-1]!=0?objectOfPixel[i][j-1]:++current_label;
            continue;
          } 
          if(j==0) {
            objectOfPixel[i][j] = objectOfPixel[i-1][j]!=0?objectOfPixel[i-1][j]:++current_label;
            continue;
          } 

            int northWest = objectOfPixel[i-1][j-1];
            int west = objectOfPixel[i][j-1];
            int north = objectOfPixel[i-1][j];
            
            //check north west neighbor
            if(northWest!=0) {
              objectOfPixel[i][j]=northWest; 
            }

            //check west neighbor
            else if(west!=0 && north==0) {
              objectOfPixel[i][j]=west;           
            }

            //check north neighbor
            else if(north!=0 && west==0) {
              objectOfPixel[i][j]=north;
            } else if(north ==0 && west ==0) {
              objectOfPixel[i][j]=++current_label;
              
            } else {  
              objectOfPixel[i][j]=north;
              int x = labelSet.Find(north);
              int y = labelSet.Find(west);
              labelSet.UnionSets(x, y);

            } 

      }


    }
    //second pass through
    for (size_t i = 0; i < num_rows; ++i) {
    for (size_t j = 0; j < num_columns; ++j) {
      if(objectOfPixel[i][j] > 0)
      {
        int pixelLabel = labelSet.Find(objectOfPixel[i][j]);
        int c = colorsMap[pixelLabel];
        if(c==0)
        {
          colorsMap[pixelLabel]=current_Grey_Scale;
          current_Grey_Scale+=20;
        }
        an_image.SetPixel(i,j,colorsMap[pixelLabel]);
      }
    }
  }

  }

void CalculateCentroid(Image &an_image, std::string output_file)
{
  const double pi = 3.1415926535897;

  unordered_map<int,int> areas;
  unordered_map<int,int> x,y;
  //unordered_map<int,float> a, aPrime,b,bPrime,c,cPrime;
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();

  //go through and calculate values needed for the orientation and centroid
  for (size_t i = 0; i < num_rows; ++i) {
    for (size_t j = 0; j < num_columns; ++j) {
      int pixelValue = an_image.GetPixel(i,j);
      if(pixelValue > 0) {
        areas[pixelValue]++;
        x[pixelValue]+=i;
        y[pixelValue]+=j;
      }
    }
  }
  int label_counter=0;
  //loop through each object
  for(auto area:areas) {
 
      //Cache values
      int pValue = area.first;
      int currentArea = area.second;

      //Centroid calculations
      double xCenter = (x[pValue])/(double)currentArea;
      double yCenter = (y[pValue])/(double)currentArea;
      cout << xCenter << " "<<yCenter<<endl;

  }
}
void CalculateRadius(Image &an_image) {
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();
  std::pair<int,int> left_most,right_most;
  std::pair<int,int> top_most,bottom_most;

 
  //loop to find left_most
  for (size_t i = 0; i < num_columns; ++i) {
    for (size_t j = 0; j < num_rows; ++j) {
      int pixelValue = an_image.GetPixel(j,i);
      if(pixelValue ==255) {
        left_most = {i,j};
        i=num_columns_;
        j=num_rows_;
      }
    }
  }

    //loop to find right most;
   for (size_t i = num_columns; i >=0; --i) {
    for (size_t j = num_rows; j >=0; --j) {
      int pixelValue = an_image.GetPixel(j,i);
      if(pixelValue ==255) {
        right_most = {i,j};
        i=j=-1;
      }
    }
  }

  //loop to find top most
  for (size_t i = 0; i < num_rows; ++i) {
    for (size_t j = 0; j < num_columns; ++j) {
      int pixelValue = an_image.GetPixel(i,j);
      if(pixelValue ==255) {
        top_most = {j,i};
        i=num_columns_;
        j=num_rows_;
      }
    }
  }

  //loop to find bottom most
  for (size_t i = num_rows; i >=0 ; --i) {
    for (size_t j = num_columns; j >=0; --j) {
      int pixelValue = an_image.GetPixel(i,j);
      if(pixelValue ==255) {
        bottom_most = {j,i};
        i=num_columns_;
        j=num_rows_;
      }
    }
  }

double diameter1 = CalculateDistance(left_most.first,left_most.second,right_most.first,right_most.second);
double diameter1 = CalculateDistance(top_most.first,top_most.second,bottom_most.first,bottom_most.second);


}

double CalculateDistance(int x1, int y1, int x2, int y2) {

  int xDif = x1-x2;
  int yDif = y1-y2;
  return sqrt(pow(xDif,2) + pow(yDif,2));

}
void RecognizeObjects(Image &an_image, vector<ComputerVisionProjects::ImageStats> imgStatVec)
{
  //to use to get max moment
  const double pi = 3.1415926535897;

  unordered_map<int,int> areas;
  unordered_map<int,int> x,y;
  unordered_map<int,float> a, aPrime,b,bPrime,c,cPrime;
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();

  //go through and calculate values needed for the orientation and centroid
  for (size_t i = 0; i < num_rows; ++i) {
    for (size_t j = 0; j < num_columns; ++j) {
      int pixelValue = an_image.GetPixel(i,j);
      if(pixelValue > 0) {
        areas[pixelValue]++;
        x[pixelValue]+=i;
        y[pixelValue]+=j;
        aPrime[pixelValue]+=pow(i,2);
        bPrime[pixelValue]+=(i*j);
        cPrime[pixelValue]+=pow(j,2);
      }
    }
  }
  int label_counter=0;
  //loop through each object
  for(auto area:areas)
    {
   
      //Cache values
      int pValue = area.first;
      int currentArea = area.second;

      //Centroid calculations
      double xCenter = (x[pValue])/(double)currentArea;
      double yCenter = (y[pValue])/(double)currentArea;

      //must mutliply by 2 per the formula
      bPrime[pValue]*=2;

      //calculate values of a, b, c
      a[pValue] = aPrime[pValue] - pow(xCenter,2)*currentArea;
      b[pValue] = bPrime[pValue] - 2*xCenter*yCenter*currentArea; 
      c[pValue] = cPrime[pValue] - pow(yCenter,2)*currentArea;  
      
      //theta, min moment, max moment calculations
      double theta = atan2(b[pValue],a[pValue]-c[pValue]);
      double minMoment = a[pValue]*pow(sin(theta),2) - b[pValue]*sin(theta)*cos(theta) + c[pValue]*pow(cos(theta),2);
      double theta2 = theta+(pi/2);
      double  maxMoment = a[pValue]*pow(sin(theta2),2) - b[pValue]*sin(theta2)*cos(theta2) + c[pValue]*pow(cos(theta2),2);
     
   
    //go through objects in db
     for(auto imgStats: imgStatVec)
     {
        double areaDifference  = fabs(imgStats.area - currentArea);
        float roundness = minMoment / maxMoment;
        float compRoundness = imgStats.maxMoment/imgStats.minMoment;
        double RoundnessDifference = fabs(roundness - compRoundness);
       if(areaDifference <150 ||RoundnessDifference<.2)
      {
          int d=30;
          int xEnd = xCenter + d*cos(theta);
          int yEnd = yCenter + d*sin(theta);

          DrawLine(xCenter,yCenter,xEnd,yEnd,255, &an_image);
          //DrawDot(an_image,xCenter,yCenter);
        }
     }
    }

}

}  // namespace ComputerVisionProjects









