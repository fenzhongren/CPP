#include "config.h"

#ifdef USE_MYMATH
#include "math/math_functions.h"
#else
#include <math.h>
#endif  //USE_MYMATH

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
#ifdef USE_MYMATH
#ifdef TEST
    printf("This is a test\n");
#endif  //TEST
    printf("Now we use our own Math library. \n");
    double result = power(base, exponent);
#else
    printf("Now we use the standard library. \n");
    double result = pow(base, exponent);
#endif  //USE_MYMATH
    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}