#include "kernel/types.h"
#include "user/user.h"

// sleep <ticks>: pause the calling process for the given number of clock ticks
int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "usage: sleep <ticks>\n");
    exit(1);
  }
  pause(atoi(argv[1]));   // system call into the kernel (sleep() was renamed to pause())
  exit(0);
}
