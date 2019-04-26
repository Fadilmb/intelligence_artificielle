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
  double distance_eucledienne;
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

void fill_the_dataSet(Data* dataSet)
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
}

void normalization(Data* dataSet, int sizeOfDataSet)
{
  double norm;

  for (int count = 0; count < sizeOfDataSet; count++)
  {
    norm = sqrt(pow(dataSet[count].sepal_length,2)+pow(dataSet[count].sepal_width,2)+pow(dataSet[count].petal_length,2)+pow(dataSet[count].petal_width,2));
    dataSet[count].sepal_length /= norm;
    dataSet[count].sepal_width /= norm;
    dataSet[count].petal_length /= norm;
    dataSet[count].petal_width /= norm;
  }
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

double doubleRand(double min, double max)
{
  double scale = ((double)rand() / RAND_MAX);
  return min + scale * (max - min);
}

void initialization_of_the_map(size_t rows, size_t columns, Node **net, Data average)
{
  double sepal_length_average_maxValue = average.sepal_length + 0.005;
  double sepal_length_average_minValue = average.sepal_length - 0.002;
  double sepal_width_average_maxValue = average.sepal_width + 0.005;
  double sepal_width_average_minValue = average.sepal_width - 0.002;
  double petal_length_average_maxValue = average.petal_length + 0.005;
  double petal_length_average_minValue = average.petal_length - 0.002;
  double petal_width_average_maxValue = average.petal_width + 0.005;
  double petal_width_average_minValue = average.petal_width - 0.002;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      net[i][j].sepal_length = doubleRand(sepal_length_average_minValue, sepal_length_average_maxValue);
      net[i][j].sepal_width = doubleRand(sepal_width_average_minValue, sepal_width_average_maxValue);
      net[i][j].petal_length = doubleRand(petal_length_average_minValue, petal_length_average_maxValue);
      net[i][j].petal_width = doubleRand(petal_width_average_minValue, petal_width_average_maxValue);
    }
  }
}

void initialize_shuffle_array(int* array, size_t sizeOfTheArray)
{
  for (int count = 0; count < sizeOfTheArray; count++)
  {
    array[count] = count;
  }
}

void shuffle_the_array(int* array, int sizeOfArray)
{
  int temporaryValueOfCell, randNumber;
  for (int count = 0; count < sizeOfArray; count++)
  {
    randNumber = rand()%(sizeOfArray);
    temporaryValueOfCell = array[count];
    array[count] = array[randNumber];
    array[randNumber] = temporaryValueOfCell;
  }
}

int main()
{
  srand(time(NULL));

  int numberOfLines = fileDimension();
  Data dataSet[numberOfLines];
  fill_the_dataSet(dataSet);
  normalization(dataSet, sizeof(dataSet)/sizeof(Data));

  Data average = averaging(dataSet, sizeof(dataSet)/sizeof(Data));
  
  int numberOfNodes = 5*sqrt(numberOfLines);
  size_t rows = ceil(sqrt(numberOfNodes));
  size_t columns = ceil(numberOfNodes / rows);
  Node **net = calloc(rows, sizeof(Node *));
  for(int i = 0; i < rows; i++)
  {
    net[i] = calloc(columns, sizeof(Node));
  }

  initialization_of_the_map(rows, columns, net, average);

  int array[numberOfLines];
  initialize_shuffle_array(array, sizeof(array)/sizeof(int));
  shuffle_the_array(array, sizeof(array)/sizeof(int));



  printf("\n%f" "\n%f", net[5][7].sepal_length, net[3][4].sepal_length);
	return 0;
}