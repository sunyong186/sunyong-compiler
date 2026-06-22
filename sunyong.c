#include <stdio.h>

// sunyong 언어로 빌드된 외부 함수 프로토타입 선언
extern double average(double x, double y);

int main()
{
    // sunyong 언어로 만든 함수를 직접 호출하여 테스트
    double res = average(10.0, 20.0);
    printf("Result from sunyong language compiler: %f\n", res);
    return 0;
}