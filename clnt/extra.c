/*
** commands2.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:24:38 2015 
** Last update Sat Mar 28  01:33:01 2015 
*/

#include	"../include/defs.h"

int             send_stor(char **t, FILE *f, char *buff)
{
  FILE          *fd;

  if ((fd = fopen(t[1], "r")) == NULL)
    {
      perror("fopen");
      return (0);
    }
  fclose(fd);
  if (t[2])
    snprintf(buff, 1023, "STOR %s\r\n", t[2]);
  else
    snprintf(buff, 1023, "STOR %s\r\n", t[1]);
  if (write(fileno(f), buff, strlen(buff)) < 0)
    {
      perror("write");
      return (1);
    }
  return (0);
}
