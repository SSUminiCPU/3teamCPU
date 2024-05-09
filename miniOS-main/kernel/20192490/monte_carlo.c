#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define NUM_THREAD 6
#define NUM_POINT 500000

int points = 0;
int inner_points = 0; // 원 안에 찍힌 점 갯수

typedef struct
{
    double x;
    double y;
}POINT;

void * make_point(void * thread_num); // 스레딩 할 함수

double make_random_minus_one_to_one() {
    return((double)rand() / (double)RAND_MAX * 2.0 - 1.0);
}

// 원점이 중심인 반지름 1인 원이 있다고 할 때 좌표평면상에서 점의 거리 계산
double cal_distance(double x, double y) { 
    return (sqrt(pow(x-0,2) + pow(y-0,2)));
}

double cal_pi(int in, int all) {
    return (4 * ((double)in / (double)all));
}

int monte_carlo() {
    /*
    printf("%f \n", make_random_minus_one_to_one());
    printf("%f \n", make_random_minus_one_to_one());
    printf("%f \n", make_random_minus_one_to_one()); // 난수 발생 함수 작동 테스트
    printf("%f \n", cal_distance(3,4)); // 거리 계산 함수 테스트
    printf("%f \n", cal_pi(2, 4)); // Pi 계산 함수 테스트
    */

    srand(time(NULL));
    clock_t start = clock();

    pthread_t tid[NUM_THREAD];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    printf("Pi 값을 알아내기 위한, Monte Carlo 방법을 진행합니다. \n");
    
    for (int i=0; i<NUM_THREAD; i++) {
        pthread_create(&tid[i], &attr, make_point, i);
    }
    for (int i=0; i<NUM_THREAD; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf(" --- 모든 스레드 종료 --- \n");
    printf("총 점 개수 (%d), 원 안의 점 개수(%d), 원 밖의 점 개수(%d) \n", points, inner_points, points-inner_points);

    printf(" -> Pi = %f\n", cal_pi(inner_points, points));

    clock_t end = clock();
    printf("소요 시간(ms) : %lf \n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 전역변수 리셋
    points = 0;
    inner_points = 0;

    return 0;
}

void * make_point(void * thread_num) {
    POINT p;
    int all = 0;
    int in = 0;

    srand(time(NULL));
    printf("[ %d번 스레드 - 점 생성 중 ...] \n", thread_num+1);

    for (int i=0; i<NUM_POINT; i++) {
        p.x = make_random_minus_one_to_one();
        p.y = make_random_minus_one_to_one();

        if (cal_distance(p.x, p.y) <= 1) {
            inner_points++; // 전역변수
            in++; // 지역변수
        } 

        points++; // 전역변수
        all++; // 지역변수
    }
    printf(" [ %d번 스레드 - 종료 (찍은 점 개수-%d, 원 안에 찍힌 점 개수-%d) ] \n", thread_num+1, all, in);
    pthread_exit(0);
}