/*
** client.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 14:45:32 2015 
** Last update Mon Mar 23 15:29:39 2015 
*/

#include                "../include/defs.h"

int             get_string(int fd, char *buff, size_t l, char s)
{
  int           r;

  r = read(fd, buff, 1024);
  buff[r] = '\0';
  if (s)
    {
      printf("server: %s", buff);
      fflush(stdout);
    }
  bzero(&buff[l], 1024 - l);
  return(r);
}

int             user(char *user, int fd)
{
  char          buffer[1024];
  FILE          *sock_stream;
  char          *pass;
  
  sock_stream = fdopen(fd, "r+");
  fprintf(sock_stream, "USER %s\n", user);
  fflush(sock_stream);
  get_string(fd, buffer, 3, 1);
  if (!strcmp(buffer, need_pass))
    {
      pass = getpass("(password): ");
      fprintf(sock_stream, "PASS %s\n", pass);
      fflush(sock_stream);
    }
  else if (!strcmp(buffer, user_logged_in))
    {
      printf("client: user logged in\n");
      return(0);
    }
  else if (!strcmp(buffer, not_logged_in))
    {
      printf("client: user could not logged in\n");
      return(0);
    }
  get_string(fd, buffer, 3, 1);
  if (!strcmp(buffer, user_logged_in))
    {
      printf("client: user logged in\n");
    }
  return (0);
}

int             auth(int fd)
{
  int           r;
  char          buffer[1024];

  printf("(username): ");
  fflush(stdout);
  r = get_string(0, buffer, 1024, 0);
  buffer[r] = '\0';
  user(buffer, fd);
  return (0);
}

char            execute_instr(char *buff, int fd)
{
  if (strcmp("quit", buff) == 0)
    return(1);
  if (strncmp("user", buff, 4) == 0)
    {
      if (strcmp("user", buff) == 0)
        auth(fd);
      else
        user(&buff[5], fd);
    }
  return (0);
}

int             handle_commands(int fd)
{
  int           r;
  char          buff[1024];

  r = 1;
  get_string(fd, buff, 3, 1);
  if (!strcmp(buff, connection_established))
    {
      printf("Connected succesfully\n");
      auth(fd);
    }
  bzero(buff, 1024);
  while(!execute_instr(buff, fd) && r)
    {
      write(1, "ftp-> ", 6);
      r = read(0, buff, 1024);
      buff[r - 1] = '\0';
    }
  return (0);
}
