#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "list.h"
#include <ctype.h>
#include <string.h>

typedef struct
{
    char *pregunta;
    char *puntos;

}datos_test;

typedef struct
{
    char *pregunta_vocacional;
    char *area;

}datos_pregunta_vocacional;


typedef struct
{
    char *carrera;
    char *area_carrera;
    list *listVocacional;

}datos_vocacional;

/*typedef struct
{
    int min, int max //rango para determinar el resultado.
    char* descripción_resultado //mensaje final del test para complementar con el resultado

}DescripciónDeResultado;
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
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

datos_test *crear_pregunta(char *preguntaR,char *punto)
{
    datos_test *nueva_pregunta = malloc(sizeof(datos_test));
    nueva_pregunta->pregunta=preguntaR;
    nueva_pregunta->puntos=punto;
    return nueva_pregunta;

}

datos_pregunta_vocacional *crear_pregunta_vocacional(char *preguntaR,char *areaR)
{
    datos_pregunta_vocacional *nueva_pregunta = malloc(sizeof(datos_pregunta_vocacional));
    nueva_pregunta->pregunta_vocacional=preguntaR;
    nueva_pregunta->area=areaR;
    return nueva_pregunta;
}

datos_vocacional *crear_vocacional(char *carreraR,char *area_carreraR)
{
    datos_vocacional *nueva_pregunta = malloc(sizeof(datos_vocacional));
    nueva_pregunta->carrera=carreraR;
    nueva_pregunta->area_carrera=area_carreraR;
    return nueva_pregunta;
}

void test_vocacional(Map *mapVocacional,list *listVocacional)
{
    FILE *entrada_preguntas = fopen("preguntas_test_vocacional.csv","r");
    char *linea;
    char *preguntaR;
    char *carreraR;
    char *areaR;
    char *area_carreraR;

    list *lista_carreras = list_create_empty();

    if (entrada_preguntas == NULL)
    {
        printf("Archivo no se pudo abrir :(");
        exit(0);
    }
    linea = (char*) malloc(sizeof(char)*1024);
    while(fgets(linea,1024,entrada_preguntas) != NULL)
     {
        preguntaR = get_csv_field(linea, 1);
        areaR = get_csv_field(linea,2);
        datos_pregunta_vocacional *m = crear_pregunta_vocacional(preguntaR,areaR);
        list_push_back(listVocacional,m);
        linea = (char*) malloc(sizeof(char)*1024);
    }

    FILE *entrada_carreras = fopen("carreras.csv","r");
    if (entrada_carreras == NULL)
    {
        printf("Archivo no se pudo abrir :(");
        exit(0);
    }
    char *linea2;
    linea2 = (char*) malloc(sizeof(char)*1024);

    while(fgets(linea2,1024,entrada_carreras) != NULL)
     {
        carreraR = get_csv_field(linea2,1);
        area_carreraR = get_csv_field(linea2,2);
        datos_vocacional *t = crear_pregunta_vocacional(carreraR,area_carreraR);
        list_push_back(lista_carreras,t);
        insertMap(mapVocacional,t->area_carrera,lista_carreras);
        linea = (char*) malloc(sizeof(char)*1024);
    }

    printf("\n\n  ---------------------------------------TEST VOCACIONAL------------------------------------------ \n");
    printf(" |                                                                                                |\n");
    printf(" |  Sabemos lo importante que es decidir adecuadamente en esta materia. Una carrera no solo va    |\n");
    printf(" |  a ser una gran inversion de dinero, tiempo y energia. Tambien va a ser lo que probablemente   |\n");
    printf(" |  te vas a dedicar los proximos 50 años de tu vida. Esperamos poder ayudarte a que te sientas   |\n");
    printf(" |  mas claro y puedas decidir con criterios mas especificos un area de interes que te represente |\n");
    printf(" |  y te haga sentir satisfecho.                                                                  |\n");
    printf(" |                                                                                                |\n");
    printf("  ------------------------------------------------------------------------------------------------ ");
    printf("\n\n Presione cualquier tecla para comenzar el test");
    getch();
    system("cls");

    char respuesta_dada[100];

    int puntaje_ingenieria = 0;
    int puntaje_salud = 0;
    int puntaje_artes = 0;
    int puntaje_cs = 0;

    datos_pregunta_vocacional *datoR;
    datoR =  list_first(listVocacional);
    while(datoR != NULL)
    {
        printf("\nContestar con 'si' o 'no', por favor\n");
        printf("--------------------------------------\n\n");
        printf("%s\n",datoR->pregunta_vocacional);

        while(1)
        {
            printf("\n");
            getchar();
            scanf("%[^\n]s",respuesta_dada);
            if((strcmp(respuesta_dada,"NO")==0)||(strcmp(respuesta_dada,"no")==0)||(strcmp(respuesta_dada,"No")==0)||(strcmp(respuesta_dada,"SI")==0)||(strcmp(respuesta_dada,"si")==0)||(strcmp(respuesta_dada,"Si")==0))
            {
                break;
            }
            printf("\nRespuesta no valida, por favor vuelva a contestar\n");
        }
        system("cls");


        if((strcmp("si",respuesta_dada)==0)&&(strcmp("ingenieria",datoR->area)==0)){
            puntaje_ingenieria++;
        }

        if((strcmp("si",respuesta_dada)==0)&&(strcmp("salud",datoR->area)==0)){
            puntaje_salud++;
        }

        if((strcmp("si",respuesta_dada)==0)&&(strcmp("artes",datoR->area)==0)){
            puntaje_artes++;
        }

        if((strcmp("si",respuesta_dada)==0)&&(strcmp("cienciaSociales",datoR->area)==0)){
            puntaje_cs++;
        }

        datoR = list_next(listVocacional);
    }
    printf("%d ",puntaje_artes);
    printf("%d ",puntaje_ingenieria);
    printf("%d ",puntaje_salud);
    printf("%d \n",puntaje_cs);



    if((puntaje_ingenieria>=puntaje_salud)&&(puntaje_ingenieria>=puntaje_artes)&&(puntaje_ingenieria>=puntaje_cs)&&(puntaje_ingenieria!=0))
    {
        char *clave;
        clave = (char*) malloc(sizeof(char)*1024);
        strcpy(clave,"ingenieria");
        list *j = searchMap(mapVocacional,clave);
        datos_vocacional *puntero = list_first(j);
        while(puntero != NULL)
        {
            if(strcmp(clave,puntero->area_carrera)==0)
            {
                printf(" -%s\n",puntero->carrera);
            }
            puntero = list_next(j);

        }
    }

    if((puntaje_salud>=puntaje_ingenieria)&&(puntaje_salud>=puntaje_artes)&&(puntaje_salud>=puntaje_cs)&&(puntaje_salud!=0))
    {
        char *clave;
        clave = (char*) malloc(sizeof(char)*1024);
        strcpy(clave,"salud");
        list *j = searchMap(mapVocacional,clave);
        datos_vocacional *puntero = list_first(j);
        while(puntero != NULL)
        {
            if(strcmp(clave,puntero->area_carrera)==0)
            {
                printf("%s\n",puntero->carrera);
            }
            puntero = list_next(j);
        }
    }

    if((puntaje_artes>=puntaje_ingenieria)&&(puntaje_artes>=puntaje_salud)&&(puntaje_artes>=puntaje_cs)&&(puntaje_artes!=0))
    {
        char *clave;
        clave = (char*) malloc(sizeof(char)*1024);
        strcpy(clave,"artes");
        list *j = searchMap(mapVocacional,clave);
        datos_vocacional *puntero = list_first(j);
        while(puntero != NULL)
        {
            if(strcmp(clave,puntero->area_carrera)==0)
            {
                printf("%s\n",puntero->carrera);
            }
            puntero = list_next(j);

        }
    }

    if((puntaje_cs>=puntaje_ingenieria)&&(puntaje_cs>=puntaje_salud)&&(puntaje_cs>=puntaje_artes)&&(puntaje_cs!=0))
    {
        char *clave;
        clave = (char*) malloc(sizeof(char)*1024);
        strcpy(clave,"cienciaSociales");
        list *j = searchMap(mapVocacional,clave);
        datos_vocacional *puntero = list_first(j);
        while(puntero != NULL)
        {
            if(strcmp(clave,puntero->area_carrera)==0)
            {
                printf("%s\n",puntero->carrera);
            }
            puntero = list_next(j);

        }
    }
    if((puntaje_ingenieria == 0)&&(puntaje_artes == 0)&&(puntaje_cs == 0)&&(puntaje_salud == 0))
    {
        printf("aqui hay que porner algo que es cuando pone que no en todo");
    }
    getch();

    printf("\n\n  ------------------------------------------------------------------------------------------------ \n");
    printf(" |                                                                                                |\n");
    printf(" |  Si despues de hacer este test vocacional todavia no puedes definir tu carrera universitaria,  |\n");
    printf(" |  todavia puedes agotar otros recursos. En primer lugar, puedes hacer una consulta profesional  |\n");
    printf(" |  con un especialista en Psicologia que pueda orientarte. Otra herramienta es solo ¡pensar y    |\n");
    printf(" |  jugar un poco! Porque si bien no sabes que te gustaria hacer, sabes exactamente lo que no te  |\n");
    printf(" |  gustaria. Hacer una gran lista con esta informacion puede resultar esclarecedor al final.     |\n");
    printf(" |  Al mismo tiempo, puedes hacer una lista de tus hobbies preferidos… Y seguir investigando      |\n");
    printf(" |  hasta encontrar lo que te interesa!                                                           |\n");
    printf(" |                                                                                                |\n");
    printf("  ------------------------------------------------------------------------------------------------ ");
    printf("\n\n Presione cualquier tecla para volver al menu");
    getch();

}

void test_ansiedad(list *ListAnsiedad)
{
    FILE *entrada_preguntas = fopen("preguntas_test_ansiedad.csv","r");

    char *linea;
    char *preguntaR;
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
        punto = (get_csv_field(linea, 2));
        datos_test *m = crear_pregunta(preguntaR,punto);
        list_push_back(ListAnsiedad,m);
        linea = (char*) malloc(sizeof(char)*1024);
    }

    system("cls");
    printf("\n  ---------------------------------------TEST ANSIEDAD---------------------------------------");
    printf("\n |                                                                                           |");
    printf("\n |   Sentir ansiedad de modo ocasional es una parte normal de la vida. Sin embargo, las      |");
    printf("\n |   personas con trastornos de ansiedad con frecuencia tienen preocupaciones y miedos       |");
    printf("\n |   intensos, excesivos y persistentes sobre situaciones diarias. Con frecuencia, en los    |");
    printf("\n |   trastornos de ansiedad se dan episodios repetidos de sentimientos repentinos de         |");
    printf("\n |   ansiedad intensa y miedo o terror que alcanzan un maximo en una cuestión de minutos     |");
    printf("\n |   (ataques de panico).                                                                    |");
    printf("\n |                                                                                           |");
    printf("\n  -------------------------------------------------------------------------------------------");
    printf("\n\n Presione cualquier tecla para comenzar el test");
    getch();
    system("cls");

    datos_test *dato;
    dato = list_first (ListAnsiedad);
    int puntaje = 0;
    while(dato != NULL)
    {
        printf("\nContestar con 'si' o 'no', por favor\n");
        printf("--------------------------------------\n\n");
        printf("%s\n",dato->pregunta);

        while(1)
        {
            printf("\n");
            getchar();
            scanf("%[^\n]s",respuesta_dada);
            if((strcmp(respuesta_dada,"NO")==0)||(strcmp(respuesta_dada,"no")==0)||(strcmp(respuesta_dada,"No")==0)||(strcmp(respuesta_dada,"SI")==0)||(strcmp(respuesta_dada,"si")==0)||(strcmp(respuesta_dada,"Si")==0))
            {
                break;
            }
            printf("\nRespuesta no valida, por favor vuelva a contestar\n");
        }
        system("cls");

        if((strcmp("si",respuesta_dada)==0)&&(strcmp("1",dato->puntos)==0)){
            puntaje++;
        }
        if((strcmp("no",respuesta_dada)==0)&&(strcmp("0",dato->puntos)==0)){
            puntaje++;
        }
        printf("%i\n\n",puntaje);
        dato = list_next(ListAnsiedad);
    }
        printf("\n");

    if(puntaje >= 7)
    {

        printf("  ----------------------------------------------------------------------------------------------------\n");
        printf(" |  Tu puntaje final es: %d                                                                           |\n",puntaje);
        printf(" |                                                                                                    |\n");
        printf(" |  Tu puntuacion ha sido muy alta, es posible que tus niveles de preocupación sean bastante bajos    |\n");
        printf(" |  esto es una buena noticia puesto que significa que tienes buenas capacidades para tu bienestar    |\n");
        printf(" |  mental y emocional.                                                                               |\n");
        printf(" |                                                                                                    |\n");
        printf("  ----------------------------------------------------------------------------------------------------\n\n");
        printf(" Para volver al menu principal presione cualquier tecla");
        getch();

    }
    else
    {
        if (puntaje <= 3)
        {
            printf("\n  ----------------------------------------------------------------------------------------------------\n");
            printf(" |  Tu puntaje final es: %d                                                                            |\n",puntaje);
            printf(" |                                                                                                    |\n");
            printf(" |  Tuviste un puntaje bastante bajo, eso quiere decir muestras una preocupacion excesiva por         |\n");
            printf(" |  lo que te rodea, se muestra aprensiva y tensa. Es recomendable que acudas a un especialista       |\n");
            printf(" |  a un especialista para poder tratar la ansiedad.                                                  |\n");
            printf(" |                                                                                                    |\n");
            printf("  ----------------------------------------------------------------------------------------------------\n\n");
            printf(" Para volver al menu principal presione cualquier tecla");
            getch();

        }
        else

        {
            printf("  --------------------------------------------------------------------------------------------------------\n");
            printf(" |  Tu puntaje final es: %d                                                                               |\n",puntaje);
            printf(" |                                                                                                       |\n");
            printf(" |  Cumples con algunos criterios diagnosticos de ansiedad pero de momento no se han manifestado de una  |\n");
            printf(" |  de una manera demasiado grave. Sin embargo, conviene recordar que es importante mantener una buena   |\n");
            printf(" |  salud mental.                                                                                        |\n");
            printf(" |                                                                                                       |\n");
            printf("  -------------------------------------------------------------------------------------------------------\n\n");
            printf(" Para volver al menu principal presione cualquier tecla");
            getch();
        }


    }
}


void test_inteligencia(list *ListInteligenciaEmocional)

{
    FILE *entrada_preguntas = fopen("preguntas_test_inteligencia.csv","r");

    char *linea;
    char *preguntaR;
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
        punto = (get_csv_field(linea, 2));
        datos_test *m = crear_pregunta(preguntaR,punto);
        list_push_back(ListInteligenciaEmocional,m);
        linea = (char*) malloc(sizeof(char)*1024);
    }

    system("cls");
    printf("\n  ---------------------------------TEST INTELIGENCIA EMOCIONAL---------------------------------");
    printf("\n |                                                                                             |");
    printf("\n |     El termino Inteligencia Emocional (IE) se refiere a la capacidad humana de sentir       |");
    printf("\n |     entender, controlar y modificar estados emocionales en uno mismo y en los demas.        |");
    printf("\n |     Inteligencia Emocional no significa ahogar las emociones, sino dirigirlas               |");
    printf("\n |     y equilibrarlas hacia estados positivos.                                                |");
    printf("\n |                                                                                             |");
    printf("\n  ---------------------------------------------------------------------------------------------");
    printf("\n\n Presione cualquier tecla para comenzar el test");
    getch();
    system("cls");

    datos_test *dato;
    dato = list_first (ListInteligenciaEmocional);
    int puntaje = 0;
    while(dato != NULL)
    {
        printf("\nContestar con 'si' o 'no', por favor\n");
        printf("--------------------------------------\n\n");
        printf("%s\n",dato->pregunta);

        while(1)
        {
            printf("\n");
            getchar();
            scanf("%[^\n]s",respuesta_dada);
            if((strcmp(respuesta_dada,"NO")==0)||(strcmp(respuesta_dada,"no")==0)||(strcmp(respuesta_dada,"No")==0)||(strcmp(respuesta_dada,"SI")==0)||(strcmp(respuesta_dada,"si")==0)||(strcmp(respuesta_dada,"Si")==0))
            {
                break;
            }
            printf("\nRespuesta no valida, por favor vuelva a contestar\n");
        }
        system("cls");
        if((strcmp("no",respuesta_dada)==0)&&(strcmp("0",dato->puntos)==0)){
            puntaje++;
        }
        if((strcmp("si",respuesta_dada)==0)&&(strcmp("1",dato->puntos)==0)){
            puntaje++;
        }
        dato = list_next(ListInteligenciaEmocional);
    }

        printf("\n");
            if(puntaje >= 7)
    {

        printf("  ----------------------------------------------------------------------------------------------------\n");
        printf(" |  Tu puntaje final es: %d                                                                           |\n",puntaje);
        printf(" |                                                                                                    |\n");
        printf(" |  Eres una persona muy consciente de ti misma y de tus emociones, esto te hace sentir fuerte frente |\n");
        printf(" |  a las dificultades de la vida cotidiana. Percibes sin dificultad las diferencias, tanto grandes   |\n");
        printf(" |  como pequeñas, que existen entre las distintas emociones, como por ejemplo entre la ilusión y la  |\n");
        printf(" |  alegría, o la ira y el miedo. Tus comportamientos resultantes, por tanto, van acorde en cada      |\n");
        printf(" |  momento y situación, no tienes nunca que lamentarte de haberactuado de forma irracional.          |\n");
        printf(" |                                                                                                    |\n");
        printf("  ----------------------------------------------------------------------------------------------------\n\n");
        printf(" Para volver al menu principal presione cualquier tecla");
        getch();

    }
    else
    {
        if (puntaje <= 3)
        {
            printf("\n  --------------------------------------------------------------------------------------------------------\n");
            printf(" |  Tu puntaje final es: %d                                                                                 |\n",puntaje);
            printf(" |                                                                                                         |\n");
            printf(" |  Has obtenido una puntuacion bastante baja, de lo que se desprende que eres una persona                 |\n");
            printf(" |  atrapada en tus propias emociones. No percibes siempre correctamente las diferencias entre las         |\n");
            printf(" |  emociones. Puede que en situaciones de gran estres no distingas entre la ira y el miedo. Esto implica  |\n");
            printf(" |  que adems careces de empatia (la capacidad de entender las emociones de los dems), ya que al no        |\n");
            printf(" |  reconocer e identificar las tuyas propias, tampoco lo puedes hacer de forma acertada con las ajenas.   |\n");
            printf(" |                                                                                                         |\n");
            printf("  --------------------------------------------------------------------------------------------------------\n\n");
            printf(" Para volver al menu principal presione cualquier tecla");
            getch();

        }
        else
        {
            printf("  ----------------------------------------------------------------------------------------------------\n");
            printf(" |  Tu puntaje final es: %d                                                                           |\n\n",puntaje);
            printf(" |                                                                                                    |\n");
            printf(" |  Eres una persona bastante consciente de ti misma y de tus emociones, aunque muchas veces  lo que  |\n");
            printf(" |  haces mas bien es aceptarlas resignadamente. Percibes las diferencias que existen entre las       |\n");
            printf(" |  distintas emociones, aunque a veces te puedes equivocar, sobre todo cuando estas son más sutiles  |\n");
            printf(" |  como por ejemplo entre la ilusión y la alegria, o la ira y la decepcion. De todos tus             |\n");
            printf(" |  comportamientos resultantes suelen ir acorde con la situacion y no sueles tener que lamentarte    |\n");
            printf(" |  de haber actuado de forma irracional.                                                             |\n");
            printf(" |                                                                                                    |\n");
            printf("  ----------------------------------------------------------------------------------------------------\n\n");
            printf(" Para volver al menu principal presione cualquier tecla");
            getch();
        }


    }
}

void test_depresion(list *ListDepresion)
{
    FILE *entrada_preguntas = fopen("preguntas_depresion.csv","r");

    char *linea;
    char *preguntaR;
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
        punto = (get_csv_field(linea, 2));
        datos_test *m = crear_pregunta(preguntaR,punto);
        list_push_back(ListDepresion,m);
        linea = (char*) malloc(sizeof(char)*1024);
    }
    system("cls");
    printf("\n  --------------------------------------TEST DE DEPRESION -----------------------------------");
    printf("\n |                                                                                           |");
    printf("\n |                                                                                           |");
    printf("\n |  Es importante que si crees sufrir depresion no dejes de consultar con un profesional     |");
    printf("\n |  calificado (psicologo con especializacion en trastornos del animo), quien te dara la     |");
    printf("\n |  guia de lo que debes hacer para superar este problema. Mientras mas tiempo pase, el      |");
    printf("\n |  problema puede volverse mas dificil de superar, pero siempre hay posibilidades de        |");
    printf("\n |  tratarlo.                                                                                |");
    printf("\n |                                                                                           |");
    printf("\n  -------------------------------------------------------------------------------------------");
    printf("\n\n Presione cualquier tecla para comenzar el test");
    getch();
    system("cls");


    datos_test *dato;
    dato = list_first (ListDepresion);
    int puntaje = 0;
    while(dato != NULL)
    {
        printf("\nContestar con 'si' o 'no', por favor\n");
        printf("--------------------------------------\n\n");
        printf("%s\n",dato->pregunta);

        while(1)
        {
            printf("\n");
            getchar();
            scanf("%[^\n]s",respuesta_dada);
            if((strcmp(respuesta_dada,"NO")==0)||(strcmp(respuesta_dada,"no")==0)||(strcmp(respuesta_dada,"No")==0)||(strcmp(respuesta_dada,"SI")==0)||(strcmp(respuesta_dada,"si")==0)||(strcmp(respuesta_dada,"Si")==0))
            {
                break;
            }
            printf("\nRespuesta no valida, por favor vuelva a contestar\n");
        }
        system("cls");

        if((strcmp("si",respuesta_dada)==0)&&(strcmp("1",dato->puntos)==0)){
            puntaje++;
        }
        if((strcmp("no",respuesta_dada)==0)&&(strcmp("0",dato->puntos)==0)){
            puntaje++;
        }
        dato = list_next(ListDepresion);
    }
        printf("\n");
    if(puntaje >= 7)
    {
        printf("  ----------------------------------------------------------------------------------------------------\n");
        printf(" |  Tu puntaje final es: %d                                                                           |\n\n",puntaje);
        printf(" |                                                                                                    |\n");
        printf(" |  Al parecer tu estado de animo es estable y no tienes sintomatologia depresiva suficiente          |\n");
        printf(" |  aunque siempre es recomendable verificarlo con un profesional calificado. Segun las respuestas    |\n");
        printf(" |  que nos brindaste, te involucras de forma saludable con tus propios asuntos y con los de otras    |\n");
        printf(" |  personas, lo que da cuenta de que no hay conflictos emocionales de importancia que afecten tu     |\n");
        printf(" |  sensibilidad emocional o que te atrapen en sentimientos de desesperanza o tristeza extrema. Te    |\n");
        printf(" |  recomendamos seguir cuidando tu salud mental y emocional y buscar ayuda profesional siempre que   |\n");
        printf(" |  enfrentes un conflicto personal que te sea dificil superar por ti mismo. Por ahora, sin embargo,  |\n");
        printf(" |  pareciera que tu vida te es grata y que puedes compartir ese bienestar con otras personas de      |\n");
        printf(" |  tu entorno. Felicitaciones por tu puntuacion!                                                     |\n");
        printf("  ----------------------------------------------------------------------------------------------------\n\n");
        printf(" Para volver al menu principal presione cualquier tecla");
        getch();

    }
    else
    {
        if (puntaje <= 3)
        {
            printf("\n  --------------------------------------------------------------------------------------------------------\n");
            printf(" |  Tu puntaje final es: %d                                                                                |\n",puntaje);
            printf(" |                                                                                                        |\n");
            printf(" |  De acuerdo con tus respuestas, estas en el grupo de las personas que presenta mayor sintomatologia    |\n");
            printf(" |  depresiva, lo cual no necesariamente implica un diagnostico de depresion, pero te recomendamos        |\n");
            printf(" |  fuertemente que visites un profesional de la salud para que lo confirme o lo descarte. Y es que tu    |\n");
            printf(" |  estado de animo parece estar bastante disminuido, sin mucha esperanza en el futuro y con bastantes    |\n");
            printf(" |  emociones de tristeza e irritabilidad. Tampoco hay un sentido de vida claro ni mucha esperanza en     |\n");
            printf(" |  poder construir una vida de calidad en el futuro, lo cual se acompaña de algunos sintomas fisicos     |\n");
            printf(" |  relacionados. Probablemente has experimentado situaciones tan dolorosas que te imaginas que si        |\n");
            printf(" |  sales de tu zona protegida siempre te va a ocurrir lo mismo y eso te hace sentir atrapado(a)          |\n");
            printf(" |  en tu dinamica de vida. Si es asi, te recomendamos darte animo para salir, hacer actividades y buscar |\n");
            printf(" |  ayuda profesional a pesar que no tengas ganas, ya que si te dejas estar, esta estudiado que el        |\n");
            printf(" |  pronóstico tiende a empeorar. Sabemos que es muy dificil superar los estados de desánimo y que puedas |\n");
            printf(" |  ver o creer en una salida, pero tambien sabemos que es más dificil vivir una vida poco gratificante,  |\n");
            printf(" |  donde los demas empiezan a volverse indiferentes o molestos y donde la desesperanza es una            |\n");
            printf(" |  constante. Ojala te puedas dar otra oportunidad y busques ayuda profesional seria para comenzar a     |\n");
            printf(" |  cambiar la manera cotidiana de sentirte y recuperar tu bienestar.                                     |\n");
            printf("  --------------------------------------------------------------------------------------------------------\n\n");
            printf(" Para volver al menu principal presione cualquier tecla");
            getch();

        }
        else
        {
            printf("\n -----------------------------------------------------------------------------------------------------\n");
            printf("|  Tu puntaje final es: %d                                                                             |\n",puntaje);
            printf("|                                                                                                     |\n");
            printf("|  Segun las respuestas brindadas, pareciera que si bien no te encuentras en un estado depresivo      |\n");
            printf("|  propiamente tal, hay ciertas situaciones en tu vida que te estan afectando considerablemente,      |\n");
            printf("|  lo cual te recomendamos poder tratarlas a tiempo. Recuerda que el diagnostico de depresion solo    |\n");
            printf("|  te lo puede dar un profesional calificado. No obstante, tu mismo(a) eres capaz de evaluar cuando   |\n");
            printf("|  hay conflictos emocionales que te esten pasando la cuenta y el solo hecho de no estar viviendo     |\n");
            printf("|  una vida de calidad es motivo suficiente para buscar ayuda. En nuestro test constatamos que        |\n");
            printf("|  efectivamente en la actualidad estas pasando por algunas situaciones dificiles que te impiden      |\n");
            printf("|  disfrutar a fondo de tus actividades y relaciones interpersonales. Sentimientos de soledad, falta  |\n");
            printf("|  de sentido, desanimo o perdida pueden ser parte de las emociones que te embargan en lo cotidiano,  |\n");
            printf("|  aunque al parecer tienes esperanza en que se pueden solucionar (solo te falta saber como hacer un  |\n");
            printf("|  cambio y ponerte manos a la obra).                                                                 |\n");
            printf(" -----------------------------------------------------------------------------------------------------\n\n");
            printf("Para volver al menu principal presione cualquier tecla");
            getch();

        }
    }

    getch();
}

int main(){
    int op;

    do
    {
        printf("\n  ------------------ MENU --------------------\n");
        printf(" |                                            |\n");
        printf(" |   0. Salir del menu                        |\n");
        printf(" |   1. Comenzar test vocacional              |\n");
        printf(" |   2. Comenzar test ansiedad                |\n");
        printf(" |   3. Comenzar test depresion               |\n");
        printf(" |   4. Comenzar test inteligencia emocional  |\n");
        printf(" |                                            |\n");
        printf("  --------------------------------------------\n\n");
        printf(" Ingrese un numero del 0-4 : ");
        scanf("%d",&op);

        if (op == 1)
        {
            list *listVocacional = list_create_empty();
            Map *mapVocacional = createMap(stringHash,stringEqual);
            system("cls");
            test_vocacional(mapVocacional,listVocacional);
            printf("\n");
        }

        if (op == 2)
        {
            list *ListAnsiedad = list_create_empty();
            system("cls");
            test_ansiedad(ListAnsiedad);
            printf("\n");
        }

        if(op == 3)
        {
            list *ListDepresion = list_create_empty();
            system("cls");
            test_depresion(ListDepresion);
            printf("\n");
        }

        if(op == 4)
        {
            list *ListInteligenciaEmocional = list_create_empty();
            system("cls");
            test_inteligencia(ListInteligenciaEmocional);
            printf("\n");
        }
        system("cls");
    }while(op != 0);

    return 0;
}
