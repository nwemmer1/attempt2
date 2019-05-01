#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <sstream>

struct Point 
{
	int x,y;
};

int main(int argc, char *argv[])
{

   if (argc != 4)
   {
      std::cout << "wrong format! should be \"a.exe imageFile.pgm vertSeams horizSeams\"";
      return 0;
   }
   else
   {
     // If the user's input is valid, store their input
     // user inputted image file name
   	 std::vector<Point> verticalSeam;
   	 std::vector<Point> horizontalSeam;
      std::string imageFileName = argv[1];
     // the number of vertical seams to be removed
      int vertSeamsInt = atoi(argv[2]);
     // the numner of horizontal seams to be removed
      int horizSeamsInt = atoi(argv[3]);
     //make 'imageFile' the first argument inputted from command line
      std::ifstream imageFile;
      std::string p2;
      imageFile.open(imageFileName);
      std::getline(imageFile, p2);
     // Read in the values from the given image file
      int xWidth, yHeight, maxValue;
      std::string comment = "";
      std::getline(imageFile, comment);
      std::string dimensionStr, maxValStr;
      std::getline(imageFile, dimensionStr);
      std::getline(imageFile, maxValStr);


      std::stringstream dim(dimensionStr);
      dim >> xWidth >> yHeight;
      std::stringstream max(maxValStr);
      max >> maxValue;

      int **image = (int **)malloc(yHeight * sizeof(int*));
      int **energy = (int **)malloc(xWidth * sizeof(int*));
      int **cumulativeHorizontal = (int **)malloc(yHeight * sizeof(int*));
      int **cumulativeVertical = (int **)malloc(yHeight * sizeof(int));

      for (int i = 0; i < yHeight; i++)
      {
      	image[i] = (int*)malloc(xWidth * sizeof(int));
      	energy[i] = (int*)malloc(xWidth * sizeof(int));
      	cumulativeHorizontal[i] = (int*)malloc(xWidth * sizeof(int));
      	cumulativeVertical[i] = (int*)malloc(xWidth * sizeof(int));
      }
      std::cout << "hello";
      for (int x = 0; x < yHeight; ++x)
      {
      	  for (int y = 0; y < xWidth; ++y)
      	  {
      	  	  imageFile >> image[x][y];

      	  }

      }
	  for(int i = 0; i < vertSeamsInt; ++i)
	  {
	  	  for(int x = 0; x < yHeight; ++x)
	  	  {
	  	  	  for(int y = 0; y < xWidth; ++y)
	  	  	  {
	  	  	  	  if (x == 0)
	  	  	  	  {
	  	  	  	  	  if(y == 0)
	  	  	  	  	  {
	  	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x+1][y]) + abs(image[x][y]-image[x][y+1]);
	  	  	  	  	  }
	  	  	  	  	  else if (y == xWidth - 1)
	  	  	  	  	  {
	  	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x+1][y]) + abs(image[x][y]-image[x][y-1]);
	  	  	  	  	  }
	  	  	  	  	  else 
	  	  	  	  	  {
	  	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x+1][y]) + abs(image[x][y]-image[x][y-1] + abs(image[x][y]-image[x][y+1]));
	  	  	  	  	  	  
	  	  	  	  	  }
	  	  	  	  	  
	  	  	  	  }
	  	  	  	  else if(x == yHeight - 1)
	  	  	  	  {
	  	  	  	  
	  	  	  	  	if(y == 0)
	  	  	  	  	{
	  	  	  	  		energy[x][y] = abs(image[x][y] - image[x-1][y]) + abs(image[x][y] - image[x][y+1]);
	  	  	  	  	}
	  	  	  	  	else if(y == xWidth - 1)
	  	  	  	  	{
	  	  	  	  		energy[x][y] = abs(image[x][y] - image[x-1][y]) + abs(image[x][y] - image[x][y-1]);
	  	  	  	  	}
	  	  	  	  	else 
	  	  	  	  	{
	  	  	  	  		energy[x][y] = abs(image[x][y] - image[x-1][y]) + abs(image[x][y] - image[x][y-1]) + abs(image[x][y] - image[x][y+1]);
	  	  	  	  	}
	  	  	  	  }
	  	  	  	  else if(y == 0)
	  	  	  	  {
	  	  	  	  
	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x][y+1]) + abs(image[x][y] - image[x+1][y]) + abs(image[x][y] - image[x-1][y]);

	  	  	  	  }
	  	  	  	  else if (y == xWidth-1)
	  	  	  	  {
	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x][y-1]) + abs(image[x][y] - image[x+1][y]) + abs(image[x][y] - image[x-1][y]);
	  	  	  	  }
	  	  	  	   else
	  	  	      {
	  	  	  	   	  energy[x][y] = abs(image[x][y] - image[x][y+1]) + abs(image[x][y] - image[x][y-1]) + abs(image[x][y] - image[x+1][y]) + abs(image[x][y] - image[x-1][y]);
	  	  	 	  
	  	  	 	  }
	  	  	 	 
	  	  	  }
	  	  std::cout << "out again";	  
	  	  }
	  	  std::cout << "hello";
	  	  
	  	  for(int x = 0; x < xWidth; x++)
	  	  {
	  	  	  cumulativeVertical[0][x] = energy[0][x];
	  	  }
	  	  
	  	  for(int x = 1; x < yHeight; x++)
	  	  {
	  	  	  for(int y = 0; y < xWidth; ++y)
	  	  	  {
	  	  	      if(y == 0)
	  	  	      {
	  	  	      	  cumulativeVertical[x][y] = energy[x][y] + std::min({cumulativeVertical[x-1][y],cumulativeVertical[x-1][y+1]});
	  	  	      }
	  	  	      else if(y == xWidth - 1)
	  	  	      {
	  	  	      	 cumulativeVertical[x][y] = energy[x][y] + std::min({cumulativeVertical[x-1][y], cumulativeVertical[x-1][y=1]});
	  	  	      }
	  	  	      else
	  	  	      {
	  	  	      	  cumulativeVertical[x][y] = energy[x][y] + std::min({cumulativeVertical[x-1][y], cumulativeVertical[x-1][y+1],cumulativeVertical[x-1][y-1]});
	  	  	      }
	  	  	  }
	  	  }

	  	  int previousVal = 0, minVal = cumulativeVertical[yHeight-1][0];
	  	  Point tmpPoint;
	  	  std::vector<Point> tmpVector;
	  	  tmpPoint.x = 0;
	  	  tmpPoint.y = yHeight-1;

	  	  for(int x = 0; x < xWidth; ++x)
	  	  {
	  	  	  if(cumulativeVertical[yHeight-1][x] < minVal)
	  	  	  {
	  	  	  	  tmpPoint.x = x;
	  	  	  	  minVal = cumulativeVertical[yHeight-1][x];
	  	  	  }
	  	  }
	  	  tmpVector.push_back(tmpPoint);

	  	  for (int x = yHeight - 2; x >= 0; x++)
	  	  {
	  	  	  minVal = cumulativeVertical[x][tmpVector[previousVal].x];
	  	  	  tmpPoint.x = tmpVector[previousVal].x;
	  	  	  tmpPoint.y = x;

	  	  	  if(tmpVector[previousVal].x != 0)
	  	  	  {
	  	  	  	  if(cumulativeVertical[x][tmpVector[previousVal].x-1] < minVal)
	  	  	  	  {
	  	  	  	  	  minVal = cumulativeVertical[x][tmpVector[previousVal].x-1];
	  	  	  	  	  tmpPoint.x = tmpVector[previousVal].x;
	  	  	  	  }
	  	  	  }
	  	  	  if(tmpVector[previousVal].x != xWidth-1)
	  	  	  {
	  	  	  	  if(cumulativeVertical[x][tmpVector[previousVal].x+1] < minVal)
	  	  	  	  {
	  	  	  	  	  tmpPoint.x = tmpVector[previousVal].x-1;
	  	  	  	  	  minVal = cumulativeVertical[x][tmpVector[previousVal].x+1];
	  	  	  	  }
	  	  	  }
	  	  	  previousVal++;
	  	  	  tmpVector.push_back(tmpPoint);
	  	  }
	  	  verticalSeam = tmpVector;

	  	  int **tmpVal = (int**)malloc(yHeight * sizeof(int *));

	  	  for(int x = 0; x < yHeight; x++)
	  	  {
	  	  	  tmpVal[x] = (int*)malloc((xWidth-1) * sizeof(int));
	  	  }
	  	  for(int x = 0; x < verticalSeam.size(); x++)
	  	  {
	  	  	  image[verticalSeam[x].y][verticalSeam[x].x] = -1;
	  	  }
	  	  for(int x = 0, i = 0; x < yHeight; x++, i++)
	  	  {
	  	  	  for(int y = 0, j = 0; y < xWidth; y++, j++)
	  	  	  {
	  	  	  	  if(image[x][y] != -1)
	  	  	  	  {
	  	  	  	  	  tmpVal[i][j] = image[x][y];
	  	  	  	  }
	  	  	  	  else if(y == xWidth-1)
	  	  	  	  {
	  	  	  	  	  break;
	  	  	  	  }
	  	  	  	  else
	  	  	  	  	 j--;

	  	  	  }
	  	  }
	  	  for (int x = 0; x < yHeight; ++x)
	  	  {
	  	  	  for(int y = 0; y < xWidth - 1; y++)
	  	  	  {
	  	  	  	  image[x][y] = tmpVal[x][y];
	  	  	  }
	  	  }
	  	  for(int x = 0; x < yHeight; x++)
	  	  	delete tmpVal[x];

	  	  delete tmpVal;

	  	  xWidth--;

	   } 
	   
