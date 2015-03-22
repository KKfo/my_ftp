/*
** defs.h for my_ftp in /srv/http
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sat Mar 21 15:01:32 2015 
** Last update Sat Mar 21 20:46:08 2015 
*/

#ifndef                         DEFS_H_
# define                        DEFS_H_

#include                        <stdio.h>
#include                        <string.h>
#include                        <sys/types.h>
#include                        <sys/socket.h>
#include                        <netinet/in.h>
#include                        <arpa/inet.h>
#include                        <time.h>
#include                        <errno.h>
#define MAXSIZE                 512
#define ACK                     2
#define NACK                    3
#define REQUESTFILE             100
#define CMD_NOT_SUPPORTED       150
#define COMND_SUP               160
#define BADFILENAME             200
#define FILENAMEOK              400
#define STARTTRANSFER           500
#define CLIENT_PORT_ID          6086

int readn(int sd,char *ptr,int size);
int writen(int sd,char *ptr,int size);

#endif
