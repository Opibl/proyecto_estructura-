#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "list.h"
#include <ctype.h>
#include <string.h>

typedef struct
{
    char *pregunta;

}preguntita;

typedef struct
{
    char pregun[1000];
    list *Alternativas;
    char area[1000];

}preguntit;

typedef struct
{
    char *texto;
    char *puntaje;

}alternativa;

/*typedef struct
{
    char *descripcion;
    list *preguntas;
    Map *resultados;

}test;
*/

char *get_csv_field (char * tmp, int i)
{
    char * line = _strdup (tmp);
    char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

char * _strdup (const char *s) {
    size_t len = strlen (s) + 1;
    void *new = malloc (len);

    if (new == NULL)
    	return NULL;

    return (char *) memcpy (new, s, len);
}


long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

preguntita *crear_pregunta(char *linea)
{
    preguntita *nueva_pregunta = malloc(sizeof(preguntita));
    strcpy(nueva_pregunta->pregunta,linea);
    return nueva_pregunta;

}

void test_depresion(list *preguntas)
{
    FILE *entrada_preguntas = fopen("preguntas_depresion.csv","r");

    char *linea;
    char respuestita[1000];

    if (entrada_preguntas == NULL)
    {
        printf("Archivo no se pudo abrir :(");
        exit(0);
    }
    linea = (char*) malloc(sizeof(char)*1024);
     while(fgets(linea,1024,entrada_preguntas) != NULL)
     {
        preguntita *m = crear_pregunta(linea);
        list_push_back(preguntas,m);
        linea = (char*) malloc(sizeof(char)*1024);

     }

   preguntita *dato;
    dato = list_first (preguntas);
    //int puntaje = 0;
    while(dato != NULL)
    {
        printf("%s\n",dato->pregunta);
        scanf("%s",respuestita);
        /*if((strcmp("si",respuestita)==0))
        {
            puntaje = puntaje++;
        }
        dato = list_next(preguntas);
        */
    }

}

int main()
{
    int op;
    list *preguntas = list_create_empty();
    //Map *resultado = createMap(stringHash,stringEqual);

    do
    {
        printf("ingrese el numero de test que desea contestar (si no desea contestar ninguno aprete 0)\n");
        printf("1.para iniciar el test vocacional\n");
        printf("2.para iniciar el test de salud mental\n");
        printf("3.para iniciar el test de depresion\n");
        printf("4.para iniciar el test de inteligencia emocional\n");
        scanf("%d",&op);

        if (op == 1)
        {

        }

        if (op == 2)
        {

        }

        if(op == 3)
        {
            test_depresion(preguntas);
        }

        if(op == 4)
        {


        }

    }while(op != 0);

    return 0;
}
