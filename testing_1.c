#include<stdio.h>

// gcc testing_1.c -O3


int main()
{

    #include "variables.c"

    point_x[0] = 0x25386de449842abe;
    point_x[1] = 0x67e4d70f5dfc4db0;
    point_x[2] = 0x375a66a689b60453;
    point_x[3] = 0x0262a5ae34cd1547;

    point_y[0] = 0x695fa2615739b88f;
    point_y[1] = 0x7b76f2bf35a0bc43;
    point_y[2] = 0xa9cb20e1d17106d3;
    point_y[3] = 0xa0dd47ef503e34d5;

    
    
    #include "step_1.c"
    #include "step_2.c"
    #include "step_3.c"
    #include "step_4.c"
    #include "step_5.c"

    printf("%lx\n", point_y[0]);
    printf("%lx\n", point_y[1]);
    printf("%lx\n", point_y[2]);
    printf("%lx\n", point_y[3]);

    return 0;
}