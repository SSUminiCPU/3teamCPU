#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESS 10
#define TIME_SLICE 2

typedef struct
{
    int arrival_time;   // 도착 시간
    int burst_time;     // 실행 시간
    int remaining_time; // 남은 실행 시간
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void round_robin(Process processes[], int n) {
    int time = 0;
    int remaining_processes = n;
    int execute_time;

    while (remaining_processes > 0) {
        for (int i=0; i<n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                execute_time = TIME_SLICE < processes[i].remaining_time ? TIME_SLICE : processes[i].remaining_time;
                processes[i].remaining_time -= execute_time;
                time += execute_time;

                if (processes[i].remaining_time == 0) {
                    remaining_processes--;
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                }
            }
        }
    }
}

void display_results(Process processes[], int n) {
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time \n");
    for (int i=0; i<n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d \n", i+1, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
}

int main() {
    Process processes[NUM_PROCESS];
    int n;

    printf("Round Robin 스케줄링할 프로세스의 개수를 입력하세요 (1~%d) : ", NUM_PROCESS);
    scanf("%d", &n);

    printf("===== 프로세스들의 arrival_time과 burst_time을 입력합니다. ===== \n");

    for (int i=0; i<n; i++) {
        printf("[ Process - P%d ] \n", i+1);
        printf("Arrival time : ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time : ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    round_robin(processes, n);
    display_results(processes, n);

    return 0;
}
