/*
** client.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 14:45:32 2015 
** Last update Mon Mar 23 12:39:34 2015 
*/

#include                "../include/defs.h"

int             get_string(int fd, char *buff, size_t l)
{
  int           r;

  r = read(fd, buff, l);
  buff[r] = '\0';
  return(r);
}

char            *getpass(const char *prompt);
int             auth(int fd)
{
  char          *pass;
  int           r;
  char          buffer[1024];

  get_string(fd, buffer, 4);
  if (!strcmp(buffer, connection_established))
    {
      printf("Connected succesfully\n");
    }
  printf("username: ");
  fflush(stdout);
  r = get_string(0, buffer, 1024);
  write(fd, "USER ", 5);
  write(fd, buffer, r);
  get_string(fd, buffer, 4);
  if (!strcmp(buffer, need_pass))
    {
      pass = getpass("(password): ");
      write(fd, pass, strlen(pass));
      write(fd, "\n", 1);
    }
  else if (!strcmp(buffer, user_logged_in))
    printf("User logged in\n");
  get_string(fd, buffer, 4);
  if (!strcmp(buffer, user_logged_in))
    {
      printf("User logged in\n");
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
      r = read(0, buff, 1024);
      buff[r - 1] = '\0';
    }
  return (0);
}
