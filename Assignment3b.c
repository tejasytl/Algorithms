//O width buildings have been allowed

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCALE 1000 
#define INFINITY 1000000

typedef struct building
{
  double x1;
  double y1;
  double x2;
  double y2;
}building;

typedef struct skyline
{
	double x;
	double h;
	double m;
}skyline;

int MAX_HEIGHT;

void form_buildings(double xl, double xr, int no_buildings, building B[]);
void get_skyline(building *A, skyline *S, int n, int *counter);
double get_slope(double x1, double y1, double x2, double y2);
void merge_skyline(skyline *A, skyline *B, skyline *C, int m, int n, int *counter);
double max_h(double a, double b);
void print_building(building *A, int n);
void print_skyline(skyline *S, int counter);
int do_intersect(skyline a, skyline b, double *xin, double *yin, double x1, double x2);

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

  	S = (skyline *)malloc((4*no_buildings)*sizeof(skyline));

/* 	B[0].x1 = 0;
  	B[0].y1 = 0.305;
  	B[0].x2 = 1.782;
  	B[0].y2 = 0.405;

  	B[1].x1 = 1.221;
  	B[1].y1 = 3.864;
  	B[1].x2 = 2.443;
  	B[1].y2 = 2.047;

  	B[2].x1 = 1.834;
  	B[2].y1 = 2.044;
  	B[2].x2 = 3;
	B[2].y2 = 0.593;
*/

/*	B[0].x1 = 0;
  	B[0].y1 = 1.217;
  	B[0].x2 = 1.413;
  	B[0].y2 = 4.059;

  	B[1].x1 = 2.417;
  	B[1].y1 = 0.973;
  	B[1].x2 = 2.67;
  	B[1].y2 = 4.203;

  	B[2].x1 = 0.858;
  	B[2].y1 = 0.766;
  	B[2].x2 = 3;
	B[2].y2 = 2.589;
*/
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

  	B[0].x1 = xl;
  	B[0].x2 = xl + (rand()% width)*1.0/SCALE;
  	B[0].y1 = (rand()%MAX_HEIGHT*1.0)/SCALE;
  	B[0].y2 = (rand()%MAX_HEIGHT*1.0)/SCALE;
  	B[--n].x1 = xl + (rand()% width)*1.0/SCALE;
  	B[n].x2 = xr;
  	B[n].y1 = (rand()%MAX_HEIGHT*1.0)/SCALE;
  	B[n].y2 = (rand()%MAX_HEIGHT*1.0)/SCALE;
  
  	for(i=1;i<n;i++)
  	{
    	B[i].x1 = xl + (rand()% width)*1.0/SCALE;
    	temp = (xr - B[i].x1)*SCALE;
    	B[i].x2 = B[i].x1 + (rand()%temp)*1.0/SCALE;
    	B[i].y1 = (rand()%MAX_HEIGHT*1.0)/SCALE;
    	B[i].y2 = (rand()%MAX_HEIGHT*1.0)/SCALE;
  	}

  	return;
}

