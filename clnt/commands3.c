/*
** commands3.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:25:32 2015 
** Last update Sat Mar 28 04:58:39 2015 
*/

#include        "../include/defs.h"

int             pwd(char **t, FILE *f)
{
  UNUSED(t);
  UNUSED(f);
 
  return (0);
}

/* int             passv() */
/* { */
/* } */

int             send_port_cmd(FILE *f)
{
  int           ip[4];
  int           p;
  socklen_t     b_size;
  char          buffer[INET6_ADDRSTRLEN];
  struct sockaddr_in   s_in;

  b_size = sizeof(s_in);
  if ((getsockname(fileno(f), (struct sockaddr*) &s_in, &b_size)) == -1)
    return (1);
  inet_ntop(AF_INET, &s_in.sin_addr, buffer, INET6_ADDRSTRLEN);
  p = ntohs(s_in.sin_port);
  p++;
  sscanf(buffer, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
  fprintf(f, "PORT %d,%d,%d,%d,%d,%d\r\n", ip[0], ip[1], ip[2], ip[3], (p >> 8) & 0xff, p & 0xff);
  fflush(f);
  return (p);
}

int             active_data_connection(FILE *f, char flg, char *file)
{
  char          *buff;
  int           p;

  p = send_port_cmd(f);
  if (!fork())
    {
      listen_to_server(flg, file, p);
    }
  buff = malloc(1024);
  get_string(f, &buff, 1024, 1);
  return (0);
}
