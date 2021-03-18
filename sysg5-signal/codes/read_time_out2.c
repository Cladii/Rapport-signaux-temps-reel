#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <setjmp.h>

sigjmp_buf env;

static void sig_handler(int);

int main(int argc, char *argv[])
{
    char c;
    printf("Tapez return en moins de 5 secondes ! \n");
    if (signal(SIGALRM, sig_handler) == SIG_ERR)
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    if (siginterrupt(SIGALRM, true) < 0)
    {
        perror("siginterrupt");
        exit(EXIT_FAILURE);
    }
    int r = 0;
    //on enregistre l'environnement
    if (sigsetjmp(env, 1) == 0)
    {
        //on passe une première fois dans le if car le premier appel à setjmp renvoie toujours 0
        //le second appel à setjmp par longjmp renvoie lui une valeur non nulle
        //sig_handler n'a pas encore été appelé
        alarm(5);
        //même si le programme était bloqué après l'instanciation de la minuterie et avant la lecture du clavier.
        //on n'est pas bloqué car le signal sigalarm doit être traité avant que le code continue donc on finit dans le sig_handler
        //qui nous emmène dans le else et on n'est pas bloqué car le read n'est jamais lancé.
        r = read(STDIN_FILENO, &c, 1);
    }
    else
    {
        // sig_handler a déjà été exécuté
        // le délai a déjà expiré, inutile de faire read
    }
    if ((r == 1) && (c == '\n'))
    {
        printf("Gagné ! \n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Perdu ! \n");
        exit(EXIT_FAILURE);
    }
}

static void sig_handler(int signum)
{
    siglongjmp(env, 1);
}