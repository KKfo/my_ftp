/*
** defs.h for my_ftp in /srv/http
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sat Mar 21 15:01:32 2015 
** Last update Sat Mar 28 04:40:00 2015 
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

#define                 CON_ESTAB "220"
#define                 LOGGED_IN "230"
#define                 bad_pass "332"
#define                 action_completed "250"
#define                 NEED_PASS "331"
#define                 NOT_L_IN "530"
#define                 UNUSED(x) (void)(x)

typedef int (*t_aptr)(char **, FILE *);
typedef int (*t_pt)(char **,FILE *);
typedef struct                  s_vars
{
  struct sockaddr_in            s_in;
  struct protoent               *s_p;
  int                           port;
  int                           sockfd;
  struct sockaddr_in            s_in_client;
  socklen_t                     s_in_size;
  int                           client_fd;
  int                           server_fd;
  char                          *file;
  char                          *client_ip;
}                               t_vars;

int                     listen_to_server(char flg, char *file, int port);
int                             need_password(char **buffer, FILE* sock_stream);
int                             logged_in(char **buffer, FILE* sock_stream);
int                             not_logged_in(char **buffer, FILE* sock_stream);
int                             get_string(FILE *sock_stream,
                                           char **buff, size_t l,
                                           char s);
int                             quit(char **, FILE *);
int                             user(char *, FILE *);
int                             ls(char **, FILE *);
int                             cd(char **, FILE *);
int                             get(char **, FILE *);
int                             put(char **, FILE *);
int                             pwd(char **, FILE *);
char                            init_socket(int *fd);
void                            init_sin(struct sockaddr_in *s_in,
                                         int port, char *ip);
int                             connect_to_server(struct sockaddr *s_in,
                                                  int *sockfd, int port, char *ip);
int                             auth(char **tab, FILE *sock_stream);
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
