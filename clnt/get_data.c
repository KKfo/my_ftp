/*
** get_data.c for my_ftp in /home/xxx/Epitech/2015/PSU_2014_myftp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 29 18:50:47 2015 
** Last update Sat Mar 28  01:32:00 2015 
*/

#include        	"../include/defs.h"

int                     write_localfile(FILE *stream, int srv)
{
  char                  buff[4096];
  int                   r;
  int                   fd;

  fd = fileno(stream);
  r = 0;
  while ((r = read(srv, buff, 4096)))
        write(fd, buff, r);
  return (0);
}

int                     get_data(t_vars *v, char flg)
{
  FILE                 *fd;
  size_t                r;
  char                  buff[2048];

  if (flg == 'l')
    {
      while ((r = read(v->server_fd, buff, 2048)))
        write(1, buff, r);
      return (0);
    }
  if (v->args[2])
    fd = fopen(v->args[2], "a");
  else
    fd = fopen(v->args[1], "a");
  if (fd == NULL)
    {
      return (EXIT_FAILURE);
    }
  write_localfile(fd, v->server_fd);
  return (0);
}
