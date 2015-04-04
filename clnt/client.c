/*
** client.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 14:45:32 2015 
** Last update Thu Apr  2 14:01:42 2015 
*/

#include	"../include/defs.h"


int		quit(char **t, FILE *f, char *buff)
{
  size_t	s;
  char		*get;

  UNUSED(t);
  UNUSED(buff);
  get = NULL;
  s = 0;
  write(fileno(f), "QUIT\r\n", 6);
  getline(&get, &s, f);
  printf("%s", get);
  return (1);
}

int		get_string(FILE *sock_stream, char **buff,
                                   size_t l, char s)
{
  size_t	n;
  ssize_t	r;

  n = 1023;
  r = 0;
  if ((r = getline(buff, &n, sock_stream)) == -1)
      return (-1);
  if (s)
    {
      if ((printf("server: %s", *buff)) < 0)
        return(-1);
      fflush(stdout);
      bzero(&(*buff)[l], r - l);
    }
  return (r);
}

char		**tokenize(char *str, char **tab)
{
  int		i;

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
              && *(str + 1) != '\t'))
        {
          *str = '\0';
          tab[i] = ++str;
          ++i;
        }
      else
        str++;
    }
  *(str - 1) = '\0';
  tab[i] = NULL;
  return (tab);
}

int		execute_instr(char **tab, FILE *sock_stream, char *buff)
{
  int		r;
  int		i;
  t_aptr	cmd_ptr[7] = {quit, auth, ls
                              , cd, get, put
                              , pwd};
  char		*cmds[8] = {"quit", "user",
                            "ls", "cd", "get",
                            "put", "pwd", NULL};

  i = 0;
  if (tab == NULL || *tab == NULL || **tab == '\0')
    return (0);
  while (cmds[i] && strcmp(cmds[i], tab[0]))
    i++;
  if (i != 7)
    {
      if ((r = cmd_ptr[i](tab, sock_stream, buff)) == EXIT_FAILURE)
        {
          return (EXIT_FAILURE);
        }
    }
  else
    printf("-> error: command not found\n");
  bzero(tab, 1024);
  return (EXIT_SUCCESS);
}

int		handle_commands(int fd)
{
  char          *input;
  ssize_t       r;
  char          *buff;
  char          **mtab = NULL;
  char          **tab;
  FILE          *sock_stream;

  r = 1;
  tab = NULL;
  if ((mtab = malloc(sizeof(char*) * 1024)) == NULL
      || (buff = malloc(sizeof(char) * 1024)) == NULL
      || (input = malloc(sizeof(char) * 1024)) == NULL
      || (sock_stream = fdopen(fd, "r+")) == NULL
      || (get_string(sock_stream, &buff, 3, 1)) == -1)
    return(1);
  if (!strcmp(buff, CON_ESTAB))
    {
      if (auth(NULL, sock_stream, buff))
        printf("auth error\n");
    }
  while (!execute_instr(tab, sock_stream, buff) && r)
    {
      write(1, "\x1B[92mmy_ftp-> \x1B[0m", 18);
      if ((r = get_string(stdin, &input, 1024, 0)) == -1)
        {
          free(buff);
          free(mtab);
          free(input);
          perror("get_line");
          return (EXIT_FAILURE);
        }
      tab = tokenize(input, mtab);
    }
  free(buff);
  free(mtab);
  free(input);
  return (EXIT_SUCCESS);
}
