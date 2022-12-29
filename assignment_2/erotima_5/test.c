#include <stdio.h>
#include <time.h>
int main()
{
    long tseed = time(0);
    printf("tseed = %ld  ", tseed);
    return 0;
}