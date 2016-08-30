#include<plib.h>
void main()
{
int n,a[10],i,b=0,c=1;
n=60;
   
    for(i=0;i<n;i++)
    {
        a[i]=n%16;
        n=n/16;
        b=b+(a[i]*c);
        c=c*10;
    }
}