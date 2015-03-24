/*
** client.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 14:45:32 2015 
** Last update Tue Mar 24 14:05:08 2015 
*/

#include                "../include/defs.h"

int                     get_string(FILE *sock_stream, char **buff, size_t l, char s)
{
  size_t                n;
  ssize_t               r;

  n = 1024;
  r = 0;
  if ((r = getline(buff, &n, sock_stream)) == -1)
      return(-1);
  if (s)
    {
      if ((printf("server: %s", *buff)) < 0)
        return(-1);
      fflush(stdout);
      bzero(&(*buff)[l], r - l);
    }
  return(r);
}

int             user(char *user, FILE *sock_stream)
{
  char          *buffer;
  char          *pass;

  if ((buffer = malloc(sizeof(char) * 1024)) == NULL)
    return(1);
  fprintf(sock_stream, "USER %s\n", user);
  fflush(sock_stream);
  get_string(sock_stream, &buffer, 3, 1);
  if (!strcmp(buffer, need_pass))
    {
      pass = getpass("(password): ");
      fprintf(sock_stream, "PASS %s\n", pass);
      fflush(sock_stream);
    }
  else if (!strcmp(buffer, user_logged_in))
    {
      printf("client: user logged in\n");
      free(buffer);
      return(0);
    }
  else if (!strcmp(buffer, not_logged_in))
    {
      printf("client: user could not log in\n");
      free(buffer);
      return(0);
    }
  get_string(sock_stream, &buffer, 3, 1);
  if (!strcmp(buffer, user_logged_in))
    {
      printf("client: user logged in\n");
    }
  free(buffer);
  return (0);
}

int             auth(FILE *sock_stream)
{
  size_t        len;
  char          *cuser;

  cuser = NULL;
  printf("(username): ");
  fflush(stdout);
  if (getline(&cuser, &len, stdin) == -1)
    return(1);
  user(cuser, sock_stream);
  free(cuser);
  return (0);
}

char            **tokenize(char *str, char **tab)
{
  int           i;

  i = 1;
  while(*str == ' ' || *str == '\t')
    str++;
  tab[0] = str;
  while(*str)
    {
      if ((*str == ' ' || *str == '\t')
          && (*(str + 1) != ' ' || *(str + 1) != '\t'))
        {
          *str = '\0';
          tab[i] = ++str;
        }
      else
        str++;
      /* Add realloc routine */
    }
  *(str - 1) = '\0';
  return(tab);
}

char            execute_instr(char **tab, FILE *sock_stream)
{
  if (tab == NULL)
    return(0);
  if (strcmp("quit", tab[0]) == 0)
    return(1);
  if (strcmp("user", tab[0]) == 0)
    {
      if (tab[1] == NULL)
        auth(sock_stream);
      else
        user(tab[1], sock_stream);
    }
  if (strcmp("ls", tab[0]) == 0)
    {
    }
  if (strcmp("cd", tab[0]) == 0)
    {
    }
  if (strcmp("get", tab[0]) == 0)
    {
    }
  if (strcmp("put", tab[0]) == 0)
    {
    }
  if (strcmp("pwd", tab[0]) == 0)
    {
    }  
  bzero(tab, 1024);
  return (0);
}

int             handle_commands(int fd)
{
  ssize_t       r;
  char          *buff;
  char          **mtab = NULL;
  char          **tab;
  FILE          *sock_stream;

  r = 1;
  tab = NULL;
  if ((mtab = malloc(sizeof(char*) * 1024)) == NULL
      || (buff = malloc(sizeof(char) * 1024)) == NULL
      || (sock_stream = fdopen(fd, "r+")) == NULL
      || (get_string(sock_stream, &buff, 3, 1)) == -1)
    return(1);
  if (!strcmp(buff, connection_established))
    {
      if (auth(sock_stream))
        printf("auth error\n");
    }
  while(!execute_instr(tab, sock_stream) && r)
    {
      write(1, "\x1B[92mftp-> \x1B[0m", 15);
      if ((r = get_string(stdin, &buff, 1024, 0)) == -1)
        return(1);
      if ((tab = tokenize(buff, mtab)) == NULL)
        return(1);
    }
  free(buff);
  free(mtab);
  printf("Bye\n");
  return (0);
}
