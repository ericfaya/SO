#include <unistd.h>
#include <signal.h>

#include <stdio.h>

void patata(){
    printf("\nPorque me interrumpes perrillo\n");
    //signal(SIGINT,SIG_DFL);
    //Reprogramo amb els valors per defecte
    //signal(SIGINT,SIG_IGN);
    //Per cualseovl signal que m'arribi ho reporgramo perque mels ignori
}

int main(){

    signal(SIGINT,patata);
    //Aquesta linea reprograma
    //Cuan arribi un SIGINT anire al metode patata

    while(1){
        printf("Nada nuevo por ahi\n");
        pause();//Pausar fins que arribi un signal
    }
}