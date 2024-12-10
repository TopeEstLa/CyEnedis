#include <maths.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

int min(int a, int b) {
    return a < b ? a : b;
}

int min3(int a, int b, int c) {
    return min(a, min(b, c));
}