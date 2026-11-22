#include <stdio.h>
#define M 7
#define N 7
static void print_matrix(int mat[M][N], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d", mat[i][j]);
        }
        printf("\n");
    }
}
int main(void) {
    int matrix[M][N];
    long long comparisons = 0;
    long long shifts = 0;
    for (int i = 0; i < M; i++) {
        printf("Vvedit ryadok %d (%d chisel): ", i + 1, N);
        for (int j = 0; j < N; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                return 1;
            }
        }
    }
    printf("\nPochatkova matrytsya A[%d][%d]:\n", M, N);
    print_matrix(matrix, M, N);
    for (int i = 0; i < M; i++) {
        for (int k = 1; k < N; k++) {
            int key = matrix[i][k];
            int j = k - 1;
            while (j >= 0) {
                comparisons++;
                if (matrix[i][j] < key) {
                    matrix[i][j + 1] = matrix[i][j];
                    shifts++;
                    j--;
                } else {
                    break;
                }
            }
            int barrier_pos = (j < 0) ? 0 : (j + 1);
            matrix[i][barrier_pos] = key;
        }
    }

    printf("-------------------------------------\n");
    printf("Vidsortovana matrytsya (za nezbilshuvannyam u kozhnomu ryadku):\n");
    print_matrix(matrix, M, N);

    printf("\nPorivnyan: %lld, Zsuviv elementiv: %lld\n", comparisons, shifts);

    return 0;
}