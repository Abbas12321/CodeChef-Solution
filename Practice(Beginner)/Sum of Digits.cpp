#include <iostream>
using namespace std;

int main() {
    int T;
    
    scanf("%d", &T);
    while(T>0)
    {
        int x,sum=0;
         scanf("%d",  &x); 
         while(x>0)
         {
             int r=x %10;
             sum+=r;
             x/=10;
         
         }
         printf("%d\n",sum);
        T--;
    }
    
	// your code goes here
	return 0;
}
