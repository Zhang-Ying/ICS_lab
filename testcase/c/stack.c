#include "../trap.h"

#define N 173
#define STACK_SIZ 200

int a[N] = {-2924, 99, 46, 1496, 1868, -2109, -2704, -1435, 640, 18, -1941, -2712, -1499, -1350, -2883, 1003, -1887, -2732, -1515, 1730, -2579, -45, 860, 267, -2914, 529, 900, -1803, -2642, -2149, -298, -99, -2572, -2009, -1488, 131, -1282, -925, 571, -2700, -976, -2379, -784, -651, 1608, 1205, 27, 1392, -2993, 146, 1251, -2957, -1439, -1164, -837, -1192, -65, -2272, 918, -1263, 1197, -2635, -47, -1443, -2299, -618, -1631, 1863, 872, 1704, 132, 1980, -2368, 1118, 1743, -432, -1911, -327, 418, -664, -1109, -2529, -860, -1409, -1421, -1478, -1833, 261, -1377, -278, 117, 1231, 657, -2048, 398, -2654, -1978, 1271, -30, -1186, -2938, 188, 1368, -2232, 769, -1640, -421, -595, 1124, 1834, -1032, 1249, -1189, 736, -292, 606, -2730, -1394, -126, -1815, -2735, -888, 1726, -1111, 1654, -2736, -2496, -1340, -1583, -2125, -2759, 331, -1062, 1034, -2845, -2890, 1069, -2336, -1187, 96, 1594, 1562, 93, -1079, -2496, -2439, 545, 264, -653, -2239, -2913, 1575, -1245, -2300, -1268, 1857, 1654, 1132, 1588, 1746, -1882, -297, 513, -2049, -2577, 997, -137, -169, -904, -1008, 791, -1922, -1330};

int ans[N] = {-1330, -1922, 791, -1008, -904, -169, -137, 997, -2577, -2049, 513, -297, -1882, 1746, 1588, 1132, 1654, 1857, -1268, -2300, -1245, 1575, -2913, -2239, -653, 264, 545, -2439, -2496, -1079, 93, 1562, 1594, 96, -1187, -2336, 1069, -2890, -2845, 1034, -1062, 331, -2759, -2125, -1583, -1340, -2496, -2736, 1654, -1111, 1726, -888, -2735, -1815, -126, -1394, -2730, 606, -292, 736, -1189, 1249, -1032, 1834, 1124, -595, -421, -1640, 769, -2232, 1368, 188, -2938, -1186, -30, 1271, -1978, -2654, 398, -2048, 657, 1231, 117, -278, -1377, 261, -1833, -1478, -1421, -1409, -860, -2529, -1109, -664, 418, -327, -1911, -432, 1743, 1118, -2368, 1980, 132, 1704, 872, 1863, -1631, -618, -2299, -1443, -47, -2635, 1197, -1263, 918, -2272, -65, -1192, -837, -1164, -1439, -2957, 1251, 146, -2993, 1392, 27, 1205, 1608, -651, -784, -2379, -976, -2700, 571, -925, -1282, 131, -1488, -2009, -2572, -99, -298, -2149, -2642, -1803, 900, 529, -2914, 267, 860, -45, -2579, 1730, -1515, -2732, -1887, 1003, -2883, -1350, -1499, -2712, -1941, 18, 640, -1435, -2704, -2109, 1868, 1496, 46, 99, -2924};

int top;
int stack_v[STACK_SIZ];

void stack_init()
{
    top = 0;
}

void push(int val)
{
    stack_v[top++] = val;
}

int pop()
{
    return stack_v[--top];
}

int main()
{
    stack_init();
    int x;
    int i;
    for (i = 0; i < N; i++) {
        push(a[i]);
    }
    for (i = 0; i < N; i++) {
        x = pop();
        nemu_assert(x = ans[i]);
    }

    HIT_GOOD_TRAP;

    return 0;
}