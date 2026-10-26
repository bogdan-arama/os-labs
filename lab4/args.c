#include "kernel/types.h"
#include "user/user.h"

// args: print every argument exactly as the kernel delivered it to main()
int
main(int argc, char *argv[])
{
  printf("argc = %d\n", argc);
  for(int i = 0; i < argc; i++)
    printf("argv[%d] = [%s]\n", i, argv[i]);
  exit(0);
}
