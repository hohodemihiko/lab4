#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void insertion(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bubble(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int flag = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = 1;
            }
        }
        if (!flag) break;
    }
}

void merge(int *arr, int *buf, int l, int r) {
    if (r - l <= 1) return;

    int m = (l + r) / 2;
    merge(arr, buf, l, m);
    merge(arr, buf, m, r);

    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (arr[i] <= arr[j]) {
            buf[k++] = arr[i++];
        } else {
            buf[k++] = arr[j++];
        }
    }
    while (i < m) buf[k++] = arr[i++];
    while (j < r) buf[k++] = arr[j++];

    for (i = l; i < r; i++) {
        arr[i] = buf[i];
    }
}

int main() {
    srand(time(NULL));
    int sizes[] = {10, 1000, 10000, 100000};
    double res[3];

    printf("Size\tBubble\t\tInsert\t\tMerge\n");

    for (int k = 0; k < 4; k++) {
        int n = sizes[k];
        int sz = n * sizeof(int);

        int *orig = (int *)malloc(sz);
        int *arr = (int *)malloc(sz);
        int *buf = (int *)malloc(sz);

        for (int i = 0; i < n; i++) {
            orig[i] = rand();
        }

        for (int m = 0; m < 3; m++) {
            memcpy(arr, orig, sz);
            clock_t start = clock();

            if (m == 0) {
                bubble(arr, n);
            } else if (m == 1) {
                insertion(arr, n);
            } else {
                merge(arr, buf, 0, n);
            }

            clock_t end = clock();
            res[m] = (double)(end - start) / CLOCKS_PER_SEC;
        }

        printf("%d\t%f\t%f\t%f\n", n, res[0], res[1], res[2]);

        free(orig);
        free(arr);
        free(buf);
    }

    return 0;
}
