//O width buildings have been allowed

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCALE 1000 

typedef struct building
{
  double l;
  double r;
  double h;
}building;

typedef struct skyline
{
	double x;
	double h;

}skyline;

int MAX_HEIGHT;

void form_buildings(double xl, double xr, int no_buildings, building B[]);
void get_skyline(building *A, skyline *S, int n, int *counter);
void merge_skyline(skyline *A, skyline *B, skyline *C, int m, int n, int *counter);
double max_h(double a, double b);
void print_building(building *A, int n);
void print_skyline(skyline *S, int counter);

int main()
{
  int no_buildings,i,counter;
  double xl,xr,max;
  building *B;
  skyline *S;

  printf("\n\n");
  printf("Enter the left most x-coordinate: " );
  scanf("%lf", &xl);
  printf("Enter the right most x-coordinate: " );
  scanf("%lf", &xr);
  printf("Enter number of buildings: ");
  scanf("%d", &no_buildings);
  printf("Enter the maximum height of the buildings: ");
  scanf("%lf", &max);
  MAX_HEIGHT = max * 1000;

  B = (building *)malloc(no_buildings*sizeof(building));
  S = (skyline *)malloc((2*no_buildings)*sizeof(skyline));

  form_buildings(xl,xr,no_buildings,B);
  get_skyline(B,S,no_buildings,&counter);

  printf("\n\n");
  print_building(B,no_buildings);
  printf("\n\n");
  print_skyline(S,counter);
  printf("\n\n");

  return 0;
}

void form_buildings(double xl, double xr, int n, building B[])
{
  int i;
  int width = (xr - xl)*SCALE;
  int temp;

  srand(time(NULL));

  B[0].l = xl;
  B[0].r = xl + (rand()% width)*1.0/SCALE;
  B[0].h = (rand()%MAX_HEIGHT*1.0)/SCALE;
  B[--n].l = xl + (rand()% width)*1.0/SCALE;
  B[n].r = xr;
  B[n].h = (rand()%MAX_HEIGHT*1.0)/SCALE;
  
  for(i=1;i<n;i++)
  {
    B[i].l = xl + (rand()% width)*1.0/SCALE;
    temp = (xr - B[i].l)*SCALE;
    B[i].r = B[i].l + (rand()%temp)*1.0/SCALE;
    B[i].h = (rand()%MAX_HEIGHT*1.0)/SCALE;
  }

  return;
}

void get_skyline(building *A, skyline *S, int n, int *counter)
{
  	int i,counter1,counter2;
  	skyline *P, *Q;

  	if(n==1)
  	{
  		S[0].x = A[0].l;
  		S[0].h = A[0].h;

  		S[1].x = A[0].r;
  		S[1].h = 0;

  		*counter = 2;

    	return ;
  	}

  	i = n/2;

  	P = (skyline *)malloc((2*i)*sizeof(skyline));
  	Q = (skyline *)malloc(2*(n-i)*sizeof(skyline));

  	get_skyline(A,P,i,&counter1);
  	get_skyline(A+i,Q,n-i,&counter2);
  	merge_skyline(P,Q,S,counter1,counter2,counter);

	return;
}

void merge_skyline(skyline *A, skyline *B, skyline *C, int m, int n, int *counter)
{
  int i=0;
  int j=0;
  int k=0;
  double h1 = 0;
  double h2 = 0;

  while((i<m)&&(j<n))
  {
  	if(A[i].x<B[j].x)
    {
    	h1 = A[i].h;
    	A[i].h = max_h(A[i].h,h2);
    	
    	if((k>0) && (A[i].h == C[k-1].h))
    	{
    		i++;
    		continue;
    	}
    	else
    	{
    		C[k++] = A[i++];
    	}      
    }	
    else if(A[i].x == B[j].x)
    {

      	if(A[i].h > B[j].h)
      	{
      		h1 = A[i].h;
      		A[i].h = max_h(A[i].h,h2);
      		h2 = B[j].h;

    		if((A[i].h == C[k-1].h)&&(k>0))
    		{
    			i++;
    			j++;
    			continue;
    		}
    		else
    		{
    			C[k++] = A[i++];
    			j++;
    		}
      	}
      	else
      	{
      		h2 = B[j].h;
      		B[j].h = max_h(B[j].h,h1);
      		h1 = A[i].h;

    		if((k>0)&&(B[j].h == C[k-1].h))
    		{
    			i++;
    			j++;
    			continue;
    		}
    		else
    		{
    			C[k++] = B[j++];
    			i++;
    		}
      	}
    }
    else
    {
      	h2 = B[j].h;
    	B[j].h = max_h(B[j].h,h1);

    	if((k>0) && (B[j].h == C[k-1].h))
    	{
    		j++;
    		continue;
    	}
    	else
    	{
    		C[k++] = B[j++];
    	}      
    }
  }

  while(i<m)
  {
    h1 = A[i].h;
   	A[i].h = max_h(A[i].h,h2);

   	if(A[i].h == C[k-1].h)
   	{
  		i++;
    	continue;
    }
   	else
    {
    	C[k++] = A[i++];
    }      
  }
  while(j<n)
  {
    h2 = B[j].h;
   	B[j].h = max_h(B[j].h,h1);

   	if(B[j].h == C[k-1].h)
   	{
  		j++;
    	continue;
    }
   	else
    {
    	C[k++] = B[j++];
    }      
  }

  *counter = k;
  return;
}

double max_h(double a, double b)
{
	return (a > b) ? a : b;
}

void print_building(building *A, int n)
{
	int i;

	printf("Printing building points. Format: (l,r,h)\n");
	printf("l: left wall, r: right wall, h: height\n");

	for(i=0;i<n;i++)
	{
		printf("%d: (%lf,%lf,%lf)\n",i+1,A[i].l,A[i].r,A[i].h);
	}
}

void print_skyline(skyline *S, int counter)
{
	int i;

	printf("Printing Skyline\n");
	printf("Please note that only the start of horizontal lines have been mentioned.\n");
	printf("Suppose two points consecutive points are (x1,h1) and (x2,h2) respectively, then to get the contour go from x1 to x2 along h1 and then from h1 to h2 along x2.\n");
	
	for(i=0;i<counter;i++)
	{
		printf("%d: (%lf,%lf)\n",i+1,S[i].x,S[i].h);
	}
	return;	
}
