/*
** commands2.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:24:38 2015 
** Last update Sun Mar 29 23:01:47 2015 
*/

#include        "../include/defs.h"

int             ls(char **t, FILE *f, char *buff)
{
  int           r;
  int           p;

  if ((p = send_port_cmd(f, buff)) == -1)
    {
      return(0);
    }
  else if(p == EXIT_FAILURE)
    {
      return(EXIT_FAILURE);
    }
  if (t[1])
    {
      snprintf(buff, 1023, "LIST %s\r\n", t[1]);
      if ((r = write(fileno(f), buff, strlen(buff))) < 0)
        {
          perror("write");
          return(1);
        }
    }
  else
    {
      if ((r = write(fileno(f), "LIST \r\n", 7)) < 0)
        {
          perror("write");
          return(1);
        }
    }
  listen_to_server('l', NULL, p, f);
  get_string(f, &buff, 3, 1);
  return (0);
}

int             cd(char **t, FILE *f, char *buff)
{
  if (t[1])
    {
      snprintf(buff, 1023, "CWD %s\r\n", t[1]);
      if (write(fileno(f), buff, strlen(buff)) < 0)
        {
          perror("write");
          return(1);
        }
    }
  else
    {
      printf("usage: cd remote-directory\n");
      return (0);
    }
  get_string(f, &buff, 3, 1);
  return (0);
}

int             get(char **t, FILE *f, char *buff)
{
  int           p;

  write(fileno(f), "TYPE I\r\n", 8);
  get_string(f, &buff, 3, 0);
  if ((p = send_port_cmd(f, buff)) == -1)
    {
      return(0);
    }
  else if(p == EXIT_FAILURE)
    {
      return(EXIT_FAILURE);
    }
  if (t[1])
    {
      snprintf(buff, 1023, "RETR %s\r\n", t[1]);
      if (write(fileno(f), buff, strlen(buff)) < 0)
        {
          perror("write");
          return(1);
        }
    }
   else
    {
      printf("usage: get remote-directory\n");
      return (0);
    }
  if (listen_to_server('g', t, p, f))
    {
      return (0);
    }
  get_string(f, &buff, 3, 1);
  return (0);
}

int             put(char **t, FILE *f, char *buff)
{
  FILE          *fd;
  int           p;

  write(fileno(f), "TYPE I\r\n", 8);
  get_string(f, &buff, 3, 0);
  if ((p = send_port_cmd(f, buff)) == -1)
    {
      return(0);
    }
  else if(p == EXIT_FAILURE)
    {
      return(EXIT_FAILURE);
    }
  if (t[1])
    {
      printf("TEST : %s", t[1]);
      if ((fd = fopen(t[1], "r")) == NULL)
        {
          perror("fopen");
          return (0);
        }
      fclose(fd);
      if (t[2])
        snprintf(buff, 1023, "STOR %s\r\n", t[2]);
      else
        snprintf(buff, 1023, "STOR %s\r\n", t[1]);
      if (write(fileno(f), buff, strlen(buff)) < 0)
        {
          perror("write");
          return(1);
        }
    }
   else
    {
      printf("usage: put remote-directory\n");
      return (0);
    }
  if (listen_to_server(0, t, p, f))
    {
      return (0);
    }
  get_string(f, &buff, 3, 1);
  return (0);
}

int             pwd(char **t, FILE *f, char *buff)
{
  UNUSED(t);
  write(fileno(f), "PWD\r\n", 5);
  get_string(f, &buff, 3, 1);
  return (0);
}
