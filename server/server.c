/*
** server.c for my_ftp in /home/xxx/Epitech/2015/ocaml
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Fri Mar 13 17:02:03 2015 
** Last update Sun Mar 29 22:57:44 2015 
*/

#include                "../include/defs.h"

int                     handle_client(int fd)
{
  int                   i;
  int                   r;
  char                  buff[4096];
  char                  *welcome;
  char                  *code;
  char                  *cmds[3] = {"USER", "PASS\r\n", NULL};
  t_action              ptr_action[2] = {suser, pass};

  r = 1;
  i = 0;
  welcome = "220 Welcome to my_ftp server\r\n";
  if (write(fd, welcome, strlen(welcome)) == -1)
    return (1);
  while((r = read(fd, buff, 4096)))
    {
      buff[r] = '\0';
      code = strtok(buff, " ");
      while(cmds[i] && strcmp(cmds[i], code))
        i++;
      if (i < 2)
        {
          if (ptr_action[i](strtok(NULL, " "), fd) == EXIT_FAILURE)
            {
              return(EXIT_FAILURE);
            }
        }
      else
        printf("error:  %s comand not recognized\n", code);
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
