#include "my128.h"

void delay_ms(unsigned int m)   //10^-3  500이면 0.5초
{
    unsigned int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<2130;j++);
    }
}

void delay_us(unsigned int u)   //10^6   
{
    unsigned int i,j;

    for(i=0;i<u;i++)
    {
        for(j=0;j<2;j++);
    }
}
