#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

static void sig_handler(int);

ssize_t myreadtimer(int fd, void *buf, size_t count, unsigned timer);

int main(int argc, char *argv[])
{
  char c;
  printf("Tapez return en moins de 5 secondes ! \n");
  //on initialise le gestionnaire de signal pour traiter le signal sigalarm
  if (signal(SIGALRM, sig_handler) == SIG_ERR)
  {
    perror("signal");
    exit(EXIT_FAILURE);
  }
  //on modifie le  comportement d'un appel système interrompu
  //par un signal sigalarm pour que l'appel système renvoit -1 s'il n'y a eu
  //aucun transfert de données
  if (siginterrupt(SIGALRM, true) < 0)
  {
    perror("siginterrupt");
    exit(EXIT_FAILURE);
  }
  //on lance la minuterie
  alarm(5);
  //on lit au clavier
  int r = read(STDIN_FILENO, &c, 1);
  //le programme est bloqué par read
  //il sera débloqué soit par une lecture au clavier, soit par le signal sigalarm de la minuterie
  if ((r == 1) && (c == '\n'))
  {
    printf("Gagné ! \n");
    exit(EXIT_SUCCESS);
  }
  printf("Perdu ! \n");
  exit(EXIT_FAILURE);
}

static void sig_handler(int signum)
{
  printf("Signal sigalarm traité ! \n");
}

//On peut alors par exemple écrire une fonction comme read avec un paramètre
//supplémentaire qui serait la durée de la lecture au clavier
ssize_t myreadtimer(int fd, void *buf, size_t count, unsigned timer)
{
  if (siginterrupt(SIGALRM, true) < 0)
  {
    perror("siginterrupt");
    exit(EXIT_FAILURE);
  }
  alarm(timer);
  ssize_t r = read(fd, buf, count);
  alarm(0);
  return r;
}