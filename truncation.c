//to study the truncation phenomenon in devide
//and maybe the type casting
#include<stdio.h>
#include<cs50.h>

int main(void)
{
    //just input two number
    int n,m;
    do
    {
        n = get_int("the first number: ");
        m = get_int("the second number: ");
    }
    while(n < 0 || m < 0);
    float x = (float) n / (float) m;
    printf("%f\n",x);



}
 