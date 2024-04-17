#include <studio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define Buffer_SIZE 25
#define READ_END 0
#define WRITE_END 1

int create_process()
{
  char write_msg[Buffer_SIZE] = "Greetings";
  char read_msg[Buffer_SIZE] ;
  int fd[2], status;
  pid_t pid;
  if(pipe(fd)== -1){
      fprintf(stderr,"Pipe failed");
      return 1;
  }


  pid = fork();
  if(pid<0){
    fprintf(stderr, "fork Failed");
    return 1;
  }
  else if (pid > 0) {
    close(fd[READ_END]);
    write(fd[WRITE_END],wirte_msg,strlen(write_msg)+1);
    close(fd[WRITE_END]);
    wait(&status);
  }
  else{
    close(fd[WRITE_END]);
    read(fd[READ_END],read_msg,Buffer_SIZE);
    printf("read %s \n", read_msg);
    close(fd[READ_END]);
    exit(1);
  }
  return 0;

}
