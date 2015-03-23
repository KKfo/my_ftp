/*
** client.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 14:45:32 2015 
** Last update Mon Mar 23 14:33:53 2015 
*/

#include                "../include/defs.h"

int             get_string(int fd, char *buff, size_t l, char s)
{
  int           r;

  r = read(fd, buff, 1024);
  buff[r] = '\0';
  if (s)
    printf("server: %s", buff);
  bzero(&buff[l], 1024 - l);
  return(r);
}

int             user(char *user)
{
  FILE          *sock_stream;
  char          *pass;
  
  sock_stream = fdopen(fd, "r+");
  fprintf(str, "USER %s\n", user);
  fflush(str);
  get_string(fd, buffer, 3, 1);
  if (!strcmp(buffer, need_pass))
    {
      pass = getpass("(password): ");
      fprintf(str, "PASS %s\n", pass);
      fflush(str);
    }
  else if (!strcmp(buffer, user_logged_in))
    {
      printf("Client: user logged in\n");
      return(0);
    }
  get_string(fd, buffer, 3, 1);
  if (!strcmp(buffer, user_logged_in))
    {
      printf("Client: user logged in\n");
      return(0);
    }
  return (0);
}

int             auth(int fd)
{
  FILE          *str;
  char          *pass;
  int           r;
  char          buffer[1024];

  str = fdopen(fd, "r+");
  get_string(fd, buffer, 3, 1);
  if (!strcmp(buffer, connection_established))
    {
      printf("Connected succesfully\n");
      printf("username: ");
      fflush(stdout);
      r = get_string(0, buffer, 1024, 0);
      buffer[r] = '\0';
      fprintf(str, "USER %s\n", buffer);
      fflush(str);
      get_string(fd, buffer, 3, 1);
      if (!strcmp(buffer, need_pass))
        {
          pass = getpass("(password): ");
          fprintf(str, "PASS %s\n", pass);
          fflush(str);
        }
      else if (!strcmp(buffer, user_logged_in))
        printf("Client: user logged in\n");
      get_string(fd, buffer, 3, 1);
      if (!strcmp(buffer, user_logged_in))
        {
          printf("Client: user logged in\n");
        }
    }
  return (0);
}

char            execute_instr(char *buff)
{
  if (strcmp("quit", buff) == 0)
    return(1);
  return (0);
}

int             handle_commands(int fd)
{
  int           r;
  char          buff[1024];

  r = 1;
  auth(fd);
  bzero(buff, 1024);
  while(!execute_instr(buff) && r)
    {
      write(1, "ftp-> ", 6);
      r = read(0, buff, 1024);
      buff[r - 1] = '\0';
    }
  return (0);
}
