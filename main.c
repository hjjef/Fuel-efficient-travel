//
//  main.c
//  travelefficiency(ideal)
//
//  Created by Henry Jeffers on 11/8/17.
//  Copyright © 2017 Henry Jeffers. All rights reserved.
//

/* Program to calculate the cheapest possible cost of fuel given the cost
 at each station and the fuel required (L) to get to the next station.
 Input the number of testcases, the number of stations before the destination,
 the cost at each station, and the ammount of litres to get to the next station
 or to get to the destination if at the last station.
 The program uses multidimensional arrays and dynamically allocates all memory.
 Input example:
 2
 5
 3 4 7 1 2
 1 4 6 3 9
 2
 5 1
 1 2
 Output:
 45
 7
 */


#include <stdio.h>
#include <stdlib.h>

void Sort_min_price(unsigned long* C, unsigned n, unsigned* min);

int main()
{
    unsigned testcases;
    scanf("%d", &testcases);
    
    unsigned* num_checkpoints = malloc(sizeof(unsigned)*testcases);
    unsigned long** C = malloc(sizeof(unsigned long*)*testcases);
    unsigned long** L = malloc(sizeof(unsigned long*)*testcases);
    
    unsigned i, j, k;
    for(i=0;i<testcases;i++)
    {
        scanf("%d", &num_checkpoints[i]);
        C[i] = malloc(sizeof(unsigned long)*num_checkpoints[i]);
        L[i] = malloc(sizeof(unsigned long)*num_checkpoints[i]);
        for(j=0;j<num_checkpoints[i];j++)
        {
            scanf("%ld", &C[i][j]);
        }
        for(j=0;j<num_checkpoints[i];j++)
        {
            scanf("%ld", &L[i][j]);
        }
    }
    
    unsigned* min_price = malloc(sizeof(unsigned)*testcases);
    double* price = malloc(sizeof(double)*testcases);
    for(i=0;i<testcases;i++)
    {
        price[i]=0;
        Sort_min_price(C[i], num_checkpoints[i], &min_price[i]);
    }
    for(k=0;k<testcases;k++)
    {
        for(i=0;i<num_checkpoints[k];i++)
        {
            if(C[k][i]==min_price[k])
            {
                for(j=i;j<num_checkpoints[k];j++)
                {
                    price[k] += C[k][i]*L[k][j];
                }
                break;
            }
            else
            {
                long litres_here=0;
                for(j=i;j<num_checkpoints[k];j++)
                {
                    if(C[k][i]<=C[k][j])
                    {
                        litres_here += L[k][j];
                    }
                    else
                    {
                        price[k] += litres_here*C[k][i];
                        i=j-1;
                        break;
                    }
                }
            }
        }
        printf("%.0f\n", price[k]);
    }
    for(i=0;i<testcases;i++)
    {
        free(C[i]);
        free(L[i]);
    }
    free (min_price);
    free (price);
    free (num_checkpoints);
    return 0;
}
void Sort_min_price(unsigned long* C, unsigned n, unsigned* min)
{
    *min = C[0];
    unsigned long i;
    for(i=0;i<n;i++)
    {
        if(*min>C[i])
        {
            *min = C[i];
        }
    }
}
