#if defined(_POSIX_REALTIME_SIGNALS)
#error "Pas de signaux temps-réel disponibles"
#endif

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define SIGRTUPDATE (SIGRTMIN)

bool etat = false;

void traitement(int signal, siginfo_t *info, void *inutile)
{
    etat = info->si_value.sival_int;
    printf("Bascule en état %d \n", etat);
}

int main()
{
    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = traitement;
    sigaction(SIGRTUPDATE, &action, NULL);
    if (fork() == 0)
    {
        union sigval valeur;
        for (int i = 0; i < 10; ++i)
        {
            valeur.sival_int = 1;
            sigqueue(getppid(), SIGRTUPDATE, valeur);
            printf("Signal SIGRTUPDATE envoyé. Valeur = %d \n", valeur.sival_int);
            valeur.sival_int = 0;
            sigqueue(getppid(), SIGRTUPDATE, valeur);
            printf("Signal SIGRTUPDATE envoyé. Valeur = %d \n", valeur.sival_int);
        }
        exit(0);
    }
    else
    {
        sleep(1);
    }
}
