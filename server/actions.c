/*
** actions.c for my_ftp in /home/xxx/Epitech/2015/PSU_2014_myftp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 29 22:28:58 2015 
** Last update Thu Apr  2 11:55:22 2015 
*/

#include        "../include/defs.h"
#include        <sys/types.h>
#include        <sys/wait.h>

int             suser(t_srv *v)
{
  char          *msg;

  if (!strcmp(v->tokens[1], "anonymous")
      || !strcmp(v->tokens[1], "Anonymous"))
    msg = "331 Please specify the password\r\n";
  else
    msg = "530 This FTP server is anonymous only\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  return (0);
}

int             pass(t_srv *v)
{
  char          *msg;

  UNUSED(v);
  v->is_auth = 1;
  msg = "230 Login successful\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  return (0);
}

int             port(t_srv *v)
{
  unsigned char port[2];
  int           ip[4];
  char          ip_decimal[40];
  char          *msg;

  if (!v->is_auth)
    {
      msg = "530 Please login with USER and PASS.\r\n";
      if (write(v->fd, msg, strlen(msg)) == -1)
        return (1);
      return(0);
    }
  msg = "200 PORT command successful. Consider using PASV.\r\n";
  sscanf(v->tokens[1], "%d,%d,%d,%d,%d,%d",
         &ip[0],&ip[1],&ip[2],&ip[3],(int*)&port[0],
         (int*)&port[1]);
  sprintf(ip_decimal, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  if ((v->s_in.sin_addr.s_addr = inet_addr(ip_decimal)) == INADDR_NONE)
    {
      msg = "503 invalid ip adress\r\n";
      if (write(v->fd, msg, strlen(msg)) == -1)
        return (1);
      return(EXIT_FAILURE);
    }
  v->s_in.sin_family = AF_INET;
  v->s_in.sin_port = htons(port[0] * 256 + port[1]);
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  return (0);
}

int             syst(t_srv *v)
{
  char          *msg;

  UNUSED(v);
  if (!v->is_auth)
    {
      msg = "530 Please login with USER and PASS.\r\n";
      if (write(v->fd, msg, strlen(msg)) == -1)
        return (1);
      return(0);
    }
  msg = "215 UNIX Type: L8\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  return (0);

}

int                     list(t_srv *v)
{
  int                   status;
  int                   sock_fd;
  int                   tmp_fildes;
  char                  *msg;
  char                  *args[] = {"ls", "-l", NULL};

  if (!v->is_auth)
    {
      msg = "530 Please login with USER and PASS.\r\n";
      if (write(v->fd, msg, strlen(msg)) == -1)
        return (1);
      return(0);
    }
  if (connect_to_client((struct sockaddr *)&v->s_in, &sock_fd))
    return (EXIT_FAILURE);

  msg = "150 Here comes the directory listing.\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  tmp_fildes = dup(1);
  dup2(sock_fd, 1);
  if (!fork())
    {
      execvp("ls", args);
    }
  wait(&status);
  dup2(tmp_fildes, 1);
  msg = "226 Directory send OK.\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  if (close(sock_fd) == -1)
    {
      perror("close");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);  
}

int                     type(t_srv *v)
{
  char                  *msg;

  msg = "200 Switching to Binary mode.\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  return (0);
}

int                     retr(t_srv *v)
{
  int                   sock_fd;
  char                  *msg;

  if (!v->is_auth)
    {
      msg = "530 Please login with USER and PASS.\r\n";
      if (write(v->fd, msg, strlen(msg)) == -1)
        return (1);
      return(0);
    }
  if (connect_to_client((struct sockaddr *)&v->s_in, &sock_fd))
    return (EXIT_FAILURE);
  msg = "150 Opening BINARY mode data connection.\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  send_to_client(v->tokens[1], sock_fd);
  msg = "226 Transfer complete.\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  if (close(sock_fd) == -1)
    {
      perror("close");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);    
}

int                     stor(t_srv *v)
{
  int                   sock_fd;
  char                  *msg;

  if (!v->is_auth)
    {
      msg = "530 Please login with USER and PASS.\r\n";
      if (write(v->fd, msg, strlen(msg)) == -1)
        return (1);
      return(0);
    }
  if (connect_to_client((struct sockaddr *)&v->s_in, &sock_fd))
    return (EXIT_FAILURE);
  msg = "150 Opening BINARY mode data connection.\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  get_from_client(v->tokens[1], sock_fd);  
  msg = "226 Transfer complete.\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  if (close(sock_fd) == -1)
    {
      perror("close");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);      
}

int                     s_quit(t_srv *v)
{
  char                  *msg;

  UNUSED(v);
  msg = "221 Goodbye.\r\n";
  if (write(v->fd, msg, strlen(msg)) == -1)
    return (1);
  return (0);
}
