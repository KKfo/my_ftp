/*
** active_mode.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Fri Mar 27 23:43:08 2015 
** Last update Sun Mar 29 00:03:07 2015 
*/

#include        "../include/defs.h"

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

int                     get_data(t_vars *v, char flg)
{
  size_t                r;
  char                  buff[2048];

  while (r = read(v->server_fd, buff, 2048))
    write(1, buff, r);
  return (0);
}

int                     send_data(t_vars *v)
{
  return (0);
}

int                     accept_data(t_vars *v, char flg)
{
  v->server_fd = accept(v->sockfd, (struct sockaddr*)&v->s_in_client,
                        &v->s_in_size);
  v->client_ip = inet_ntoa(v->s_in_client.sin_addr);
  printf("accepted connection from adress %s\n", v->client_ip);
  if (flg)
    {
      printf("get_data\n");
      if (get_data(v, flg))
        {
          perror("get_data");
          return (EXIT_FAILURE);
        }
    }
  else if (send_data(v))
    {
      perror("get_data");
      return (EXIT_FAILURE);
    }
  if ((close(v->sockfd)) == -1 || (close(v->server_fd)) == -1)
    {
      perror("close");
      return (EXIT_FAILURE);
    }
  return (0);
}

int                     listen_to_server(char flg, char *file, int port)
{
  t_vars                v;

  printf("listen to server"); /* test */
  memset(&v, 0, sizeof(v));
  v.file = file;
  v.s_in_size = sizeof(v.s_in);
  v.s_in.sin_family = AF_INET;
  v.s_in.sin_port = htons(port);
  v.s_in.sin_addr.s_addr = INADDR_ANY;
  if ((init_socket(&v.sockfd))
      || do_bind(v.sockfd,
                 (const struct sockaddr*)&v.s_in,
                 v.s_in_size)
      || do_listen(v.sockfd))
    return (EXIT_FAILURE);
  accept_data(&v, flg);
  return (0);
}