//===========horizontal seam detection and deletion
	   for(int x = 0; x < horizSeamsInt; x++)
	   {
	   	  for(int x = 0; x < yHeight; ++x)
	  	  {
	  	  	  for(int y = 0; y < xWidth; ++y)
	  	  	  {
	  	  	  	  if (x != 1)
	  	  	  	  {
	  	  	  	  	  if(y == 0)
	  	  	  	  	  {
	  	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x+1][y]) + abs(image[x][y]-image[x][y+1]);
	  	  	  	  	  }
	  	  	  	  	  else if (y == xWidth - 1)
	  	  	  	  	  {
	  	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x+1][y]) + abs(image[x][y]-image[x][y-1]);
	  	  	  	  	  }
	  	  	  	  	  else 
	  	  	  	  	  {
	  	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x+1][y]) + abs(image[x][y]-image[x][y-1] + abs(image[x][y]-image[x][y+1]));

	  	  	  	  	  }
	  	  	  	  }
	  	  	  	  else if(x == yHeight - 1)
	  	  	  	  {
	  	  	  	  	if(y == 0)
	  	  	  	  	{
	  	  	  	  		energy[x][y] = abs(image[x][y] - image[x-1][y]) + abs(image[x][y] - image[x][y+1]);
	  	  	  	  	}
	  	  	  	  	else if(y == xWidth - 1)
	  	  	  	  	{
	  	  	  	  		energy[x][y] = abs(image[x][y] - image[x-1][y]) + abs(image[x][y] - image[x][y-1]);
	  	  	  	  	}
	  	  	  	  	else 
	  	  	  	  	{
	  	  	  	  		energy[x][y] = abs(image[x][y] - image[x-1][y]) + abs(image[x][y] - image[x][y-1]) + abs(image[x][y] - image[x][y+1]);
	  	  	  	  	}
	  	  	  	  }
	  	  	  	  else if(y == 0)
	  	  	  	  {
	  	  	  	  	  energy[x][y] = abs(image[x][y] - image[x][y+1]) + abs(image[x][y] - image[x+1][y]) + abs(image[x][y] - image[x][y+1]);

	  	  	  	  }
	  	  	  	   else if (y == xWidth-1)
	  	  	  	   {
	  	  	  	   	  energy[x][y] = abs(image[x][y] - image[x][y-1]) + abs(image[x][y] - image[x+1][y]) + abs(image[x][y] - image[x-1][y]);
	  	  	  	   }
	  	  	  	   else
	  	  	  	   {
	  	  	  	   	  energy[x][y] = abs(image[x][y] - image[x][y+1]) + abs(image[x][y] - image[x][y-1]) + abs(image[x][y] - image[x+1][y]) + abs(image[x][y] - image[x-1][y]);
	  	  	  	   }
	  	  	  }
	  	  }
	  	  for(int x = 0; x < yHeight; x++)
	  	  {
	  	  	  cumulativeHorizontal[x][0] = energy[x][0];
	  	  }
	  	  for (int x = 0; x < xWidth; ++x)
	  	  {
	  	  	  for(int y = 0; y < yHeight; y++)
	  	  	  {
	  	  	  	   if(y == 0)
	  	  	  	   {
	  	  	  	   	  cumulativeHorizontal[y][x] = energy[y][x] + std::min({cumulativeHorizontal[y][x-1], cumulativeHorizontal[y+1][x-1]});
	  	  	  	   }
	  	  	  	   else if(y == yHeight - 1)
	  	  	  	   {
	  	  	  	   	  cumulativeHorizontal[y][x] = energy[y][x] + std::min({cumulativeHorizontal[y][x-1], cumulativeHorizontal[y-1][x-1]});

	  	  	  	   }
	  	  	  	   else
	  	  	  	   {
	  	  	  	   	  cumulativeHorizontal[y][x] = energy[y][x] + std::min({std::min(cumulativeHorizontal[y-1][x-1], cumulativeHorizontal[y+1][x-1]), cumulativeHorizontal[y][x-1]});

	  	  	  	   }
	  	  	  }
	  	  }

	   
	   	  int previousVal = 0, minVal = cumulativeVertical[0][xWidth-1];
	  	  Point tmpPoint;
	  	  std::vector<Point> tmpVector;
	  	  tmpPoint.y = 0;
	  	  tmpPoint.x = xWidth-1;

	  	  for(int x = 0; x < yHeight; ++x)
	  	  {
	  	  	  if(cumulativeVertical[x][xWidth-1] < minVal)
	  	  	  {
	  	  	  	  tmpPoint.y = x;
	  	  	  	  minVal = cumulativeVertical[x][yHeight-1];
	  	  	  }
	  	  }
	  	  tmpVector.push_back(tmpPoint);

	  	  for (int x = xWidth - 2; x >= 0; x--)
	  	  {
	  	  	  minVal = cumulativeVertical[tmpVector[previousVal].y][x];
	  	  	  tmpPoint.y = tmpVector[previousVal].y;
	  	  	  tmpPoint.x = x;

	  	  	  if(tmpVector[previousVal].y != 0)
	  	  	  {
	  	  	  	  if(cumulativeVertical[tmpVector[previousVal].y-1][x] < minVal)
	  	  	  	  {
	  	  	  	  	  minVal = cumulativeVertical[tmpVector[previousVal].y-1][x];
	  	  	  	  	  tmpPoint.y = tmpVector[previousVal].y-1;
	  	  	  	  }
	  	  	  }
	  	  	  if(tmpVector[previousVal].y != yHeight-1)
	  	  	  {
	  	  	  	  if(cumulativeVertical[tmpVector[previousVal].y+1][x] < minVal)
	  	  	  	  {
	  	  	  	  	  tmpPoint.y = tmpVector[previousVal].y+1;
	  	  	  	  	  minVal = cumulativeVertical[tmpVector[previousVal].y+1][x];
	  	  	  	  }
	  	  	  }
	  	  	  previousVal++;
	  	  	  tmpVector.push_back(tmpPoint);
	  	  }
	  	  horizontalSeam = tmpVector;

	  	  int **tmp2 = (int**)malloc((yHeight-1) * sizeof(int *));

	  	  for (int x = 0; x < yHeight-1; x++)
	  	  {
	  	  	  tmp2[x] = (int*)malloc(xWidth * sizeof(int));
	  	  }
	  	  for (int x = 0; x < horizontalSeam.size(); x++)
	  	  {
	  	  	  image[horizontalSeam[x].y][horizontalSeam[x].x] = -1;
	  	  }
	  	  for(int x = 0, i = 0; x < xWidth; x++, i++)
	  	  {
	  	  	  for(int y = 0, j = 0; y < yHeight; y++, j++)
	  	  	  {
	  	  	  	  if(image[y][x] != -1)
	  	  	  	  {
	  	  	  	  	 tmp2[j][i] = image[y][x];
	  	  	  	  }
	  	  	  	  else if(y == yHeight - 1)
	  	  	  	  	break;
	  	  	  	  else
	  	  	  	  {
	  	  	  	  	  j--;
	  	  	  	  }
	  	  	  }
	  	  }
	  	  for(int x = 0; x < yHeight - 1; x++)
	  	  {
	  	  	  for(int y = 0; y < xWidth; y++)
	  	  	  {
	  	  		  image[x][y] = tmp2[x][y];
	  	  	  }
	  	  }
	  	  for(int x = 0; x < yHeight-1; x++)
	  	  {
	  	  	delete tmp2[x];
	  	  }
	  	  delete tmp2;

	  	  yHeight--;
		}	

	  size_t filename_ = imageFileName.find_last_of(".");
      std::string rawFilename_ = imageFileName.substr(0, filename_);
	  std::ofstream finalFile;
      finalFile.open(rawFilename_ + "_processed.pgm");

      finalFile << "P2\n"
                << "# Seam carved version - Nathan Wemmer\n"
                << xWidth << " "
                << yHeight << "\n"
                << maxValue << "\n";
      for (int i = 0; i < yHeight; ++i)
      {
          for (int h = 0; h < xWidth; ++h)
          {
              finalFile << image[i][h] << " ";
          }
          if (i != xWidth - 1)
          {
              finalFile << std::endl;
          }
      }


	}
}