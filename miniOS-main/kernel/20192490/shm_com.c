#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <sys/mman.h>

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int shm_com() {
  const int SIZE = 4096;
  const char * name = "OS";

  const char * message_0 = "Hello";
  const char * message_1 = "World!";

  int fd;
  char * ptr;
 
  pid_t pid;
 
  fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(fd, SIZE);
  ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  sprintf(ptr, "%s", message_0);
  ptr += strlen(message_0);
  sprintf(ptr, "%s", message_1);
  ptr += strlen(message_1);
  
  printf("입력값이 Shared memory에 저장되었습니다. \n");

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  } else if (pid == 0) {
    printf("Child process에서 Shared memory의 값을 읽어옵니다. \n");
    
    fd = shm_open(name, O_RDONLY, 0666);
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    printf("%s", (char *)ptr);
    sleep(2);
    
    shm_unlink(name);
  }	else {
    wait(NULL);
    printf("Shared memory test를 종료합니다. \n");
  }

  return 0;
}


