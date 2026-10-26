#include "kernel/types.h"
#include "user/user.h"

// primes: the prime sieve as a chain of processes connected by pipes.
// Each stage reads its first number p (always a prime), prints it, and
// forwards to the next stage only the numbers that p does not divide.

void sieve(int in) __attribute__((noreturn));

void
sieve(int in)
{
  int p, n;

  if(read(in, &p, sizeof(p)) != sizeof(p)){   // nothing left: end of the chain
    close(in);
    exit(0);
  }
  printf("prime %d\n", p);

  int fd[2];
  pipe(fd);
  if(fork() == 0){
    close(fd[1]);                             // the child only reads
    close(in);
    sieve(fd[0]);
  }
  close(fd[0]);                               // this stage only writes forward
  while(read(in, &n, sizeof(n)) == sizeof(n))
    if(n % p != 0)
      write(fd[1], &n, sizeof(n));
  close(in);
  close(fd[1]);                               // next stage sees end of file
  wait(0);
  exit(0);
}

int
main(int argc, char *argv[])
{
  int fd[2];

  pipe(fd);
  if(fork() == 0){
    close(fd[1]);
    sieve(fd[0]);
  }
  close(fd[0]);
  for(int i = 2; i <= 35; i++)
    write(fd[1], &i, sizeof(i));
  close(fd[1]);
  wait(0);
  exit(0);
}
