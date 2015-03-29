/*
** active_mode.c for my_ftp in /home/xxx
** 
** Made by 
** Login   <xxx@epitech.eu>
** 
** Started on  Wed Apr  1 22:49:10 2015 
** Last update Sat Mar 28  14:21:18 2015 
*/

#include                "../include/defs.h"


int                     write_localfile(FILE *stream, int srv)
{
  char                  buff[4096];
  int                   r;
  int                   fd;

  fd = fileno(stream);
  r = 0;
  while ((r = read(srv, buff, 4096)))
        write(fd, buff, r);
  return (0);
}

int                     get_from_client(char *file, int client_fd)
{
  FILE                 *fd;

  fd = fopen(file, "a");
  if (fd == NULL)
    {
      return (EXIT_FAILURE);
    }
  write_localfile(fd, client_fd);
  return (0);
}

int                     send_to_client(char *file, int client_fd)
{
  int                   r;
  char                  buff[4096];
  FILE                 *fd;

  if ((fd = fopen(file, "r")) == NULL)
    {
      perror("fopen");
      return (0);
    }
  while ((r = read(fileno(fd), buff, 4096)))
    write(client_fd, buff, r);
  fclose(fd);
  return (0);
}

int                     connect_to_client(struct sockaddr *s_in, int *sockfd)
{
  if (init_socket(sockfd))
    return (1);
  if (connect(*sockfd, s_in, sizeof(*s_in)) == -1)
    {
      perror("connect");
      return (1);
    }
  return (0);
}
