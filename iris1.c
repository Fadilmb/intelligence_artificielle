#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define filename "iris.data.txt"

typedef struct Data Data;
struct Data
{
  double sepal_length;
  double sepal_width;
  double petal_length;
  double petal_width;
  char label[20]; 
};

typedef struct Node Node;
struct Node
{
  double sepal_length;
  double sepal_width;
  double petal_length;
  double petal_width;
  double distance_eucledienne
  char label[20]; 
};

int fileDimension()
{
  FILE* file = NULL;
  int count= 0;
  char c;

  file = fopen(filename, "r");
  if (file != NULL)
  {
    while((c = getc(file)) != EOF)
    { 
      if (c == '\n')
      { 
        count ++;
      }
    }
    fclose(file);
    return count +1;
  }
  else
  {
    printf("Impossible to open the file");
    return count = -1 ;
  }
}

Data* fill_the_dataSet(Data* dataSet)
{
  FILE* file = NULL;
  char line[100] = ""; 
  char* string = "";
  int count = 0;

  file = fopen(filename, "r");
  while((fgets(line,100,file)) != NULL)
	{
	  dataSet[count].sepal_length = strtod(strtok(line,","), &string);
	  dataSet[count].sepal_width = strtod(strtok(NULL,","), &string);
	  dataSet[count].petal_length = strtod(strtok(NULL,","), &string);
	  dataSet[count].petal_width = strtod(strtok(NULL,","), &string);
    strcpy(dataSet[count].label,strtok(NULL,","));
    count++;
	}

  fclose(file);
  return dataSet;
}

Data* normalization(Data* dataSet, int sizeOfDataSet)
{
  int count;
  double norm;

  for (count = 0; count < sizeOfDataSet; count++)
  {
    norm = sqrt(pow(dataSet[count].sepal_length,2)+pow(dataSet[count].sepal_width,2)+pow(dataSet[count].petal_length,2)+pow(dataSet[count].petal_width,2));
    dataSet[count].sepal_length /= norm;
    dataSet[count].sepal_width /= norm;
    dataSet[count].petal_length /= norm;
    dataSet[count].petal_width /= norm;
  }
  return dataSet;
}

Data averaging(Data* dataSet, int sizeOfDataSet)
{
  int count;
  Data average;

  for (count = 0; count < sizeOfDataSet; count++)
  {
    average.sepal_length += dataSet[count].sepal_length;
    average.sepal_width += dataSet[count].sepal_width;
    average.petal_length += dataSet[count].petal_length;
    average.petal_width += dataSet[count].petal_width;
  }
  average.sepal_length /= count;
  average.sepal_width /= count;
  average.petal_length /= count;
  average.petal_width /= count;

  return average;
}

Data* initialization_of_the_map(int numberOfNodes, Data average)
{
  int columns = ceil(sqrt(numberOfNodes));
  int lines = ceil(numberOfNodes / columns);
  printf("\n%d" "\n%d", columns, lines);

  return &average;
}

int main()
{
  int numberOfLines = fileDimension();
	Data *dataSet = calloc(numberOfLines, sizeof(Data));

  dataSet = fill_the_dataSet(dataSet);
  dataSet = normalization(dataSet, numberOfLines);

  int numberOfNodes = 5*sqrt(numberOfLines);

  Data average;
  //average = averaging(dataSet, numberOfLines);

	//printf("\n%f" "\n%f" "\n%f" "\n%f", average.sepal_length, average.sepal_width, average.petal_length, average.petal_width );
  initialization_of_the_map(numberOfNodes, average);
	return 0;
}