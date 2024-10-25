#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    
    
    if (execlp("/home/tsl4297a/sr2/systemes/sr2_systemes_tp1/boucler", "boucler", "1", "3", NULL) == -1) {
        perror("error executing boucler");
        exit(EXIT_FAILURE);
    }

    return 0;  
}
