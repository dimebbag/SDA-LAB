#include <stdio.h>
    #define N 7
int main(void) {
    float matrix[N][N];
    float target_x = 0.0f;

    printf("Vvedit shukane diisne chyslo X: ");
    if (scanf("%f", &target_x) != 1) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
        printf("Vvedit ryadok %d (%d chisel): ", i + 1, N);
        for (int j = 0; j < N; j++) {
            if (scanf("%f", &matrix[i][j]) != 1) {
                return 1;
            }
        }
    }

    printf("\nMatrytsya A[%d][%d]:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }

    int left = 0;
    int right = N - 1;
    int found_idx = -1;
    int steps = 0;
     while (left <= right) {
        steps++;
        int mid = left + (right - left) / 2;
        int r = (N - 1) - mid;
        int c = mid;

        if (matrix[r][c] >= target_x) {
            if (matrix[r][c] == target_x) {
                found_idx = mid;
            }
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("\nKilkist krokiv binary search: %d\n", steps);

    if (found_idx != -1) {
        int r = (N - 1) - found_idx;
        int c = found_idx;
        printf("Chyslo %.2f znaydeno na pobichniy diagonali.\n", target_x);
        printf("Koordynaty (ryadok, stovpets): (%d, %d)\n", r + 1, c + 1);
    } else {
        printf("Chyslo %.2f vidsutnye na pobichniy diagonali.\n", target_x);
    }

    return 0;
}