#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void tipusBasics(){
    int enter;
    char string[100],pregunta[]="Digam el nombre pi amb 4 decimals: ";
    char buffer[200];
    float nombrePi=3.1416;
    char nombreUser[10];
    float nombreUserAtof;

    enter = read(0, string, 100);
    //Enter es la quantitat de bytes que s'han lllegit
     //El 0 es que el file descriptor es 0 i la informacio es de entrada (vindra pel teclat)
    //El 100 es la mida del string que com a maxim llegira
    string[enter-1] = '\0';//Als strings se li te que asignar manualment el final de la paraula
    sprintf(buffer, "Input string: [%s] %ld characters\n", string, strlen(string)); 
    write(1, buffer, strlen(buffer));

//• Tipos básicos (int, char, short, float, etc.).

    write(1,pregunta,strlen(pregunta));
    read(0,nombreUser,sizeof(nombreUser));
    nombreUserAtof=atof(nombreUser);
    //• Uso de bucles y condicionales.

    if(nombrePi==nombreUserAtof)
        write(1,"Bona\n",5);
    else
            write(1,"Mala\n",5);

}
void createStructs(){

}

int main(){
    tipusBasics();
    createStructs();

    return 0;
}