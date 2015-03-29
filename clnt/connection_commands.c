/*
** commands3.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:25:32 2015 
** Last update Sat Mar 28  01:14:23 2015 
*/

#include                "../include/defs.h"

int                     send_port_cmd(FILE *f, char *b)
{
  char                  mssg[1024];
  int                   ip[4];
  int                   p;
  socklen_t             b_size;
  char                  buffer[INET6_ADDRSTRLEN];
  struct sockaddr_in    s_in;

  b_size = sizeof(s_in);
  if ((getsockname(fileno(f), (struct sockaddr*) &s_in,
                   &b_size)) == -1)
    return (EXIT_FAILURE);
  inet_ntop(AF_INET, &s_in.sin_addr, buffer, INET6_ADDRSTRLEN);
  p = ntohs(s_in.sin_port);
  srand(time(NULL));
  p -= rand() % 1000;
  sscanf(buffer, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
  snprintf(mssg, 1023, "PORT %d,%d,%d,%d,%d,%d\r\n",
           ip[0], ip[1], ip[2], ip[3], (p >> 8) & 0xff, p & 0xff);
  write(fileno(f), mssg, strlen(mssg));
  get_string(f, &b, 3, 1);
  if (strcmp(b, SUCCESS))
    return (-1);
  return (p);
}
