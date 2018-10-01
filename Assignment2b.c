#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 10000000.0

typedef struct point
{
	double x;
	double y;
}point;

double closest_pair(point P[], point *a, point *b, int n);
void mergeSortX(point *A, int n);
void mergeX(point *A, point *B, point*C, int m, int n);
void mergeSortY(point *A, int n);
void mergeY(point *A, point *B, point*C, int m, int n);
double find_min_distance(point Px[], point Py[], point *a, point *b, int n);
double brute_force(point Px[], point *a, point *b, int n);
double distance(point a, point b);
double strip_closest(point PyStrip[], double d, point *a, point *b, int n);

int main()
{
	int n,i;
	point *P,a,b;
	double minimum_distance;

	printf("\n");
	printf("Enter number of points: ");
	scanf("%d", &n);
	printf("\n");

	P = (point *)malloc(n*sizeof(point));

	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("Enter x coordinate and y coordinate of point %d respectively with a space in between: ",i+1);
		scanf("%lf %lf", &P[i].x, &P[i].y);
	}
	printf("\n");

	minimum_distance = closest_pair(P,&a,&b,n);

	printf("\n");
	printf("The closest pair of points are (%lf,%lf) and (%lf,%lf) with distance between them equal to %.3lf.\n",a.x,a.y,b.x,b.y,minimum_distance);
	printf("\n");
}

double closest_pair(point P[], point *a, point *b, int n)
{
	int i;
	point Px[n], Py[n];

	for(i=0;i<n;i++)
	{
		Px[i] = Py[i] = P[i];
	}
	
	mergeSortX(Px,n);
	mergeSortY(Py,n);

	return find_min_distance(Px,Py,a,b,n);
}


void mergeSortX(point *A, int n)
{
	int i,j;
	point *B;

	if(n<=1)
	{
		return ;
	}

	B = (point *)malloc(n*sizeof(point));

	i = n/2;

	mergeSortX(A,i);
	mergeSortX(A+i,n-i);
	mergeX(A,A+i,B,i,n-i);

	for(i=0;i<n;i++)
	{
		A[i] = B[i];
	}

	free (B);

	return;
}

void mergeX(point *A, point *B, point*C, int m, int n)
{
	int i=0;
	int j=0;
	int k=0;

	while((i<m)&&(j<n))
	{
		if(A[i].x<B[j].x)
		{
			C[k++] = A[i++];
		}
		else if(A[i].x == B[j].x)
		{
			if(A[i].y <= B[j].y)
			{
				C[k++] = A[i++];
			}
			else
			{
				C[k++] = B[j++];
			}
		}
		else
		{
			C[k++] = B[j++];
		}
	}

	while(i<m)
	{
		C[k++] = A[i++];
	}
	while(j<n)
	{
		C[k++] = B[j++];
	}

	return;
}

void mergeSortY(point *A, int n)
{
	int i,j;
	point *B;

	if(n<=1)
	{
		return ;
	}

	B = (point *)malloc(n*sizeof(point));

	i = n/2;

	mergeSortY(A,i);
	mergeSortY(A+i,n-i);
	mergeY(A,A+i,B,i,n-i);

	for(i=0;i<n;i++)
	{
		A[i] = B[i];
	}

	free (B);

	return;
}

void mergeY(point *A, point *B, point*C, int m, int n)
{
	int i=0;
	int j=0;
	int k=0;

	while((i<m)&&(j<n))
	{
		if(A[i].y<B[j].y)
		{
			C[k++] = A[i++];
		}
		else if(A[i].y == B[j].y)
		{
			if(A[i].x <= B[j].x)
			{
				C[k++] = A[i++];
			}
			else
			{
				C[k++] = B[j++];
			}
		}
		else
		{
			C[k++] = B[j++];
		}
	}

	while(i<m)
	{
		C[k++] = A[i++];
	}
	while(j<n)
	{
		C[k++] = B[j++];
	}

	return;
}

double find_min_distance(point Px[], point Py[], point *a, point *b, int n)
{
	int i,j,mid,counter = 1,k;
	double d1,d2,dl,dr;
	point Pxl[(int)ceil(n/2.0)], Pxr[n/2], Pyl[(int)ceil(n/2.0)], Pyr[n/2], PyStrip[n];
	point c,d;

	if(n<=3)
	{
		d1 = brute_force(Px,a,b,n);
		return d1;
	}

	for(i=0;i<(int)ceil(n/2.0);i++)
	{
		Pxl[i] = Px[i];
	}
	for(j=0;i<n;i++,j++)
	{
		Pxr[j] = Px[i];
	}

	mid = (int)ceil(n/2.0)-1;
	i = mid - 1;

	while((i>=0)&&(Pxl[i].x == Pxl[mid].x))
	{
		counter++;
		i--;
	}

	for(i=0,j=0,k=0;i<n;i++)
	{
		if(Py[i].x < Pxl[mid].x)
		{
			Pyl[j++] = Py[i]; 
		}
		else if(Py[i].x == Pxl[mid].x)
		{
			if(counter>0)
			{
				Pyl[j++] = Py[i];
				counter--;
			}
			else
			{
				Pyr[k++] = Py[i];
			}
		}
		else
		{
			Pyr[k++] = Py[i];
		}
	}

	d1 = find_min_distance(Pxl, Pyl, a, b, (int)ceil(n/2.0));
	d2 = find_min_distance(Pxr, Pyr, &c, &d, n/2);
	
	if(d2<d1)
	{
		d1 = d2;
		*a = c;
		*b = d;
	}

	dl = Pxl[mid].x - d1;
	dr = dl + 2*d1;
	for(i=0,k=0;i<=mid;i++)
	{
		if(Pyl[i].x >= dl)
		{
			PyStrip[k++] = Pyl[i];
		}
	}
	for(j=0;j<n/2;j++)
	{
		if(Pyr[j].x <= dr)
		{
			PyStrip[k++] = Pyr[j];
		}
	}

	d2 = strip_closest(PyStrip,d1,a,b,k);

	return (d1<d2) ? d1:d2 ;
}

double brute_force(point Px[], point *a, point *b, int n)
{
	double	 min,d1,d2;
	min = distance(Px[0],Px[1]);
	if(n==3)
	{
		d1 = distance(Px[0],Px[2]);
		d2 = distance(Px[1],Px[2]);

		if(d1<min)
		{
			if(d2 < d1)
			{
				*a = Px[1];
				*b = Px[2];
				return d2;
			}
			else
			{
				*a = Px[0];
				*b = Px[2];
				return d1;
			}
		}
		else if(d2 < min)
		{
			*a = Px[1];
			*b = Px[2];
			return d2;
		}
		else
		{
			*a = Px[0];
			*b = Px[1];
			return min;
		}
	}
	
	*a = Px[0];
	*b = Px[1];
	return min;
}

double distance(point a, point b)
{
	double xlength, ylength;

	xlength = a.x - b.x;
	ylength = a.y - b.y;

	return sqrt(xlength*xlength+ylength*ylength);
}

double strip_closest(point PyStrip[], double d, point *a, point *b, int n)
{
	int i,j;
	double d1 = MAX;

	for(i=n-1;i>0;i--)
	{
		for(j=1;(j<=7)&&(i-j>=0);j++)
		{
			if(distance(PyStrip[i],PyStrip[i-j])<d)
			{
				d1 = distance(PyStrip[i],PyStrip[i-j]);
				*a = PyStrip[i];
				*b = PyStrip[i-j];
			}
		}
	}
	return d1;
}
