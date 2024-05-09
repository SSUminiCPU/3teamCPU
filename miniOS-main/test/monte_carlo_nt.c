#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
}POINT;

double make_random_minus_one_to_one() {
    return((double)rand() / (double)RAND_MAX * 2.0 - 1.0);
}

double cal_distance(double x, double y) {
    return (sqrt(pow(x-0,2) + pow(y-0,2)));
}

double cal_pi(int in, int all) {
    return (4 * ((double)in / (double)all));
}

int main() {
    POINT p_r;
    int all_compare = 0;
    int in_compare = 0;

    srand(time(NULL));

    // 스레드 사용 안하고 점 3,000,000개를 생성할 때
    clock_t start_r = clock();
    printf("< 스레드 사용 안하고 점 3,000,000개를 찍으면? > \n");
    for (int j=0; j<3000000; j++) {
        p_r.x = make_random_minus_one_to_one();
        p_r.y = make_random_minus_one_to_one();

        if (cal_distance(p_r.x, p_r.y) <= 1) {
            in_compare++;
        } 
        all_compare++;
    }
    printf("총 점 개수 (%d), 원 안의 점 개수(%d), 원 밖의 점 개수(%d) \n", all_compare, in_compare, all_compare - in_compare);
    printf(" -> Pi = %f \n", cal_pi(in_compare, all_compare));

    clock_t end_r = clock();
    printf("소요 시간(ms) : %lf \n\n", (double)(end_r - start_r) / CLOCKS_PER_SEC);

    return 0;
}