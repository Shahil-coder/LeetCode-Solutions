
#include <stdlib.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int *A = nums1, *B = nums2;
    int m = nums1Size, n = nums2Size;
    if (m > n) {
        int *t = A; A = B; B = t;
        int tmp = m; m = n; n = tmp;
    }
    int half = (m + n + 1) / 2;
    int lo = 0, hi = m;
    while (lo <= hi) {
        int i = (lo + hi) / 2;
        int j = half - i;
        int aL = (i > 0) ? A[i - 1] : INT_MIN;
        int aR = (i < m) ? A[i] : INT_MAX;
        int bL = (j > 0) ? B[j - 1] : INT_MIN;
        int bR = (j < n) ? B[j] : INT_MAX;
        if (aL <= bR && bL <= aR) {
            int leftMax = aL > bL ? aL : bL;
            if ((m + n) % 2) return (double)leftMax;
            int rightMin = aR < bR ? aR : bR;
            return (leftMax + rightMin) / 2.0;
        }
        if (aL > bR) hi = i - 1;
        else lo = i + 1;
    }
    return 0.0;
}