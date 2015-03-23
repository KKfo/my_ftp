/*
** main.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 16:53:59 2015 
** Last update Sun Mar 22 16:56:22 2015 
*/

#include                "../include/defs.h"

char                    check_args(int ac, char *av, int *p)
{
    if (ac < 2 || !(*p = atoi(av)))
    {
      write(2, "usage ./server port\n", 20);
      return (1);
    }
    return (0);
}

char                    init_socket( struct protoent **s_p, int *fd)
{
  if (!(*s_p = getprotobyname("TCP")))
    {
      perror("socket");
      return (1);
    }
  if ((*fd = socket(AF_INET, SOCK_STREAM, (*s_p)->p_proto)) == -1)
    {
      perror("socket");
      return (1);
    }
  return (0);
}

void                    init_sin(struct sockaddr_in *s_in, int port)
{
  s_in->sin_family = AF_INET;
  s_in->sin_port = htons(port);
  s_in->sin_addr.s_addr = INADDR_ANY;
}

char                    do_bind(int sockfd,
                                const struct sockaddr* s_in,
                                socklen_t  size)
{
  if ((bind(sockfd, s_in, size)) == -1)
    {
      if ((close(sockfd)) == -1)
        {
          perror("close");
          return(1);
        }
      perror("bind");
      return(1);
    }
  return (0);  
}

char                    do_listen(int sockfd)
{
  if (listen(sockfd, 42) == -1)
    {
      if ((close(sockfd)) == -1)
        {
          perror("close");
          return(1);
        }
      perror("listen");
      return(1);
    }
  return (0);
}

char                    do_accept(int *c_fd,
                                  int fd,
                                  struct sockaddr* s_in_client,
                                  socklen_t *size)
{
   *c_fd = accept(fd, s_in_client, size);
   return(0);
}


int                     main(int argc, char **argv)
{
  t_vars                v;
  
  if ((check_args(argc, argv[1], &v.port)))
    return (EXIT_FAILURE);
  v.s_in_size = sizeof(v.s_in);
  init_sin(&v.s_in, v.port);
  if ((init_socket(&v.s_p, &v.sockfd))
      || do_bind(v.sockfd,
                 (const struct sockaddr*)&v.s_in,
                 v.s_in_size)
      || do_listen(v.sockfd))
    return (EXIT_FAILURE);
  process_clients(&v);
  /* wait(); */
  return (EXIT_SUCCESS);
}
