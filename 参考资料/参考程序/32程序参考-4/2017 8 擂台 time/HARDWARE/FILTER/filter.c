#include "filter.h"

extern u16 juli[14];
extern u16 fir[10][14];

void filter(void)
{
	register u16 sum=0;
	u8 count=0,i=0,j=0;
	for(;i<14;i++)
	{
		while(j<10)
		{//865
			if(fir[j][i]<0){}
				else
			{
			sum+=fir[j][i];
					count++;
			}
		  j++;
		}
		juli[i]=sum/count;
		sum=0;count=0;j=0;
	}
}
