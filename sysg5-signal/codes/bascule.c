#if defined(_POSIX_REALTIME_SIGNALS)
#error "Pas de signaux temps-réel disponibles"
#endif

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define SIGRTUP (SIGRTMIN)
#define SIGRTDOWN (SIGRTMIN + 1)

bool etat = false;

void traitement(int signal, siginfo_t *info, void *inutile)
{
    if (signal == SIGRTUP)
        etat = true;
    else
        etat = false;
    printf("Bascule en-état %d \n", etat);
}

int main()
{
    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = traitement;
    sigaction(SIGRTUP, &action, NULL);
    sigaction(SIGRTDOWN, &action, NULL);
    sigset_t masque;
    sigemptyset(&masque);
    sigaddset(&masque, SIGRTUP);
    sigaddset(&masque, SIGRTDOWN);
    sigprocmask(SIG_BLOCK, &masque, NULL);
    for (int i = 0; i < 10; i++)
    {
        raise(SIGRTUP);
        printf("Signal SIGRTUP envoyé \n");
        raise(SIGRTDOWN);
        printf("Signal SIGRTDOWN envoyé \n");
    }
    sigprocmask(SIG_UNBLOCK, &masque, NULL);
}
