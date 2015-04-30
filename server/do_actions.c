/*
** server.c for my_ftp in /home/xxx/Epitech/2015/ocaml
** 
** Made by Adolfo Flores
** Login   <flores_a@epitech.eu>
** 
** Started on  Fri Mar 13 17:02:03 2015 
** Last update Fri Apr 17 12:17:39 2015 
*/

#include                "../include/defs.h"

int                     do_actions(int i, t_srv *v, int fd)
{
  char                  *message;
  t_action              ptr_action[9] = {suser, pass, port,
                                         list, syst, type,
                                         retr, stor, s_quit};

  if (i < 9)
    {
      if (ptr_action[i](v) == EXIT_FAILURE)
        {
          message = "451 Requested action aborted. Local error in processing.";
          if (write(fd, message, strlen(message)) == -1)
            return (1);
          free(v->tokens);
          return(EXIT_FAILURE);
        }
    }
  else
    {
      message = "502 Command not implemented.";
      if (write(fd, message, strlen(message)) == -1)
        return (1);
      printf("error: %s comand not recognized\n", v->tokens[0]);
    }
  return (0);
}
