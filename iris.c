#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define filename "iris.data.txt"
#define DEFINE_LINE_AND_CHARACTERE() int charactere = fileDimension().number_of_character +1; \
									 int numberOfLine = fileDimension().number_of_line +1;

struct Size
{
   int number_of_line;
   int number_of_character;
};

struct Size fileDimension()
{
  FILE* file = NULL;
  int count=0;
  int i=0;
  int j=0;
  char c;

  struct Size size={-1,-1};

  file = fopen(filename, "r");
  if (file != NULL)
  {
    while((c = getc(file)) != EOF)
    { 
      if (c == '\n')
      { 
        count ++;
        if (i>j)
        {
          j = i;       	
        }
        i = 0;
      }
      else
      {
      	i = i +1;
      }
    }
    fclose(file);
    size.number_of_line = count;
    size.number_of_character= j;
    return size;
  }
  else
  {
    printf("Impossible to open the file");
    return size;
  }
}

struct Data
{
  double sepal[2];
  double petal[2];
  double norm;
  char* label;  
};

void initializeData(struct Data* flower)
{
  flower-> sepal[0] = 0;
  flower-> sepal[1] = 0;
  flower-> petal[0] = 0;
  flower-> petal[1] = 0;
  flower-> norm = 0;
  flower-> label = "";
}

struct DataEntry
  {   
	struct Data arrayFlower[200];
  };


struct DataEntry defineData()
{
  DEFINE_LINE_AND_CHARACTERE();

  FILE* file = NULL;
  char line[charactere]; 
  char* string = "";
  int i = 0;

  struct Data flower[numberOfLine];
  struct DataEntry flowerArray;

  file = fopen(filename, "r");
  if (file != NULL)
  {
  	while((fgets(line,charactere,file)) != NULL)
    {
      initializeData(&flower[i]);
      flower[i].sepal[0] = strtod(strtok(line,","), &string);
      printf("\n%f",flower[i].sepal[0]);
      flower[i].sepal[0] = strtod(strtok(NULL,","), &string);
      printf("\n%f",flower[i].sepal[0]);
      flower[i].petal[0] = strtod(strtok(NULL,","), &string);
      printf("\n%f",flower[i].petal[0]);
      flower[i].petal[1] = strtod(strtok(NULL,","), &string);
      printf("\n%f",flower[i].petal[1]);
      flower[i].norm = sqrt(flower[i].sepal[0]) + sqrt(flower[i].sepal[1]) + sqrt(flower[i].petal[0]) + sqrt(flower[i].petal[1]);
      printf("\n%f",flower[i].norm);
      flower[0].label = strtok(NULL,",");
      printf("\n%s",flower[i].label);
      flowerArray.arrayFlower[i] = flower[i];
    }
  	fclose(file);
  	return flowerArray;
  }
  else
  {
  	printf("Impossible to open the file");
  	return flowerArray;
  }
}

int main()
{
  defineData();
  return 0;
}

