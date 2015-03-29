/*
** send_data.c for my_ftp in /home/xxx/Epitech/2015/PSU_2014_myftp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 29 18:51:52 2015 
** Last update Sun Mar 29 23:06:15 2015 
*/

#include        "../include/defs.h"

int                     send_data(t_vars *v)
{
  int                   r;
  char                  buff[4096];
  FILE                 *fd;

  if ((fd = fopen(v->args[1], "r")) == NULL)
    {
      perror("fopen");
      return (0);
    }
  while ((r = read(fileno(fd), buff, 4096)))
    write(v->server_fd, buff, r);
  return (0);
}
