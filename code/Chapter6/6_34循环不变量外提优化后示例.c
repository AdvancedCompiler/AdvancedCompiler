#include <stdio.h>
int main() {
    const int M = 256;
    const int N = 256;
    float U[M], W[M], D[M];
    float T1, T2;
    float dt = 5.0;
    for (int i = 1; i < N; i++) {
        U[i] = i;
        W[i] = i + 1;
        D[i] = i + 2;
    }
    T1 = 1 / (dt * dt);
    for (int i = 1; i < N; i++) {
        T2 = W[i];
        for (int j = 1; j < M; j++)
            U[i] = U[i] + T2 * D[j] * T1;
    }
    printf("%f", U[1]);
}