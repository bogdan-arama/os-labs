#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

// find <dir> <name> [-n]
// Print every path under <dir> whose last component is <name>.
// With -n, the inode number is printed next to each path.

int show_inode;

// return a pointer to the last component of path ("a/b/r2" -> "r2")
char *
basename(char *path)
{
  char *p = path + strlen(path);
  while(p > path && *(p - 1) != '/')
    p--;
  return p;
}

void
report(char *path, struct stat *st)
{
  if(show_inode)
    printf("%s %d\n", path, st->ino);
  else
    printf("%s\n", path);
}

void
find(char *path, char *name)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }
  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if(st.type != T_DIR){
    // a plain file or device: only the name has to match
    if(strcmp(basename(path), name) == 0)
      report(path, &st);
    close(fd);
    return;
  }

  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
    fprintf(2, "find: path too long: %s\n", path);
    close(fd);
    return;
  }
  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/';

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)                       // free slot in the directory
      continue;
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    if(strcmp(p, ".") == 0 || strcmp(p, "..") == 0)
      continue;                            // never walk back up or in place
    if(stat(buf, &st) < 0){
      fprintf(2, "find: cannot stat %s\n", buf);
      continue;
    }
    if(strcmp(p, name) == 0)
      report(buf, &st);
    if(st.type == T_DIR)
      find(buf, name);                     // descend; fd of this level stays open
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  if(argc == 4 && strcmp(argv[3], "-n") == 0)
    show_inode = 1;
  else if(argc != 3){
    fprintf(2, "usage: find <dir> <name> [-n]\n");
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}
