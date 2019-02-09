#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define filename "iris.data.txt"

/*
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
*/
typedef struct Data Data;
struct Data
{
  double sepal[2];
  double petal[2];
  double norm;
  char label[20]; 

  Data *suivant; 
};

void initializeData(Data* flower)
{
  flower-> sepal[0] = 0;
  flower-> sepal[1] = 0;
  flower-> petal[0] = 0;
  flower-> petal[1] = 0;
  flower-> norm = 0;
  strcpy(flower-> label, "");
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
    strcpy(nouveau->label,nvNombre.label);

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

Liste defineData(Liste *maListe)
{
  FILE* file = NULL;
  char line[100] = ""; 
  char* string = "";

  maListe = initialisation();
  Data flower;
  initializeData(&flower);

  file = fopen(filename, "r");
  while((fgets(line,100,file)) != NULL)
	{
	  flower.sepal[0] = strtod(strtok(line,","), &string);
	  flower.sepal[1] = strtod(strtok(NULL,","), &string);
	  flower.petal[0] = strtod(strtok(NULL,","), &string);
	  flower.petal[1] = strtod(strtok(NULL,","), &string);
	  flower.norm = sqrt(flower.sepal[0]) + sqrt(flower.sepal[1]) + sqrt(flower.petal[0]) + sqrt(flower.petal[1]);
    strcpy(flower.label,strtok(NULL,","));
	  insertion(maListe, flower);
	}
  fclose(file);
  return *maListe;
}

typedef struct VectorDonnee VectorDonnee;
struct VectorDonnee
{
   Data flower[150];
};

void copyToVector(Liste* liste, VectorDonnee* vectorDonnee)
{
	Data* tmp = liste->premier;
	int count = 0;

    do
    {
    	vectorDonnee->flower[count].sepal[0] = tmp->sepal[0];
    	vectorDonnee->flower[count].sepal[1] = tmp->sepal[1];
    	vectorDonnee->flower[count].petal[0] = tmp->petal[0];
    	vectorDonnee->flower[count].petal[1] = tmp->petal[1];
    	vectorDonnee->flower[count].norm = tmp->norm;
        strcpy(vectorDonnee->flower[count].label,tmp->label);
    	tmp = tmp->suivant;
    	count++;
    }
    while (tmp != NULL); 
}

int nombreElements(Liste *liste)
{
    if(liste == NULL)
    {
      return 0;
    }
    else
    {
      Data *actuel = liste->premier;
      int count = 0;
      while (actuel != NULL)
        {
        count++;
        actuel = actuel->suivant;
        }
      return count;
    }
}

Liste* supprimerElementEnFin(Liste* liste)
{
    /* Si la liste est vide, on retourne NULL */
    if(liste == NULL)
        return NULL;
 
    /* Si la liste contient un seul élément */
    Data *actuel = liste->premier;
    if(actuel == NULL)
    {
        /* On le libère et on retourne NULL (la liste est maintenant vide) */
        free(liste);
        return NULL;
    }
 
    /* Si la liste contient au moins deux éléments */
    Data* tmp = liste->premier;
    Data* ptmp = tmp->suivant;
    /* Tant qu'on n'est pas au dernier élément */
    while(tmp->suivant != NULL)
    {
        /* ptmp stock l'adresse de tmp */
        ptmp = tmp;
        /* On déplace tmp (mais ptmp garde l'ancienne valeur de tmp */
        tmp = tmp->suivant;
    }
    /* A la sortie de la boucle, tmp pointe sur le dernier élément, et ptmp sur
    l'avant-dernier. On indique que l'avant-dernier devient la fin de la liste
    et on supprime le dernier élément */
    ptmp->suivant = NULL;
    free(tmp);
    return liste;
}

void normalize(Liste* liste){

	Data* tmp = liste->premier;
    double sepalLenghtMax = tmp->sepal[0];
    double sepalWidthMax = tmp->sepal[1];
    double petalLenghtMax = tmp->petal[0];
    double petalWidthMax = tmp->petal[1];
    double normMax = tmp->norm;

    while (tmp->suivant != NULL)
    {
    	if (tmp->suivant->sepal[0]> sepalLenghtMax)
    	{
    		sepalLenghtMax = tmp->suivant->sepal[0];
    	}

    	if (tmp->suivant->sepal[1]> sepalWidthMax)
    	{
    		sepalWidthMax = tmp->suivant->sepal[1];
    	}

    	if (tmp->suivant->petal[0]> petalLenghtMax)
    	{
    		petalLenghtMax = tmp->suivant->petal[0];
    	}

    	if (tmp->suivant->petal[1]> petalWidthMax)
    	{
    		petalWidthMax = tmp->suivant->petal[1];
    	}

    	if (tmp->suivant->norm> normMax)
    	{
    		normMax = tmp->suivant->norm;
    	}

    	tmp = tmp->suivant;
    }

    tmp = liste->premier;
    do
    {
      tmp->sepal[0] = tmp->sepal[0]/ sepalLenghtMax;
      tmp->sepal[1] = tmp->sepal[1] / sepalWidthMax;
      tmp->petal[0] = tmp->petal[0] / petalLenghtMax;
      tmp->petal[1] = tmp->petal[1] / petalWidthMax;
      tmp->norm = tmp->norm / normMax;

      tmp = tmp->suivant;
    }
    while (tmp != NULL);  
}

Data moyenne(Liste* liste)
{
	Data* tmp = liste->premier;
    Data average;
    initializeData(&average);

    double sepalLenghtMoy = tmp->sepal[0];
    double sepalWidthMoy = tmp->sepal[1];
    double petalLenghtMoy = tmp->petal[0];
    double petalWidthMoy = tmp->petal[1];
    double normMoy = tmp->norm;

    while (tmp->suivant != NULL)
    {
      sepalLenghtMoy += tmp->suivant->sepal[0];
      sepalWidthMoy += tmp->suivant->sepal[1];
      petalLenghtMoy += tmp->suivant->petal[0];
      petalWidthMoy += tmp->suivant->petal[1];
      normMoy += tmp->suivant->norm;

      tmp = tmp->suivant;
    }

    average.sepal[0] = sepalLenghtMoy /nombreElements(liste);
    average.sepal[1] = sepalWidthMoy /nombreElements(liste);
    average.petal[0] = petalLenghtMoy /nombreElements(liste);
    average.petal[1] = petalWidthMoy /nombreElements(liste);
    average.norm = normMoy /nombreElements(liste);

    return average;
}

typedef struct Array Array;
struct Array {
  int caseNumber[150];
};

void initializeArray(Array* array, int sizeOfArray)
{
  int count = 0;
  for (count = 0; count < sizeOfArray; count++)
  {
    array->caseNumber[count] = count;
  }
}

void swapDataEntry(Array* array, int sizeOfArray)
{
  int count = 0;
  int temporaryValueOfCell = 0;
  int r = 0;
  for (count = 0; count < sizeOfArray; count++)
  {
    r = rand()%(sizeOfArray);
    temporaryValueOfCell = array->caseNumber[count];
    array->caseNumber[count] = array->caseNumber[r];
    array->caseNumber[r] = temporaryValueOfCell;
  }
}

struct Bmu
{
   int l;
   int c;
   double activation;
};

struct List_header
{
   int nb;
   struct bmu *bmu_list;
   struct bmu *last;
};

int main()
{
  Liste dataEntry;
  dataEntry = defineData(&dataEntry);
  supprimerElementEnFin(&dataEntry);

  VectorDonnee VectorDataEntry;
  copyToVector(&dataEntry, &VectorDataEntry);

  normalize(&dataEntry);
  //afficherListe(&dataEntry);
  moyenne(&dataEntry);

  srand(time(NULL));
  Array array = {0};
  initializeArray(&array, sizeof(array)/sizeof(int));
  swapDataEntry(&array,sizeof(array)/sizeof(int));
/*
  printf("\n%f",VectorDataEntry.flower[array.caseNumber[0]].sepal[0]);
  printf("\n%f",VectorDataEntry.flower[array.caseNumber[0]].sepal[1]);
  printf("\n%f",VectorDataEntry.flower[array.caseNumber[0]].petal[0]);
  printf("\n%f",VectorDataEntry.flower[array.caseNumber[0]].petal[1]);
  printf("\n%f",VectorDataEntry.flower[array.caseNumber[0]].norm);
*/

/*
  int count = 0;
  int count2 = 0;
  for (count = 0; count <= sizeof(array)/sizeof(int); count++)
  {
    for (count2 = 0; count2 <= sizeof(array)/sizeof(int); count2++)
    {
      if (array.caseNumber[count2] == count)
      {
        printf("\n%d",array.caseNumber[count2]);
      }
    }
   }
*/
  return 0;
}