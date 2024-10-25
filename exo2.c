#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <aio.h>
#include <sys/wait.h>

// Écrire une application dans laquelle le père crée un processus fils qui aura le même comportement
// que le processus de l’exercice précédent (c’est-à-dire boucler indéfiniment en affichant, toutes les
// secondes, un message l’identifiant et en affichant un message spécifique lorsque le signal SIGUSR1
// lui parvient). Faire en sorte que le père ne puisse se terminer avant son fils.
// Exécuter l’application plusieurs fois pour vérifier son bon fonctionnement.

void action(int sig) {
    printf(">> SIGUSR1 received by %d\n", getpid());
}

void affichage(){
    printf("Je suis le processus %d \n", getpid()); 
}

int main(int argc, char* argv[]) {
    
    struct sigaction sa;

    sa.sa_handler = action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    int pid = fork(); 
    switch (pid){
        case -1:
        perror("erreur lors du fork"); 

        //On est dans le fils
        case 0:
        
        while(1){
            affichage(); 
            sleep(2); 
        }
        
        //On est dans le pere
        default:
        wait(NULL); 
        exit(0); 
    }

    return 0;  
}