void get_skyline(building *A, skyline *S, int n, int *counter)
{
  	int i,counter1,counter2;
  	skyline *P, *Q;

  	if(n==1)
  	{
  		S[0].x = A[0].x1;
  		S[0].h = 0;
  		S[0].m = INFINITY;

  		S[1].x = A[0].x1;
  		S[1].h = A[0].y1;
  		S[1].m = get_slope(A[0].x1,A[0].y1,A[0].x2,A[0].y2);

  		S[2].x = A[0].x2;
  		S[2].h = A[0].y2;
  		S[2].m = -1*INFINITY;

  		S[3].x = A[0].x2;
  		S[3].h = 0;
  		S[3].m = 0;

  		*counter = 4;

    	return ;
  	}

  	i = n/2;

  	P = (skyline *)malloc((4*i)*sizeof(skyline));
  	Q = (skyline *)malloc(4*(n-i)*sizeof(skyline));

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
  	skyline a,b;
  	double xin, yin;
  	int intersect;

  	a.x = a.h = a.m = 0;
  	b.x = b.h = b.m = 0;

  	while((i<m)&&(j<n))
  	{
  		if(A[i].x<=B[j].x)
    	{
    		if(A[i].m == -1*INFINITY)
    		{
    			if(a.m * (A[i].x - a.x) + a.h >= A[i].h)
    			{
    			}
    			else if(b.m * (A[i].x - b.x) + b.h == A[i].h)
    			{
    				C[k++] = A[i];
    				if(a.m * (A[i].x - a.x) + a.h >= A[i+1].h)
    				{
    					C[k].x = A[i].x;
    					C[k].h = a.m * (A[i].x - a.x) + a.h;
    					C[k++].m = a.m;
    				}
    				else
    				{
    					C[k++] = A[i+1];
    				}
    			}
    			else
    			{
    				C[k++] = A[i];
    				C[k].x = A[i].x;
    				C[k].h = a.m * (A[i].x - a.x) + a.h;
    				C[k++].m = a.m;
    			}

    				b = A[i+1];
    				i += 2;
    				continue;
    		}

    		if(A[i].m == INFINITY)
    		{
    			b = A[i+1];

    			if(a.m * (A[i].x - a.x) + a.h >= A[i+1].h)
    			{
    				i += 2;
    			}
    			else if(a.m * (A[i].x - a.x) + a.h >= A[i].h)
    			{
    				C[k].x = A[i].x;
    				C[k].h = a.m * (A[i].x - a.x) + a.h;
    				C[k++].m = INFINITY;
    				C[k++] = A[++i];
	    			i++;
	    		}
	    		else
	    		{
	    			C[k++] = A[i++];
	    			C[k++] = A[i++];
	    		}
    			continue;
    		}

	    	b = A[i];

	    	intersect = do_intersect(A[i],a,&xin,&yin,A[i+1].x,B[j].x);

			if(intersect)
	    	{
	    		if(a.m * (A[i].x - a.x) + a.h >= A[i].h)
	    		{
	    			C[k].x = xin;
	    			C[k].h = yin;
	    			C[k++].m = A[i++].m;
    			}
    			else
	    		{
	    			C[k++] = A[i++];
	    			C[k].x = xin;
	    			C[k].h = yin;
	    			C[k++].m = a.m;
	    		}
	    	}
	    	else
	    	{
	    		if(a.m * (A[i].x - a.x) + a.h >= A[i].h)
	    		{
	    			i++;
	    		}
	    		else
	    		{
	    			C[k++] = A[i++];
	    		}
    		}
    	}
    	else
    	{
    		if(B[j].m == -1*INFINITY)
    		{    		
    			if(b.m * (B[j].x - b.x) + b.h >= B[j].h)
    			{
    			}
    			else if(a.m * (B[j].x - a.x) + a.h == B[j].h)
    			{
    				C[k++] = B[j];
	    			if(b.m * (B[j].x - b.x) + b.h >= B[j+1].h)
	    			{
	    				C[k].x = B[j].x;
	    				C[k].h = b.m * (B[j].x - b.x) + b.h;
	    				C[k++].m = b.m;
	    			}
	    			else
	    			{
	    				C[k++] = B[j+1];
	    			}
	    		}
	    		else
	    		{
	    			C[k++] = B[j];
	    			C[k].x = B[j].x;
	    			C[k].h = b.m * (B[j].x - b.x) + b.h;
	    			C[k++].m = b.m;
	    		}
    			a = B[j+1];
    			j+=2;
    			continue;
	    		
    		}

	    	if(B[j].m == INFINITY)
	    	{
	    		a = B[j+1];

	    		if(b.m * (B[j].x - b.x) + b.h >= B[j+1].h)
	    		{
	    			j += 2;
	    		}
	    		else if(b.m * (B[j].x - b.x) + b.h >= B[j].h)
	    		{
	    			C[k].x = B[j].x;
	    			C[k].h = b.m * (B[j].x - b.x) + b.h;
	    			C[k++].m = INFINITY;
	    			C[k++] = B[++j];
	    			j++;
	    		}
	    		else
	    		{
	    			C[k++] = B[j++];
	    			C[k++] = B[j++];
	    		}
	    		continue;
	    	}

	      	a = B[j];

	    	intersect = do_intersect(B[j],b,&xin,&yin,A[i].x,B[j+1].x);

	    	if(intersect)
	    	{
	    		if(b.m * (B[j].x - b.x) + b.h >= B[j].h)
	    		{
	    			C[k].x = xin;
	    			C[k].h = yin;
	    			C[k++].m = B[j++].m;
	    		}
	    		else
	    		{
	    			C[k++] = B[j++];
	    			C[k].x = xin;
	    			C[k].h = yin;
	    			C[k++].m = b.m;
	    			j++;
	    		}
	    	}
	    	else
	    	{
	    		if(b.m * (B[j].x - b.x) + b.h >= B[j].h)
	    		{
	    			j++;
	    		}
	    		else
	    		{
	    			C[k++] = B[j++];	    			
	    		}
    		}
    	}
 	}

  	while(i<m)
  	{
  		if(A[i].m == -1*INFINITY)
    	{
    		if(a.m * (A[i].x - a.x) + a.h >= A[i].h)
    		{
    		}
    		else if(b.m * (A[i].x - b.x) + b.h == A[i].h)
    		{
    			C[k++] = A[i];
    			if(a.m * (A[i].x - a.x) + a.h >= A[i+1].h)
    			{
    				C[k].x = A[i].x;
    				C[k].h = a.m * (A[i].x - a.x) + a.h;
    				C[k++].m = a.m;
    			}
    			else
    			{
    			C[k++] = A[i+1];
    			}
    		}
    		else
    		{
    			C[k++] = A[i];
    			C[k].x = A[i].x;
    			C[k].h = a.m * (A[i].x - a.x) + a.h;
   				C[k++].m = a.m;
   			}
 			b = A[i+1];
    		i += 2;
    		continue;
    	}

    	if(A[i].m == INFINITY)
    	{
    		b = A[i+1];

    		if(a.m * (A[i].x - a.x) + a.h >= A[i+1].h)
    		{
    			i += 2;
    		}
    		else if(a.m * (A[i].x - a.x) + a.h >= A[i].h)
    		{
    			C[k].x = A[i].x;
    			C[k].h = a.m * (A[i].x - a.x) + a.h;
    			C[k++].m = INFINITY;
    			C[k++] = A[++i];
	    		i++;
	    	}
	    	else
	    	{
	    		C[k++] = A[i++];
	    		C[k++] = A[i++];
	    	}
    		continue;
    	}

    	b = A[i];
    	intersect = do_intersect(A[i],a,&xin,&yin,A[i+1].x,B[j].x);

		if(intersect)
    	{
    		if(a.m * (A[i].x - a.x) + a.h >= A[i].h)
    		{
    			C[k].x = xin;
    			C[k].h = yin;
    			C[k++].m = A[i++].m;
   			}
   			else
    		{
    			C[k++] = A[i++];
    			C[k].x = xin;
    			C[k].h = yin;
    			C[k++].m = a.m;
    		}
    	}
    	else
    	{
    		if(a.m * (A[i].x - a.x) + a.h >= A[i].h)
    		{
    			i++;
    		}
    		else
    		{
    			C[k++] = A[i++];
    		}
   		}
	}
 	while(j<n)
 	{
 		if(B[j].m == -1*INFINITY)
    	{    		
    		if(b.m * (B[j].x - b.x) + b.h >= B[j].h)
    		{
    		}
    		else if(a.m * (B[j].x - a.x) + a.h == B[j].h)
    		{
    			C[k++] = B[j];
	    		if(b.m * (B[j].x - b.x) + b.h >= B[j+1].h)
	    		{
	    			C[k].x = B[j].x;
	    			C[k].h = b.m * (B[j].x - b.x) + b.h;
	    			C[k++].m = b.m;
	    		}
	    		else
	    		{
	    			C[k++] = B[j+1];
	    		}
	    	}
	    	else
	    	{
	    		C[k++] = B[j];
	    		C[k].x = B[j].x;
	    		C[k].h = b.m * (B[j].x - b.x) + b.h;
	    		C[k++].m = b.m;
	    	}
    		a = B[j+1];
    		j+=2;
    		continue;	
    	}

	    if(B[j].m == INFINITY)
	    {
	    	a = B[j+1];

	    	if(b.m * (B[j].x - b.x) + b.h >= B[j+1].h)
	    	{
	    		j += 2;
	    	}
	    	else if(b.m * (B[j].x - b.x) + b.h >= B[j].h)
	    	{
	    		C[k].x = B[j].x;
	    		C[k].h = b.m * (B[j].x - b.x) + b.h;
	    		C[k++].m = INFINITY;
	    		C[k++] = B[++j];
	    		j++;
	    	}
	    	else
	    	{
	    		C[k++] = B[j++];
	    		C[k++] = B[j++];
	    	}
	    	continue;
	    }

	    a = B[j];

	    intersect = do_intersect(B[j],b,&xin,&yin,A[i].x,B[j+1].x);

	    if(intersect)
	    {
	    	if(b.m * (B[j].x - b.x) + b.h >= B[j].h)
	    	{
	    		C[k].x = xin;
	    		C[k].h = yin;
	    		C[k++].m = B[j++].m;
	    	}
	    	else
	    	{
	    		C[k++] = B[j++];
	    		C[k].x = xin;
	    		C[k].h = yin;
	    		C[k++].m = b.m;
	    		j++;
	    	}
	    }
	    else
	    {
	    	if(b.m * (B[j].x - b.x) + b.h >= B[j].h)
	    	{
	    		j++;
	    	}
	    	else
	    	{
	    		C[k++] = B[j++];	    			
	    	}
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

	printf("Printing building points. Format: (x1,h1,x2,h2)\n");
	printf("x1: X-coordinate of left wall\n");
	printf("h1: Height of left wall\n");
	printf("x2: X-coordinate of right wall\n");
	printf("h2: Height of right wall\n");	

	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%d: (%lf,%lf,%lf,%lf)\n",i+1,A[i].x1,A[i].y1,A[i].x2,A[i].y2);
	}
	printf("\n\n");
}

void print_skyline(skyline *S, int counter)
{
	int i;

	printf("Printing Skyline\n");
	printf("\n");
	for(i=0;i<counter;i++)
	{
		printf("%d: (%lf,%lf) \n",i+1,S[i].x,S[i].h);
	}
	printf("\n\n");
	return;	
}

double get_slope(double x1, double y1, double x2, double y2)
{
	if(x1==x2)
	{
		if(y1<y2)
		{
			return INFINITY;
		}
		else
		{
			return -1*INFINITY;
		}
	}

	return (y2-y1)/(x2-x1);
}

int do_intersect(skyline a, skyline b, double *xin, double *yin, double x1, double x2)
{
	if(a.m==b.m)
	{
		return 0;
	}

	*xin = (a.m * a.x - a.h - b.m * b.x + b.h)/(a.m-b.m);
	
	if(*xin > a.x)
	{
		if(*xin < x1)
		{
			if(*xin < x2)
			{

				*yin = a.m * (*xin) + a.m * a.x - a.h;
				return 1;
			}
		}
	}

	return 0;
}
