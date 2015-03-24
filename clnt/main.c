/*
** client/main.c for my_ftp in /home/xxx/Documents
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 22 17:01:56 2015 
** Last update Tue Mar 24 13:13:36 2015 
*/

#include                "../include/defs.h"

char                    check_args(int ac, char *av, int *p)
{
  if (!av)
    {
      write(2, "usage: ./client server-ip port\n", 31);
      return (1);
    }    
  *p = atoi(av);
  if (ac != 3 || !(*p))
    {
      write(2, "usage: ./client server-ip port\n", 31);
      return (1);
    }
  return (0);
}

char                    init_socket( struct protoent **s_p, int *fd)
{
  if (!(*s_p = getprotobyname("TCP")))
    {
      perror("getprotobyname");
      return (1);
    }
  if ((*fd = socket(AF_INET, SOCK_STREAM, (*s_p)->p_proto)) == -1)
    {
      perror("socket");
      return (1);
    }
  return (0);
}

void                    init_sin(struct sockaddr_in *s_in, int port, char *ip)
{
  s_in->sin_family = AF_INET;
  s_in->sin_port = htons(port);
  s_in->sin_addr.s_addr = inet_addr(ip);
}


int                     main(int argc, char **argv)
{
  struct sockaddr_in    s_in;
  struct protoent       *s_p;
  int                   port;
  int                   sockfd;

  if ((check_args(argc, argv[2], &port)))
    return (EXIT_FAILURE);
  init_sin(&s_in, port, argv[1]);
  if (init_socket(&s_p, &sockfd))
    return (EXIT_FAILURE);
  if(connect(sockfd, (struct sockaddr*)&s_in, sizeof(s_in)) == -1)
    {
      perror("connect");
      return(EXIT_FAILURE);  
    }
  printf("\n[\x1B[34mEpitech \x1B[0m\x1B[93mmy_ftp\x1B[0m 1.0]\n\nConnected to %s\n", argv[1]);
  if (handle_commands(sockfd))
    return(EXIT_FAILURE);
  if (close(sockfd) == -1)
    {
      perror("close");
      return(EXIT_FAILURE);
    }
    
  return (EXIT_SUCCESS);
}
