/*
** client.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 14:45:32 2015 
** Last update Sat Mar 28 17:02:26 2015 
*/

#include                "../include/defs.h"

int                     get_string(FILE *sock_stream, char **buff,
                                   size_t l, char s)
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

char            **tokenize(char *str, char **tab)
{
  int           i;

  i = 1;
  if (str == NULL || *str == '\n')
    return (NULL);
  while(*str == ' ' || *str == '\t')
    str++;
  tab[0] = str;
  while(*str)
    {
      if ((*str == ' ' || *str == '\t')
          && (*(str + 1) != ' '
              || *(str + 1) != '\t'))
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
  int           i;
  t_aptr        cmd_ptr[7] = {quit, auth, ls
                              , cd, get, put
                              , pwd};
  char          *cmds[8] = {"quit", "user",
                            "ls", "cd", "get",
                            "put", "pwd", NULL};

  i = 0;
  if (tab == NULL || *tab == NULL || **tab == '\0')
    return (0);
  while(cmds[i] && strcmp(cmds[i], tab[0]))
    i++;
  if (i != 7)
    {
      if (cmd_ptr[i](tab, sock_stream))
        {
          printf("error execute instr\n");
          return(1);
        }
    }
  else
    printf("-> error: command not found\n");
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
  if (!strcmp(buff, CON_ESTAB))
    {
      if (auth(NULL, sock_stream))
        printf("auth error\n");
    }
  while(!execute_instr(tab, sock_stream) && r)
    {
      write(1, "\x1B[92mmy_ftp-> \x1B[0m", 18);
      if ((r = get_string(stdin, &buff, 1024, 0)) == -1)
        {
          perror("get_line");
          return(1);
        }
      tab = tokenize(buff, mtab);
    }
  free(buff);
  free(mtab);
  return (0);
}
