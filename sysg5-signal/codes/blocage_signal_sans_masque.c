#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int diviseur;

void traitement(int signal)
{
    diviseur = 0;
    printf("Diviseur vaut désormais 0 \n");
}

int main()
{
    struct sigaction action;
    action.sa_handler = traitement;
    sigaction(SIGUSR1, &action, NULL);
    long int val = 10000000000;
    diviseur = 10;
    if (fork() == 0)
    {
        sleep(4);
        printf("Signal SIGUSR1 envoyé \n");
        kill(getppid(), SIGUSR1);
        exit(0);
    }
    else
    {
        while (val != 100)
        {
            val = val / diviseur;
            printf("%ld \n", val);
            sleep(1);
        }
    }
}