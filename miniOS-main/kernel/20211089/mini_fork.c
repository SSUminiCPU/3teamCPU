#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int mini_fork() {
  pid_t pid;

  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  }

  else if (pid == 0) {
    printf("Child process is running \n");
    // execlp("/bin/ls", "ls", NULL);
    execl("/home/hyunwoo/miniOS/kernel/20192490/print_os_name", "print_os_name", NULL);
    perror("execl is failed! \n");     

    printf("Maybe, This won't show \n");
  }

  else {
    wait(NULL);
    printf("Child complete \n");
  }

  return 0;
}
