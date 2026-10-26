#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* does the same as the shell command:   ls /usr/bin | grep x | wc -l
 * two pipes, three children:  ls --a--> grep --b--> wc            */

static int a[2], b[2];

/* every process closes all four pipe ends it does not need any more */
static void close_all(void)
{
    close(a[0]); close(a[1]);
    close(b[0]); close(b[1]);
}

/* start one stage: its stdin becomes in_fd, its stdout becomes out_fd (-1 = keep) */
static void stage(int in_fd, int out_fd, char *const argv[])
{
    if (fork() != 0)
        return;                                  /* parent: go start the next stage */
    if (in_fd >= 0)  { close(0); dup(in_fd); }   /* smallest free number: 0 */
    if (out_fd >= 0) { close(1); dup(out_fd); }  /* smallest free number: 1 */
    close_all();
    execvp(argv[0], argv);
    perror(argv[0]);
    exit(127);
}

int main(void)
{
    if (pipe(a) < 0 || pipe(b) < 0) { perror("pipe"); return 1; }

    char *ls[]   = { "ls", "/usr/bin", NULL };
    char *grep[] = { "grep", "x", NULL };
    char *wc[]   = { "wc", "-l", NULL };

    stage(-1,   a[1], ls);                       /* ls   writes into a      */
    stage(a[0], b[1], grep);                     /* grep reads a, writes b  */
    stage(b[0], -1,   wc);                       /* wc   reads b            */

    close_all();                                 /* or wc never sees end of file */
    for (int i = 0; i < 3; i++)
        wait(NULL);
    return 0;
}
