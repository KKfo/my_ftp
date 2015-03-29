/*
** active_mode.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Fri Mar 27 23:43:08 2015 
** Last update Sat Mar 28  01:40:34 2015 
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
      return (1);
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
          return (1);
        }
      perror("listen");
      return (1);
    }
  return (0);
}

int                     accept_data(t_vars *v, char flg, FILE *f)
{
  char                  *b;

  if ((b = malloc(sizeof(char) * 1024)) == NULL)
    return (EXIT_FAILURE);
  get_string(f, &b, 3, 1);
  if (strcmp(b, OPEN_CONNECTION))
    {
      free(b);
      return (1);
    }
  free(b);
  v->server_fd = accept(v->sockfd, (struct sockaddr*)&v->s_in_client,
                        &v->s_in_size);
  v->client_ip = inet_ntoa(v->s_in_client.sin_addr);
  if (flg)
    {
      if (get_data(v, flg))
        {
          perror("get_data");
          if ((close(v->sockfd)) == -1 || (close(v->server_fd)) == -1)
            {
              perror("close");
              return (EXIT_FAILURE);
            }
          return (EXIT_FAILURE);
        }
    }
  else if (send_data(v))
    {
      if ((close(v->sockfd)) == -1 || (close(v->server_fd)) == -1)
        {
          perror("close");
          return (EXIT_FAILURE);
        }
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

int                     listen_to_server(char flg, char **args,
                                         int port, FILE *f)
{
  t_vars                v;

  memset(&v, 0, sizeof(v));
  v.args = args;
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
  if (accept_data(&v, flg, f))
    {
      return (1);
    }
  return (0);
}
