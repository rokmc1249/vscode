#define HAVE_STRUCT_TIMESPEC 
#include <time.h> // timespec 정의 포함
#include <sched.h> // sched_param 정의 포함
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<math.h>
#include <pthread.h>



// 전역 변수 및 뮤텍스 선언
int global_var; // 초기화되지 않은 전역 변수

pthread_mutex_t L1;
pthread_mutex_t L2;
pthread_mutex_t mutex;

// 함수 선언
void NonInitializedLocalVariable();
void NonInitializedPointer();
void OutOfBoundArrayIndex();
void Overflow();
void DivideByZero();
void SquareRootOfNegativeNumber();
void NonTerminationOfLoop();
void NonTerminationOfCall();
void UnreachableCode();
void MemoryLeak();
int* DoubleFree();
void NullPointerDereference();
void IllegalMemoryAccess();
void ImproperSynchronizationToSharedResource();
void Deadlock();
int* memory_alloc();
void misaligned_object();
void cast_alters_value(int num);
void missing_lock_acquisition();
void concurrency_lock_unknown();
void concurrency_starve_blocking(pthread_mutex_t lock);
void double_lock_unlock_twice_lock();

 //main 함수
int main() {
    
    int val = 7000000;
    cast_alters_value(val);
    NonInitializedLocalVariable();
    printf("젠kis");
   
    return 0;
}

void cast_alters_value(int num) {
    printf("short: %d\n", (short)(5 + num)); // cast_alters_value 유발 
}

void misaligned_object() {
    char* p = malloc(10);
    if (!p) {
        return;
    }
    free(p + 1);
}

void buffer_over_under() {

    char* arr[4];

    for (int i = 0; i <= 5; i++) { // 버퍼 언더 오버런 유발
        arr[i - 1] = i + 1;
    }

}

void NonInitializedLocalVariable() {
    int uninitialized_var; // Non-Initialized Local Variable
    //int err = result + uninitialized_var;
    printf("Uninitialized variable: %d\n", uninitialized_var);

    // 다음 함수 호출
    NonInitializedPointer();
}

void NonInitializedPointer() {
    int* ptr;
    *ptr = 5; // Non-Initialized Pointer 사용
    printf("Pointer value: %d\n", *ptr);

    // 다음 함수 호출
    OutOfBoundArrayIndex();
}

void OutOfBoundArrayIndex() {
    int arr[3] = { 1, 2, 3 };
    arr[5] = 10; // Out of bound array index
    printf("Array value: %d\n", arr[5]);

    // 다음 함수 호출
    DivideByZero();
}

void DivideByZero() {
    int divisor = 0;
    int result = 10 / divisor; // Divide by zero
    printf("Division Result: %d\n", result);

    // 다음 함수 호출
    SquareRootOfNegativeNumber();
}

void SquareRootOfNegativeNumber() {
    
    double value = -1.0;
    double result = sqrt(value); // Square root of negative number
    printf("Square Root: %f\n", result);

    NonTerminationOfLoop();
}

void NonTerminationOfLoop() {
    while (1) { // Non Termination of Loop
        printf("Infinite Loop\n");
        break; // 무한 루프 종료 테스트용
    }

    NonTerminationOfCall();
}

void NonTerminationOfCall() {
    UnreachableCode(); // 비종료 호출
    int* r_p;
    // 다음 함수 호출
    r_p = DoubleFree();
    free(r_p);
    
}

void UnreachableCode() {
    printf("This code is reachable\n");
    return;
    printf("Unreachable Code\n"); // 도달할 수 없는 코드
    
}

void MemoryLeak() {
    int* memory_leak_ptr = (int*)malloc(sizeof(int) * 10); // Memory Leak
    // 메모리 해제 없음

    NullPointerDereference();
}



void NullPointerDereference() {
    int* ptr = NULL;
    *ptr = 10; // Null Pointer Dereference

    ImproperSynchronizationToSharedResource();
}

void IllegalMemoryAccess() {
    int* ptr = (int*)malloc(sizeof(int) * 10);
    ptr[10] = 5; // Illegal Memory Access (배열 경계 초과)
    free(ptr);
    
}


void ImproperSynchronizationToSharedResource() {
    pthread_mutex_lock(&mutex);
    global_var++; // Improper Synchronization to Shared Resource
    pthread_mutex_unlock(&mutex);
    missing_lock_acquisition();

    
}

void missing_lock_acquisition() {
    pthread_mutex_unlock(&L2); // 잠금하는 부분 없음
    concurrency_lock_unknown();
    return;
}


void concurrency_lock_unknown() {
     pthread_mutex_lock(NULL);
     concurrency_starve_blocking(mutex);
}

void concurrency_starve_blocking(pthread_mutex_t lock) {
    
    pthread_mutex_lock(&lock); // 잠금


    // sleep 함수는 작업 기간을 지연시키기에 사용 자제
    //sleep(5); // 임계 영역 차단 유발  

    pthread_mutex_unlock(&lock); // 해제
    double_lock_unlock_twice_lock();
}


void double_lock_unlock_twice_lock() {

    pthread_mutex_lock(&L1);
    pthread_mutex_lock(&L1); // 동일한 뮤텍스 중복 잠금


    pthread_mutex_unlock(&L1);
    pthread_mutex_unlock(&L1); // 동일한 뮤텍스 중복 해제
    DoubleFree();
}


void Deadlock() {
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex); // Deadlock 발생 가능
    pthread_mutex_unlock(&mutex);

   

}
int* memory_alloc() {
    int* m_p = malloc(sizeof(int));
    if (m_p == NULL) {
        return NULL;
    }
    int* return_p = m_p;
    *return_p = 13;
    printf("return_p: %p, %d\n", return_p, *return_p);
    return(return_p);
}

int* DoubleFree(){
    int* px = malloc(sizeof(int));


    int* py = memory_alloc();

    int cd = 4;

    if (px == NULL || py == NULL) {

            if (px == NULL) { // px만 메모리 할당 안된 경우  
                free(py);
                return NULL;
            }
            else if (py == NULL) { // py만 메모리 할당 안된 경우  
                free(px);
                return NULL;
            }
            else { // 둘 다 할당 안된 경우  
                return NULL;
            }
    }

    *py *= cd;

    free(px);

    return(px);
}

