#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
  int childpid;
  if ((childpid = fork()) == -1)
  {
    perror("Can't fork it.\n");
    exit(1);
  }
  else if (childpid == 0)
  {
    while(1) printf("%d ", getpid());
    return 0;
  }
  else 
  {
    while(1) printf("%d ", getpid());
    return 0;
  }
}
