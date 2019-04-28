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
  double euclidean_distance;
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
    strcpy(dataSet[count].label , strtok(NULL,","));
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
  double maxBoundaryAveraging = 0.005;
  double minBoundrayAveraging = 0.002;
  double sepal_length_average_maxValue = average.sepal_length + maxBoundaryAveraging;
  double sepal_length_average_minValue = average.sepal_length - minBoundrayAveraging;
  double sepal_width_average_maxValue = average.sepal_width + maxBoundaryAveraging;
  double sepal_width_average_minValue = average.sepal_width - minBoundrayAveraging;
  double petal_length_average_maxValue = average.petal_length + maxBoundaryAveraging;
  double petal_length_average_minValue = average.petal_length - minBoundrayAveraging;
  double petal_width_average_maxValue = average.petal_width + maxBoundaryAveraging;
  double petal_width_average_minValue = average.petal_width - minBoundrayAveraging;

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

void calculate_euclidean_distance(size_t rows, size_t columns, Node **net, Data* data)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      net[i][j].euclidean_distance = sqrt(pow(net[i][j].sepal_length-data->sepal_length,2)+pow(net[i][j].sepal_width-data->sepal_width,2)+pow(net[i][j].petal_length-data->petal_length,2)+pow(net[i][j].petal_width-data->petal_width,2));
    }
  }
}

int* best_match_unit(int* bmuIndex, size_t rows, size_t columns, Node **net)
{
  double euclideanDistanceMin = net[0][0].euclidean_distance;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      if (net[i][j].euclidean_distance < euclideanDistanceMin)
      {
        euclideanDistanceMin = net[i][j].euclidean_distance;
        bmuIndex[0] = i;
        bmuIndex[1] = j;
      }
    }
  }
  return bmuIndex;
}

double alpha_function(double alpha_initial, int iteration, int iteration_max)
{
  return alpha_initial*(1-(iteration/iteration_max));
}

int neighborhood(int nhd_size, int* bmuIndex, int* nodeIndex)
{
  if (abs(bmuIndex[0]-nodeIndex[0]) < nhd_size && abs(bmuIndex[1]-nodeIndex[1]) < nhd_size)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void learning_rule(size_t rows, size_t columns, Node **net, int nhd_size, int* bmuIndex, double alpha, Data* data)
{
  int nodeIndex[2];
  int nhd;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      nodeIndex[0] = i;
      nodeIndex[1] = j; 
      nhd = neighborhood(nhd_size, bmuIndex, nodeIndex);
      net[i][j].sepal_length += alpha*nhd*(data->sepal_length-net[i][j].sepal_length);
      net[i][j].sepal_width += alpha*nhd*(data->sepal_width-net[i][j].sepal_width);
      net[i][j].petal_length += alpha*nhd*(data->petal_length-net[i][j].petal_length);
      net[i][j].petal_width += alpha*nhd*(data->petal_width-net[i][j].petal_width);
    }
  }
}

void labelization(size_t rows, size_t columns, Node **net, Data* dataSet, int sizeOfDataSet)
{
  int bmuIndex[2]= {0,0};
  for(int count = 0; count < sizeOfDataSet; count++)
  {
    calculate_euclidean_distance(rows, columns, net, &dataSet[count]);
    best_match_unit(bmuIndex, rows, columns, net);
    strcpy(net[bmuIndex[0]][bmuIndex[1]].label , dataSet[count].label);
  }
}

void display_the_map(size_t rows, size_t columns, Node **net, Data* dataSet, int sizeOfDataSet)
{
  char label1[20] = "", label2[20] = "", label3[20] = "";

  strcpy(label1 , dataSet[0].label);
  printf("\x1B[31m" "%s", label1);
  for(int count = 1; count < sizeOfDataSet; count++)
  {
    if ((strcmp(label1 , dataSet[count].label) != 0) && ((strcmp(label2 , "")) == 0))
    {
      strcpy(label2 , dataSet[count].label);
      printf("\x1B[32m" "\x1B[32m" "%s", label2);
    }
    else if ((strcmp(label1 , dataSet[count].label) != 0) && (strcmp(label2 , dataSet[count].label) != 0) && ((strcmp(label3 , "")) == 0))
    {
      strcpy(label3 , dataSet[count].label);
      printf("\x1B[34m" "%s", label3);
    }
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      if (strcmp(net[i][j].label , label1) == 0)
      {
        printf("%s#","\x1B[31m");
      }
      else if (strcmp(net[i][j].label , label2) == 0)
      {
        printf("%s#","\x1B[32m");
      }
      else if (strcmp(net[i][j].label , label3) == 0)
      {
        printf("%s#","\x1B[34m");
      }
      else
      {
        printf("%s"," ");
      }
    }
  printf("%s\n"," ");
  } 
}

void testing(size_t rows, size_t columns, Node **net, Data* dataSet, int sizeOfDataSet)
{
  float trueResult = 0;
  int bmuIndex[2]= {0,0};
  for(int count = 0; count< sizeOfDataSet; count++)
  {
    calculate_euclidean_distance(rows, columns, net, &dataSet[count]);
    best_match_unit(bmuIndex, rows, columns, net);
    if (strcmp(net[bmuIndex[0]][bmuIndex[1]].label , dataSet[count].label) == 0)
    {
      trueResult++;
    }
  }
  printf("\x1B[0m" "The test succeed at %0.2f%%\n", (trueResult/sizeOfDataSet)*100);  
}

int main()
{
  //initialization
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

  int shuffleArray[numberOfLines];
  initialize_shuffle_array(shuffleArray, sizeof(shuffleArray)/sizeof(int));

  
  //phase1
  int iteration_max = 300;
  double alpha_initial = 0.8;
  int nhd_size = 3;

  shuffle_the_array(shuffleArray, sizeof(shuffleArray)/sizeof(int));

  double alpha;
  int bmuIndex[2]= {0,0};
  int randVectorDataIndex;
  for(int iteration = 0; iteration < iteration_max; iteration++)
  {
    randVectorDataIndex = rand()%(sizeof(dataSet)/sizeof(Data));

    calculate_euclidean_distance(rows, columns, net, &dataSet[shuffleArray[randVectorDataIndex]]);

    best_match_unit(bmuIndex, rows, columns, net);

    alpha = alpha_function(alpha_initial, iteration, iteration_max);

    learning_rule(rows, columns, net, nhd_size, bmuIndex, alpha, &dataSet[shuffleArray[randVectorDataIndex]]);
  }


  //phase2
  iteration_max = 2000;
  alpha_initial = 0.08;

  shuffle_the_array(shuffleArray, sizeof(shuffleArray)/sizeof(int));

  for(int iteration = 0; iteration < iteration_max; iteration++)
  {
    randVectorDataIndex = rand()%(sizeof(dataSet)/sizeof(Data));

    calculate_euclidean_distance(rows, columns, net, &dataSet[shuffleArray[randVectorDataIndex]]);

    best_match_unit(bmuIndex, rows, columns, net);

    alpha = alpha_function(alpha_initial, iteration, iteration_max);
    learning_rule(rows, columns, net, nhd_size, bmuIndex, alpha, &dataSet[shuffleArray[randVectorDataIndex]]);
  }

  //labelization
  labelization(rows, columns, net, dataSet, sizeof(dataSet)/sizeof(Data));

  //affichage
  display_the_map(rows, columns, net, dataSet, sizeof(dataSet)/sizeof(Data));

  //test
  testing(rows, columns, net, dataSet, sizeof(dataSet)/sizeof(Data));

	return 0;
}