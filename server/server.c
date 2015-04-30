/*
** server.c for my_ftp in /home/xxx/Epitech/2015/ocaml
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Fri Mar 13 17:02:03 2015 
** Last update Fri Apr 17 16:16:21 2015 
*/

#include                "../include/defs.h"

void                    create_token(char *str, char ** const result)
{
  int                   i;

  i = 0;
  if (!str || !*str || *str == '\r')
    {
      if (str)
        *str = '\0';
      *result = NULL;
      return ;
    }
  UNUSED(i);
  result[0] = str;
  while((i < 1024) && str[i] && str[i] != ' '
        && str[i] != '\r' && str[i] != '\n')
    i++;
  if ((str[i] == ' ' || str[i] == '\r' || str[i] == '\n'))
    {
      str[i] = '\0';
      create_token(&str[i + 1], result + 1);
      return ;
    }
  else
    *result = NULL;
  return ;
}

int                     check_first_char(t_srv *v, int fd)
{
  char                  *message;

  if (v->tokens == NULL)
    {
      message = "502 Command not implemented.";
      if (write(fd, message, strlen(message)) == -1)
        return (EXIT_FAILURE);
      printf("error: comand empty\n");
      free(v->tokens);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int                     do_handle(char *buff, t_srv *v, int fd)
{
  int                   i;
  char                  *cmds[10] = {"USER", "PASS", "PORT",
                                    "LIST", "SYST", "TYPE",
                                    "RETR", "STOR", "QUIT",
                                    NULL};

  i = 0;
  create_token(buff, v->tokens);
  if (check_first_char(v, fd))
    return (EXIT_FAILURE);
  while (cmds[i] && strcmp(cmds[i], v->tokens[0]))
    i++;
  if (do_actions(i, v, fd))
    return (EXIT_FAILURE);
  return (0);
}

int                     handle_client(int fd)
{
  t_srv                 v;
  int                   r;
  char                  buff[4096];
  char                  *message;

  r = 1;
  memset(&v, 0, sizeof(v));
  v.fd = fd;
  if ((v.tokens = malloc(sizeof(char*) * 4096)) == NULL)
    {
      return (1);
    }
  message = "220 Welcome to my_ftp server\r\n";
  if (write(fd, message, strlen(message)) == -1)
    return (1);
  while((r = read(fd, buff, 4095)))
    {
      if (r > 4095)
        {
          printf("error\n");
          exit (1);
        }
        buff[r] = '\0';
      do_handle(buff, &v, fd);
    }
  free(v.tokens);
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
          printf("Client connected from adress: %s\n", v->client_ip);
          if (handle_client(v->client_fd))
            {
              if ((close(v->sockfd)) == -1 || (close(v->client_fd)) == -1)
                {
                  perror("close");
                  exit(EXIT_FAILURE);
                }
              perror("write");
              exit(EXIT_FAILURE);
            }
          if ((close(v->sockfd)) == -1 || (close(v->client_fd)) == -1)
            {
              perror("close");
              return(EXIT_FAILURE);
            }
          exit(EXIT_SUCCESS);
        }
    }
}
