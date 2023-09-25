#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void kctrlc(int signum){
    printf("He rebut un ctrl + c (%d).\n",signum);
}
void ksigalrm(int signum){
    printf("He rebut un sigalrm (%d).\n",signum);
    alarm(2);//Cada 2 segons m'arriba un alarm
}
void kgeneric(int signum){
    printf("He rebut un altre senyal (%d).\n",signum);
}

void ksighandler(int signum){
    switch(signum){
        case SIGINT:
            kctrlc(signum);
        break;
        case SIGALRM:
        ksigalrm(signum);
        break;
        default:
        kgeneric(signum);
        break;
    }
    signal(signum,ksighandler);
    //Ho reprogramo per si m'arriba un segon signal de un que ja m'hagi arribat
}

int main(){
    int i;
    for(i=1;i<=64;i++){
        //Amb aquest bucle estic reprogramant tots els signals

        signal(i,ksighandler);
    }
    alarm(5);//Al cap de 5 segons m'arriba un sigalarm
    //El alarm es pot reprogramar amb el SIGALRM
    while(1){
        printf("Soc el putu pid de merda: %d i espero senyals\n",getpid());
        //sleep(1);//Consumeix cpu
        pause();
    }

}