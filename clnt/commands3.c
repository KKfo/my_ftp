/*
** commands3.c for my_ftp in /home/xxx/Epitech/2015/philosophes/tp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Wed Mar 25 20:25:32 2015 
** Last update Sun Mar 29 13:24:29 2015 
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
  char          mssg[1024];
  size_t        s;
  char          *get;
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
  srand(time(NULL));
  p -= rand() % 1000;
  sscanf(buffer, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
  snprintf(mssg, 1023, "PORT %d,%d,%d,%d,%d,%d\r\n", ip[0], ip[1], ip[2], ip[3], (p >> 8) & 0xff, p & 0xff);
  write(fileno(f), mssg, strlen(mssg));
  get = NULL;
  s = 0;
  getline(&get, &s, f);
  printf("%s\n", get);
  return (p);
}

int             active_data_connection(FILE *f, char flg, char *file)
{
  int           r;
  char          buff[1024];
  int           p;

  p = send_port_cmd(f);
  printf("%i\n", p);
  if (!fork())
    {
      printf("Hello from listen to server child\n");
      listen_to_server(flg, file, p);
      exit(1);
    }
  else
    {
      sleep(4);
      printf("send list command to server\n");
      /* while(1) */
      /*   { */
      if (r = write(fileno(f), "LIST \r\n", 7) < 0)
        {
          perror("fprintf");
          printf("error transmission");
        }
      printf("sent %i\n", r);
        /* } */
    }
  wait();
  return (0);
}
