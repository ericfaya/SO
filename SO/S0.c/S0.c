//Logins: eric.faya i victor.corral
//Nombres Eric Faya Esteban i Victor Alfonso Corral Morales

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VALUE 100

typedef struct {
    char nomNen[100];
    int anyNaixement;
    int inscripcio; // si es ok 1 i si es ko 0;
    char salud[100];
    int targetaSanitaria;
    int dni;
    int imagen;
} Nen;

void guardaInfoMemory(char cadena[MAX_VALUE],  int *nensCount,int quinCampEs,Nen *nuevoNen) {
    if (*nensCount < 25) {
        //fem malloc amb mida nen
        //comprovem malloc dona espai
      
        switch(quinCampEs){
            case 0:  
               // nens[*nensCount] = nuevoNen; //posicio nou nen
                (*nensCount)++;
                strcpy(nuevoNen->nomNen, cadena); //copiem lo de la cadena en el nomNen. fletxa perq es punter
            break;
            case 1:
                nuevoNen->anyNaixement=1999;
            break;
            case 2:
                if(strcmp(cadena,"OK")){
                    nuevoNen->inscripcio=0;
                }
                else if(strcmp(cadena,"KO")){
                    //Aqui yo faria per cada "," que troba de la cadena ,sumarli un a la incriupcio:exemple
                    //[Salut Gluten,Fructosa, Llet llavors si te dos comas son 3 i si te una coma es 2
                    nuevoNen->inscripcio=1;
                }
            break;
            case 3:
                strcpy(nuevoNen->salud, cadena); //copiem lo de la cadena en el nomNen. fletxa perq es punter
            break;
            case 4:
                if(strcmp(cadena,"OK")){
                    nuevoNen->inscripcio=0;
                }
                else if(strcmp(cadena,"KO")){
                    nuevoNen->inscripcio=1;
                }
            break;
            case 5:
                if(strcmp(cadena,"OK")){
                    nuevoNen->inscripcio=0;
                }
                else if(strcmp(cadena,"KO")){
                    nuevoNen->inscripcio=1;
                }
            break;
            case 6:
                if(strcmp(cadena,"Yes")){
                    nuevoNen->inscripcio=0;
                }
                else if(strcmp(cadena,"No")){
                    nuevoNen->inscripcio=1;
                }
            break; 
        
        }
    }         
}

int extraeInfo(char byteLlegit[1], int contador, char cadena[MAX_VALUE], int *nensCount,int quinCampEs,Nen *nuevoNen) {
    

    if (byteLlegit[0] != '[' && byteLlegit[0] != ']') {
        cadena[contador] = byteLlegit[0];
        contador++;
    } else {
       
        cadena[contador] = '\0';
       // if (contador > 0) {
           /* if (cadena[0] == '*' && contador > 1) {
                enter = atoi(cadena + 1); //fem servir atoi del sistema, +1 per no pillar asterisco
                printf("Num: %d\n", enter);
            } else {*/
      /*  if(quinCampEs==0){
            Nen *nuevoNen = malloc(sizeof(Nen));//Pero clar d'aquesta forma cada cop que entra fa un malloc i no ho volem
        }

            if (nuevoNen != NULL) {*/
                guardaInfoMemory(cadena, nensCount,quinCampEs,nuevoNen);
            
                printf("%s\n", cadena);
          //  }
       // }
         quinCampEs++;
        contador = 0; // Reiniciar contador
        if(quinCampEs>6){
            quinCampEs=0;//Ja em acabat un nen
        }
    }
    return contador;
}

void readBinaryFile(int fd_file_bin,º int *nensCount,Nen *nuevoNen) {
    int posicioCadenaBinari = 0;
    char byteLlegit[1];
    char cadena[MAX_VALUE];
 //   char intBuffer[4];
    int final_ficher;
   // int entero_leido;
    int quinCampEs=0;

    final_ficher = read(fd_file_bin, byteLlegit, sizeof(byteLlegit));
    while (final_ficher != 0 && final_ficher != -1) {
        //Si es 0 es que ha arribat al final del arxiu perque els bytes llegits seran 0 i si es -1 es que ha hagut un error
        // while (byteLlegit[0] != '#') { // Hasta el final del archivo
  
        if (byteLlegit[0] != '*' /*|| posicioCadenaBinari > 0*/) {
            posicioCadenaBinari = extraeInfo(byteLlegit, posicioCadenaBinari, cadena, nensCount,quinCampEs,nuevoNen);
        } else if(byteLlegit[0] == '*'){
            //final_ficher = read(fd_file_bin, intBuffer, sizeof(intBuffer)); //Per llegir el segon asterisc
            //entero_leido = atoi(intBuffer);
          // printf("any eeeeeeee%d",entero_leido);
            //final_ficher = read(fd_file_bin, byteLlegit, sizeof(byteLlegit)); //Per llegir el segon asterisc
        }
        final_ficher = read(fd_file_bin, byteLlegit, sizeof(byteLlegit));
    }
   
    close(fd_file_bin);
}

int main(int argc, char *argv[]) {
    int fd_file_bin;
    Nen *nens[25];
    int nensCount = 0;

        for (int i = 0; i < 25; i++) {
            Nen *nuevoNen = malloc(sizeof(Nen));//Pero clar d'aquesta forma cada cop que entra fa un malloc i no ho volem
            if (nuevoNen != NULL) {
                if (argc < 2) {
                    fprintf(stderr, "Falten arguments\n");
                    return -1;
                } else {
                    fd_file_bin = open(argv[1], O_RDONLY);
                }
                if (fd_file_bin < 0) {
                    fprintf(stderr, "ERROR: Can't open file '%s'\n\n", argv[1]);
                    return -2;
                } else {
                    readBinaryFile(fd_file_bin, nens, &nensCount,nuevoNen);
                }

                /* info nens
                for (int i = 0; i < nensCount; i++) {
                    printf("Nombre: %s\n", nens[i]->nomNen);
                    // Imprimir otros campos según sea necesario
                }*/
            }
        }

    

    // free per cada espaoi
    for (int i = 0; i < nensCount; i++) {
        free(nens[i]);
    }

    return 0;
}