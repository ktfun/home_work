#include <stdio.h>
#include <math.h>

main()
{
    int x,y;
    int x0 = 12;
    int y0 = 10;
    int r = 10;

    for(y = y0 + r; y >= y0 -r; y--)
    {
        int m1 = 1 * (x0 - sqrt( r * r - (y - y0)*(y - y0) ));
        int m2 = 1 * (x0 + sqrt( r * r - (y - y0)*(y - y0) ));
        for( x = 0; x < m1; x++)
        {
            printf(" ");
        }
        printf("*");

        for(; x < m2; x++)
        {
            printf(" ");
        }
        printf("*\n");
    }
}
