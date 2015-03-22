/*
** server.c for my_ftp in /home/xxx/Epitech/2015/ocaml
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Fri Mar 13 17:02:03 2015 
** Last update Sun Mar 22 13:46:46 2015 
*/

#include                <sys/socket.h>
#include                <stdlib.h>
#include                <netdb.h>
#include                <netinet/in.h>
#include                <arpa/inet.h>
#include                <unistd.h>
#include                <string.h>

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

int                     handle_client(int fd, char const *ip, int sockfd)
{
  char buff[1024];
  char *message;

  message = "Welcome your ip is ";
  if (write(fd, message, strlen(message)) == -1
      || write(fd, ip, strlen(ip)) == -1
      || write(fd, "\n", 1) == -1)
    return (1);
  write(fd, "user:\n", 6);
  while(read(fd, buff, 1024))
    {
      printf("%s", buff);
    }
  return (0);
}

int                     main(int argc, char **argv)
{
  struct sockaddr_in    s_in;
  struct protoent       *s_p;
  int                   port;
  int                   sockfd;
  struct sockaddr_in    s_in_client;
  socklen_t             s_in_size;
  int                   client_fd;
  char                  *client_ip;

  if ((check_args(argc, argv[1], &port)))
    return (EXIT_FAILURE);
  s_in_size = sizeof(s_in);
  init_sin(&s_in, port);
  if ((init_socket(&s_p, &sockfd))
      || do_bind(sockfd,
                 (const struct sockaddr*)&s_in,
                 s_in_size)
      || do_listen(sockfd))
    return (EXIT_FAILURE);
  while(1)
    {
      do_accept(&client_fd, sockfd,
                (struct sockaddr*)&s_in_client,
                &s_in_size);
      if (!fork())
        {
          client_ip = inet_ntoa(s_in_client.sin_addr);
          if (handle_client(client_fd, client_ip, sockfd))
            {
              perror("write");
              return(EXIT_FAILURE);
            }
          if ((close(sockfd)) == -1 || (close(client_fd)) == -1)
            {
              perror("close");
              return(EXIT_FAILURE);
            }
          exit(0);
        }
    }
   wait();
  return (EXIT_SUCCESS);
}
