/*
** defs.h for my_ftp in /srv/http
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sat Mar 21 15:01:32 2015 
** Last update Mon Mar 23 13:46:19 2015 
*/

#ifndef                         DEFS_H_
# define                        DEFS_H_

#include                        <stdio.h>
#include                        <strings.h>
#include                        <string.h>
#include                        <sys/types.h>
#include                        <sys/socket.h>
#include                        <netinet/in.h>
#include                        <arpa/inet.h>
#include                        <time.h>
#include                        <errno.h>
#include                        <sys/socket.h>
#include                        <stdlib.h>
#include                        <netdb.h>
#include                        <netinet/in.h>
#include                        <unistd.h>

/* #define MAXSIZE                 512 */
/* #define ACK                     2 */
/* #define NACK                    3 */
/* #define REQUESTFILE             100 */
/* #define CMD_NOT_SUPPORTED       150 */
/* #define COMND_SUP               160 */
/* #define BADFILENAME             200 */
/* #define FILENAMEOK              400 */
/* #define STARTTRANSFER           500 */
/* #define CLIENT_PORT_ID          6086 */

#define                 connection_established "220"
#define                 user_logged_in "230"
#define                 bad_pass "332"
#define                 action_completed "250"
#define                 need_pass "331"

typedef struct                  s_vars
{
  struct sockaddr_in            s_in;
  struct protoent               *s_p;
  int                           port;
  int                           sockfd;
  struct sockaddr_in            s_in_client;
  socklen_t                     s_in_size;
  int                           client_fd;
  char                          *client_ip;
}                               t_vars;

int                             readn(int sd,char *ptr,int size);
int                             writen(int sd,char *ptr,int size);
int                             process_clients(t_vars *v);
int                             handle_client(int fd);
char                            do_accept(int *c_fd,
                                  int fd,
                                  struct sockaddr* s_in_client,
                                  socklen_t *size);
int                             handle_commands(int fd);
#endif
