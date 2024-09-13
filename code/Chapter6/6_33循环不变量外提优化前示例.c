#include <stdio.h>
int main() {
    const int M = 256;
    const int N = 256;
    float U[M], W[M], D[M];
    float dt = 5.0;
    for (int i = 1; i < N; i++) {
        U[i] = i;
        W[i] = i + 1;
        D[i] = i + 2;
    }
    for (int i = 1; i < N; i++)
        for (int j = 1; j < M; j++)
            U[i] = U[i] + W[i] * D[j] / (dt * dt);
    printf("%f", U[1]);
}