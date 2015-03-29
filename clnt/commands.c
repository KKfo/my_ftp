/*
** commands2.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:24:38 2015 
** Last update Sun Mar 29 16:41:31 2015 
*/

#include        "../include/defs.h"

int             ls(char **t, FILE *f, char *buff)
{
  size_t        s;
  int           r;
  int           p;

  s = 1023;
  /* int           passive; */

  /* passive = 0; */
  /* if(passive) */
  /*   send_passv_cmd(); */
  /* else */
  p = send_port_cmd(f);
  if (p == -1)
    {
      return(0);
    }
  /* if (t[1]) */
  /*   { */
  /*     fprintf(f, "LIST %s\r\n", t[1]); */
  /*     fflush(f); */
  /*   } */
  /* else */
  /*   { */
  if (r = write(fileno(f), "LIST \r\n", 7) < 0)
    {
      perror("write");
      return(1);
    }
  /* } */
  listen_to_server('l', NULL, p, f);
  getline(&buff, &s, f);
  printf("%s", buff);
  return (0);
}

int             cd(char **t, FILE *f, char *buff)
{
  UNUSED(t);
  UNUSED(f);
  return (0);
}

int             get(char **t, FILE *f, char *buff)
{
  UNUSED(t);
  UNUSED(f);
 
  return (0);
}

int             put(char **t, FILE *f, char *buff)
{
  UNUSED(t);
  UNUSED(f);
 
  return (0);
}

int             pwd(char **t, FILE *f, char *buff)
{
  UNUSED(t);
  UNUSED(f);
 
  return (0);
}
