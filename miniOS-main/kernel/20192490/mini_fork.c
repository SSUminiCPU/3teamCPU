#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int mini_fork() {
  pid_t pid;

  int child_pid; // child process의 PID값
  int status;
  int ret;

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  }

  else if (pid == 0) {
    printf("Child process is running \n");
    printf("[ This process's PID is %d ] \n\n", getpid());
    // execlp("/bin/ls", "ls", NULL);
    execl("/home/hyunwoo-kim/miniOS/kernel/20192490/print_os_name", "print_os_name", NULL);
    perror("execl is failed! \n");
  }

  else {
    child_pid = wait(&status);
    
    printf("\nParents PID (%d), Child PID (%d) \n", getpid(), child_pid);
    ret = WIFEXITED(status);
    if (ret != 0) {
      printf("Child process is normally terminated! \n");
    } else {
      printf("Child process is abnormally terminated! \n");
    }
  }

  return 0;
}
