#include <stdio.h>

float Channel1 = 400;
float Channel2 = 500;

int main() {
    int arr[10][2]; // 2D array of size 5x2
    int i, j;

    // Filling the first column with 30
    for(i = 0; i < 5; i++) {
        arr[i][0] = Channel1;
    }

    // Filling the second column with 50
    for(i = 0; i < 5; i++) {
        arr[i][1] = Channel2;
    }

    // Printing the values of the 2D array
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 2; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}