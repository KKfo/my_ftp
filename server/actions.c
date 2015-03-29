/*
** actions.c for my_ftp in /home/xxx/Epitech/2015/PSU_2014_myftp
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Sun Mar 29 22:28:58 2015 
** Last update Sun Mar 29 22:59:39 2015 
*/

#include                "../include/defs.h"

int             suser(char *user, int fd)
{
  char          *msg;

  UNUSED(user);
  msg = "331 Please specify the password\r\n";
  if (write(fd, msg, strlen(msg)) == -1)
    return (1);
  return (0);
}

int             pass(char *pass, int fd)
{
  char          *msg;

  UNUSED(pass);
  msg = "230 Login successful\r\n";
  if (write(fd, msg, strlen(msg)) == -1)
    return (1);
  return (0);
}
