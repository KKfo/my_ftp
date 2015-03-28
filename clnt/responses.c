/*
** responses.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:49:40 2015 
** Last update Wed Mar 25 22:42:15 2015 
*/

#include        "../include/defs.h"

int             need_password(char **buffer, FILE* sock_stream)
{
  char          *pass;

  pass = getpass("(password): ");
  fprintf(sock_stream, "PASS %s\r\n", pass);
  fflush(sock_stream);
  get_string(sock_stream, buffer, 3, 1);
  if (!strcmp(*buffer, LOGGED_IN))
    {
      printf("client: user logged in\n");
    }
  return (1);
}

int     logged_in(char **buffer, FILE* sock_stream)
{
  UNUSED(sock_stream);
  UNUSED(buffer);
  printf("client: user logged in\n");
  return(0);
}

int     not_logged_in(char **buffer, FILE* sock_stream)
{
  UNUSED(buffer);
  UNUSED(sock_stream);
  printf("client: user could not log in\n");
  return(0);
}
