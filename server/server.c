/*
** server.c for my_ftp in /home/xxx/Epitech/2015/ocaml
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Fri Mar 13 17:02:03 2015 
** Last update Mon Mar 23 12:44:55 2015 
*/

#include                "../include/defs.h"

int                     handle_client(int fd/* , int sockfd */)
{
  int r;
  char buff[1024];

  if (write(fd, connection_established, 4) == -1)
    return (1);
  while((strcmp(buff, "")))
    {
      r = read(fd, buff, 1024);
      buff[r] = '\0';
      printf("%s", buff);
      write(fd, need_pass, 4);
    }
  return (0);
}

int                     process_clients(t_vars *v)
{
    while(1)
    {
      do_accept(&v->client_fd, v->sockfd,
                (struct sockaddr*)&v->s_in_client,
                &v->s_in_size);
      if (!fork())
        {
          v->client_ip = inet_ntoa(v->s_in_client.sin_addr);
          if (handle_client(v->client_fd))
            {
              perror("write");
              return(EXIT_FAILURE);
            }
          if ((close(v->sockfd)) == -1 || (close(v->client_fd)) == -1)
            {
              perror("close");
              return(EXIT_FAILURE);
            }
          exit(0);
        }
    }
}
