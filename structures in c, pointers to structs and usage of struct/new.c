#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
} X, y;
struct point makepoint(int x, int y);
struct point addpoint(struct point x, struct point y);
int          main() {
    struct point  p1 = {10, 5};
    struct point  p2 = {5, 10};
    struct point* x  = &p1;
    printf("address of p1 is %d",
                    x->y);  // -> sign used only for pointers to structs, actually the
                   // compiler automatically change the signs
    return 0;
}
struct point makepoint(int x, int y) {
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
};
struct point addpoint(struct point x, struct point y) {
    x.x += y.x;
    y.x += x.y;

    return x;
}