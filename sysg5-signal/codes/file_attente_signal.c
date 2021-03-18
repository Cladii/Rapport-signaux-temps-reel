#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void traitement(int signal)
{
    printf("Signal reçu \n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d \n", i);
        sleep(1);
    }
}

int main()
{
    struct sigaction action;
    action.sa_handler = traitement;
    sigaction(SIGUSR1, &action, NULL);
    sigset_t masque;
    sigemptyset(&masque);
    sigaddset(&masque, SIGUSR1);
    sigprocmask(SIG_BLOCK, &masque, NULL);
    if (fork() == 0)
    {
        kill(getppid(), SIGUSR1);
        kill(getppid(), SIGUSR1);
        kill(getppid(), SIGUSR1);
    }
    else
    {
        sleep(1);
        sigprocmask(SIG_UNBLOCK, &masque, NULL);
    }
}
