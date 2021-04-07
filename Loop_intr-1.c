
//adapted  from Rulph chassing book
//NUCES FAST (Teacher: Munzir Ahmad)

#include "dsk6713_aic23.h"  			//support file for codec,DSK
Uint32 fs = DSK6713_AIC23_FREQ_8KHZ;//set sampling rate
short	loop = 0;         			  	//table index
short gain = 1;							//gain factor
short sine_table[8]={0,707,1000,707,0,-707,-1000,-707};//sine values

short cos_table[8]={1000,707,0,-707,-1000,-707,0,707};

short beta[8]={0,1,1,1,0,0,1,1};
short i[4]={1,0,-1,0};
short q[4]={0,1,0,-1};
int j = 0;
int k=0;
interrupt void c_int11()         //interrupt service routine
{
	if(beta[k]==0)
	{ if(beta[k+1]==0)
		{
		  j=0;
		}
		else if(beta[k+1]==1)
		{ 
		 j=1;
		}
	}

	else 
	 {
	  if(beta[k+1]==0)
		{
		  j=2;
		}
		else if(beta[k+1]==1)
		{ 
		 j=3;
		} 
	   
	 }
	
    output_sample((sine_table[loop]*q[j]) + (cos_table[loop]*i[j]));//output for on-time sec
    if (loop < 7) ++loop;   			//check for end of table
    else 
    {loop = 0;
    j++;
	k=k+2;
    }
	
    if(k>7)	{k=0;}	    			//reinit loop index
    return;
}

void main()
{
  comm_intr();                   //init DSK, codec, McBSP
  while(1);                	   //infinite loop
}

