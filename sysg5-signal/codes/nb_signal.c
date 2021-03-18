#include <signal.h>
#include <stdio.h>

#if defined(_POSIX_REALTIME_SIGNALS)
#error "Pas de signaux temps-réel disponibles"
#endif

#define SIGRT0 (SIGRTMIN)
#define SIGRT1 (SIGRTMIN + 1)
#define SIGRT13 (SIGRTMIN + 13)
#define NB_SIGRT_NEEDED 14

int main()
{
    if ((SIGRTMAX - SIGRTMIN + 1) < NB_SIGRT_NEEDED)
        printf("Pas assez de signaux temps-réel \n");
    printf("Les signaux temps réels commencent à partir de %d \n", SIGRTMIN);
    printf("Les signaux temps réels finissent à %d \n", SIGRTMAX);
    printf("Nombre de signaux disponibles %d \n", SIGRTMAX - SIGRTMIN);
    printf("Nombre de signaux nécessaires %d \n", NB_SIGRT_NEEDED);
}