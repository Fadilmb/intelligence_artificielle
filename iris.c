#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define filename "iris.data.txt"


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
    nouveau->sepal[1] = nvNombre.sepal[1];
    nouveau->petal[0] = nvNombre.petal[0];
    nouveau->petal[1] = nvNombre.petal[1];
    nouveau->norm = nvNombre.norm;
    nouveau->label = nvNombre.label;

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
        printf("%f\n", actuel->sepal[0]);
        printf("%f\n", actuel->sepal[1]);
        printf("%f\n", actuel->petal[0]);
        printf("%f\n", actuel->petal[1]);
        printf("%f\n", actuel->norm);
        printf("%s\n", actuel->label);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

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

Liste defineData(Liste *maListe)
{
  FILE* file = NULL;
  char line[100] = ""; 
  char* string = "";

  maListe = initialisation();
  struct Data flower;
  initializeData(&flower);

  file = fopen(filename, "r");
  while((fgets(line,100,file)) != NULL)
	{
	  flower.sepal[0] = strtod(strtok(line,","), &string);
	  flower.sepal[1] = strtod(strtok(NULL,","), &string);
	  flower.petal[0] = strtod(strtok(NULL,","), &string);
	  flower.petal[1] = strtod(strtok(NULL,","), &string);
	  flower.norm = sqrt(flower.sepal[0]) + sqrt(flower.sepal[1]) + sqrt(flower.petal[0]) + sqrt(flower.petal[1]);
	  flower.label = strtok(NULL,",");
	  insertion(maListe, flower);
	  afficherListe(maListe);
	}
  return *maListe;
}	

int main()
{
  Liste maListe2;
  maListe2 = defineData(&maListe2);
  afficherListe(&maListe2);
  return 0;
}