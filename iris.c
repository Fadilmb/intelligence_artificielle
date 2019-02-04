#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define filename "iris.data.txt"
#define DEFINE_NUMBER_OF_LINE() int numberOfLine = fileDimension() +1 


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
    return count;
  }
  else
  {
    printf("Impossible to open the file");
    return count = -1 ;
  }
}

typedef struct Data Data;
struct Data
{
  double sepal[2];
  double petal[2];
  double norm;
  char* label; 

  Data *suivant; 
};

void initializeData(Data* flower)
{
  flower-> sepal[0] = 0;
  flower-> sepal[1] = 0;
  flower-> petal[0] = 0;
  flower-> petal[1] = 0;
  flower-> norm = 0;
  flower-> label = "";
}

typedef struct Liste Liste;
struct Liste
{
   Data *premier;
};

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Data *data = malloc(sizeof(*data));

    if (liste == NULL || data == NULL)
    {
        exit(EXIT_FAILURE);
    }

    initializeData(data);
    data->suivant = NULL;
    liste->premier = data;

    return liste;
}

void insertion(Liste *liste, Data nvNombre)
{
    /* Création du nouvel élément */
    Data *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->sepal[0] = nvNombre.sepal[0];
    //printf("\n%f",nouveau -> sepal[0]);
    nouveau->sepal[1] = nvNombre.sepal[1];
    //printf("\n%f",nouveau -> sepal[1]);
    nouveau->petal[0] = nvNombre.petal[0];
    //printf("\n%f",nouveau -> petal[0]);
    nouveau->petal[1] = nvNombre.petal[1];
    //printf("\n%f",nouveau -> petal[1]);
    nouveau->norm = nvNombre.norm;
    //printf("\n%f",nouveau -> norm);
    nouveau->label = nvNombre.label;
    //printf("\n%s",nouveau -> label);


    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void suppression(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL)
    {
        Data *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Data *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%f -> ", actuel->sepal[0]);
        printf("%f -> ", actuel->sepal[1]);
        printf("%f -> ", actuel->petal[0]);
        printf("%f -> ", actuel->petal[1]);
        printf("%f -> ", actuel->norm);
        printf("%s -> ", actuel->label);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

struct DataEntry {
	Data arrayFlower[200];
};

struct Bmu {
   int l;
   int c;
   double activation;
};

struct List_header {
   int nb;
   struct bmu *bmu_list;
   struct bmu *last;
};

struct DataEntry defineData()
{
  DEFINE_NUMBER_OF_LINE();

  FILE* file = NULL;
  char line[100] = ""; 
  char* string = "";
  int i = 0;

  Liste *maListe = initialisation();

  struct Data flower[numberOfLine];
  struct DataEntry flowerArray;

  file = fopen(filename, "r");
  while((fgets(line,100,file)) != NULL)
	{
	  initializeData(&flower[i]);
	  flower[i].sepal[0] = strtod(strtok(line,","), &string);
	  flower[i].sepal[1] = strtod(strtok(NULL,","), &string);
	  flower[i].petal[0] = strtod(strtok(NULL,","), &string);
	  flower[i].petal[1] = strtod(strtok(NULL,","), &string);
	  flower[i].norm = sqrt(flower[i].sepal[0]) + sqrt(flower[i].sepal[1]) + sqrt(flower[i].petal[0]) + sqrt(flower[i].petal[1]);
	  flower[i].label = strtok(NULL,",");
	  flowerArray.arrayFlower[i] = flower[i];
	  insertion(maListe, flower[i]);
	  afficherListe(maListe);
	}
  afficherListe(maListe);
  return flowerArray;
}	

int main()
{
  defineData();
  return 0;
}