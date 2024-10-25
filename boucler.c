#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>


void action(int sig) {
    printf(">> SIGUSR1 received by %d\n", getpid());
}

int main(int argc, char* argv[]){

    struct sigaction sa;

    sa.sa_handler = action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;


    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    int cadence = atoi(argv[1]); 
    int nombreAffichage = atoi(argv[2]); 

    while(1){
      
        time_t now = time (NULL);

        struct tm tm_now = *localtime (&now);

        char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];

        strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);

        for(int i = 0; i < nombreAffichage; i++){
            /* afficher le resultat : */
            printf("mon numero est %d , il est : ", getpid()); 
            printf ("'%s'\n", s_now);
            
        }
        sleep(cadence); 
   
    }
    return 0;
}
