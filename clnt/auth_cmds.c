/*
** commands.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:10:54 2015 
** Last update Sun Mar 29 23:08:04 2015 
*/

#include        "../include/defs.h"

int     connection_established(char **buffer, FILE* sock_stream)
{
  UNUSED(buffer);
  UNUSED(sock_stream);
  printf("connest : Cool!\n");
  return(0);
}

int             user(char *user, FILE *sock_stream, char *buffer)
{
  int           i;
  char          *responses[5] = {NEED_PASS, LOGGED_IN
                                 , NOT_L_IN, CON_ESTAB,
                                 NULL};
  t_pt          action[4] = {need_password, logged_in
                             , not_logged_in, connection_established};

  i = 0;
  fprintf(sock_stream, "USER %s\r\n", user);
  fflush(sock_stream);
  snprintf(buffer, 10, "220");
  while (!strcmp(buffer, CON_ESTAB))
    get_string(sock_stream, &buffer, 3, 1);
  while (i < 4 && strcmp(buffer, responses[i]))
    i++;
  if (i != 4)
    if (action[i](&buffer, sock_stream))
      {
        return(1);
      }
  return (0);
}

int             auth(char **tab, FILE *sock_stream, char* buffer)
{
  int           r;
  size_t        len;
  char          *cuser;

  cuser = NULL;
  if (tab == NULL || tab[1] == NULL)
    {
      printf("(username): ");
      fflush(stdout);
      if ((r = getline(&cuser, &len, stdin)) == -1)
        return(1);
      cuser[r - 1] = '\0';
      user(cuser, sock_stream, buffer);
      free(cuser);
    }
  else
    user(tab[1], sock_stream, buffer);
  return (0);
}
