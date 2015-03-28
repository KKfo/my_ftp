/*
** commands2.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:24:38 2015 
** Last update Sat Mar 28 04:50:51 2015 
*/

#include        "../include/defs.h"

int             quit(char **t, FILE *f)
{
  UNUSED(t);
  UNUSED(f);
  printf("Goodbye\n");
  return (1);
}

int             ls(char **t, FILE *f)
{
  /* int           passive; */

  /* passive = 0; */
  /* if(passive) */
  /*   send_passv_cmd(); */
  /* else */
    active_data_connection(f, 'l', NULL);
  if (t[1])
    {
      fprintf(f, "LIST %s\r\n", t[1]);
      fflush(f);
    }
  else
    {
      fprintf(f, "LIST\r\n");
      fflush(f);
    }
  return (0);
}

int             cd(char **t, FILE *f)
{
  UNUSED(t);
  UNUSED(f);
  return (0);
}

int             get(char **t, FILE *f)
{
  UNUSED(t);
  UNUSED(f);
 
  return (0);
}

int             put(char **t, FILE *f)
{
  UNUSED(t);
  UNUSED(f);
 
  return (0);
}
