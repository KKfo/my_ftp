/*
** client/main.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 17:01:56 2015 
** Last update Sun Mar 29 22:53:31 2015 
*/

#include                "../include/defs.h"

char                    check_args(int ac, char *av, int *p)
{
  if (!av || ac != 3 || !(*p = atoi(av)))
    {
      if (write(2, "usage: ./client server-ip port\n", 31) == -1)
        perror("write");
      return (1);
    }
  return (0);
}

char                    init_socket(int *fd)
{
  struct protoent       *s_p;

  if (!(s_p = getprotobyname("TCP")))
    {
      perror("getprotobyname");
      return (1);
    }
  if ((*fd = socket(AF_INET, SOCK_STREAM, s_p->p_proto)) == -1)
    {
      perror("socket");
      return (1);
    }
  return (0);
}

int                     connect_to_server(struct sockaddr *s_in, int *sockfd,
                                          int port, char *ip)
{
  memset(s_in, 0, sizeof(*s_in));
  ((struct sockaddr_in*)s_in)->sin_family = AF_INET;
  ((struct sockaddr_in*)s_in)->sin_port = htons(port);
  ((struct sockaddr_in*)s_in)->sin_addr.s_addr = inet_addr(ip);
  if (init_socket(sockfd))
    return (1);
  if(connect(*sockfd, s_in, sizeof(*s_in)) == -1)
    {
      perror("connect");
      return (1);  
    }
  return (0);
}

int                     main(int argc, char **argv)
{
  struct sockaddr       s_in;
  int                   port;
  int                   cmd_sock_fd;

  if ((check_args(argc, argv[2], &port)))
    return (EXIT_FAILURE);
  if (connect_to_server(&s_in, &cmd_sock_fd,
                        port, argv[1]))
    return (EXIT_FAILURE);
  printf("\n[\x1B[34mEpitech \x1B[0m"
         "\x1B[93mmy_ftp\x1B[0m 1.0]"
         "\n\nConnected to %s\n", argv[1]);
  if (handle_commands(cmd_sock_fd))
    {
      return (EXIT_FAILURE);
    }
  if (close(cmd_sock_fd) == -1)
    {
      perror("close");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
