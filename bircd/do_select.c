
#include <stdlib.h>
#include "bircd.h"

void	do_select(t_env *e)
{
  e->r = select(FD_SETSIZE, &e->fd_read, &e->fd_write, NULL, NULL);
  // if (e->r == -1)
  //   std::cout << "Select() ERROR\n"; 

}
