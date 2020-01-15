#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "list.h"
#include <ctype.h>
#include <string.h>

typedef struct
{
    char *pregunta;
    char *respuesta;
    char *puntos;

}datos_test;

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

datos_test *crear_pregunta(char *preguntaR,char *respuestaR,char *punto)
{
    datos_test *nueva_pregunta = malloc(sizeof(datos_test));
    nueva_pregunta->pregunta=preguntaR;
    nueva_pregunta->respuesta=respuestaR;
    nueva_pregunta->puntos=punto;
    return nueva_pregunta;

}

void test_depresion(list *preguntas)
{
    FILE *entrada_preguntas = fopen("preguntas_depresion.csv","r");

    char *linea;
    char *preguntaR;
    char *respuestaR;
    char *punto;
    char respuesta_dada[1000];

    if (entrada_preguntas == NULL)
    {
        printf("Archivo no se pudo abrir :(");
        exit(0);
    }
    linea = (char*) malloc(sizeof(char)*1024);
     while(fgets(linea,1024,entrada_preguntas) != NULL)
     {
        preguntaR = get_csv_field(linea, 1);
        respuestaR = get_csv_field(linea, 2);
        punto = (get_csv_field(linea, 3));
        datos_test *m = crear_pregunta(preguntaR,respuestaR,punto);
        list_push_back(preguntas,m);
        linea = (char*) malloc(sizeof(char)*1024);

     }
    printf("Bienvenido al test de depresion (porfavor contestar si o no a cada pregunta)\n");
    datos_test *dato;
    dato = list_first (preguntas);
    int puntaje = 0;
    while(dato != NULL)
    {
        printf("%s\n",dato->pregunta);
        while(1)
        {
            scanf("%s",respuesta_dada);
            if((strcmp(respuesta_dada,"NO")==0)||(strcmp(respuesta_dada,"no")==0)||(strcmp(respuesta_dada,"No")==0)||(strcmp(respuesta_dada,"SI")==0)||(strcmp(respuesta_dada,"si")==0)||(strcmp(respuesta_dada,"Si")==0))
            {
                break;
            }
            printf("respuesta no valida por favor vuelva a contestar\n");
        }

        if((strcmp("si",respuesta_dada)==0)&&(strcmp("1",dato->puntos)==0))
        {
            puntaje++;
        }

        dato = list_next(preguntas);
    }
    printf("es puntaje final es %d\n",puntaje);
    if(puntaje >= 3)
    {
        printf("Tu test de depresion es negativo .... bla bla bla hay que inventar algo XD\n");
    }
    else
    {
        if (puntaje == 0)
        {
            printf("probablemente estes cursando una depresion y blalbla\n");
        }
        else
        {
            printf("bla bla (no esta cursando depresion) hay que inventar algo xD\n");
        }
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
            printf("\n");
        }

        if(op == 4)
        {


        }

    }while(op != 0);

    return 0;
}
