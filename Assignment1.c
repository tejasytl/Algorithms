#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.1415926

typedef struct complex{
  	double Re;
  	double Im;
} complex;

complex prod(complex a, complex b)
{
  	complex product;
  	product.Re = a.Re * b.Re - a.Im * b.Im;
  	product.Im = a.Re * b.Im + a.Im * b.Re;
  	return product;
}

complex add(complex a, complex b)
{
  	complex sum;
  	sum.Re = a.Re + b.Re;
  	sum.Im = a.Im + b.Im;
  	return sum;
}

complex sub(complex a, complex b)
{
  	complex diff;
  	diff.Re = a.Re - b.Re;
  	diff.Im = a.Im - b.Im;
  	return diff;
}

int get_n(int no_of_digits);
void get_integers(complex integer1[], complex integer2[], int n, int no_of_digits);
void fft(int n, complex A[], complex F[]);
void multiply_ffts(complex A[], complex B[], complex C[], int n);
void inverse_fft(int n, complex A[], complex F[]);
void get_final_poly(complex A[], int n);
void print_number(complex A[], int n);

int main()
{
	int no_of_digits,n;
	complex *number1, *number2, *fft1, *fft2, *fft_prod, *coef_prod_poly;

	printf("Enter number of digits: ");
	scanf("%d", &no_of_digits);
	n = get_n(no_of_digits);

	number1 = (complex *)malloc((2*n)*sizeof(complex));
	number2 = (complex *)malloc((2*n)*sizeof(complex));
	get_integers(number1,number2,(2*n),no_of_digits);

	fft1 = (complex *)malloc((2*n)*sizeof(complex));
	fft2 = (complex *)malloc((2*n)*sizeof(complex));
	fft((2*n),number1,fft1);
	fft((2*n),number2,fft2);

	fft_prod = (complex *)malloc((2*n)*sizeof(complex));
	multiply_ffts(fft1,fft2,fft_prod,(2*n));

	coef_prod_poly = (complex *)malloc((2*n)*sizeof(complex));
	inverse_fft((2*n),fft_prod,coef_prod_poly);
	get_final_poly(coef_prod_poly,(2*n));

	printf("A = ");
  	print_number(number1,no_of_digits);
  	printf("\n");
  	printf("B = ");
  	print_number(number2,no_of_digits);
  	printf("\n");
  	printf("A * B = ");
  	print_number(coef_prod_poly,(2*no_of_digits+1));
  	printf("\n");

	return 0;
}

//To get least n >= no_of_digits such that it is a power of 2
int get_n(int no_of_digits)
{
  	int n=1;
  	no_of_digits--;

  	while(no_of_digits)
  	{
    	n *= 2;
    	no_of_digits /= 2;
  	}

  	return n;
}

// To obtain random integers and extend the array with 0s
void get_integers(complex integer1[], complex integer2[], int n, int no_of_digits)
{
	srand(time(NULL));
  	int i;

  	for(i=0;i<no_of_digits;i++)
  	{
    	integer1[i].Re = rand()%10;
    	integer2[i].Re = rand()%10;
    	integer2[i].Im = integer1[i].Im = 0;
  	}
  	while(integer1[no_of_digits-1].Re == 0)
  	{
  		integer1[no_of_digits-1].Re = rand()%10;
  	}
  	while(integer2[no_of_digits-1].Re == 0)
  	{
  		integer2[no_of_digits-1].Re = rand()%10;
  	}
  	while(i<n)
  	{
    	integer1[i].Re = integer1[i].Im = integer2[i].Re = integer2[i].Im = 0;
    	i++;
  	}

  	return;
}

//get the FFTs with A as coefficient vector
void fft(int n, complex A[], complex F[])
{
  	int j,k, sft = n/2;
  	complex omegak, omega;

  	if(n==1)
    {
    	F[0] = A[0];
      	return ;
    }

  	complex E[n/2], O[n/2], EF[n/2], OF[n/2];
  
  	for(j=k=0;k<n;j++,k+=2)
    {
      	E[j] = A[k];
      	O[j] = A[k+1];
    }  

  	fft(n/2,E,EF);
  	fft(n/2,O,OF);

  	omega.Re = cos(2*PI/n);
  	omega.Im = sin(2*PI/n);
  	omegak.Re = 1.00;
  	omegak.Im = 0.00; 
  	for(k=0;k<n/2;k++,omegak = prod(omegak,omega))
    {
   	    F[k] = add(EF[k], prod(omegak,OF[k]));
      	F[k+sft] = sub(EF[k], prod(omegak,OF[k]));
    }

    return ;
}

// Multiplication of respective indivual values of two ffts
void multiply_ffts(complex A[], complex B[], complex C[], int n)
{
  	int i;

  	for(i=0;i<n;i++)
  	{
    	C[i] = prod(A[i],B[i]);
  	}

  	return;
}

//To get the inverse fft with A as our product vector and F as to be coefficient vector of the product polynomial
void inverse_fft(int n, complex A[], complex F[])
{
  	int j,k, sft = n/2;
  	complex omegak, omega;

  	if(n==1)
    {
  		F[0] = A[0];
      	return ;
    }

  	complex E[n/2], O[n/2], EF[n/2], OF[n/2];
  
  	for(j=k=0;k<n;j++,k+=2)
    {
     	E[j] = A[k];
      	O[j] = A[k+1];
    }  

  	inverse_fft(n/2,E,EF);
  	inverse_fft(n/2,O,OF);

  	omega.Re = cos(-2*PI/n);
  	omega.Im = sin(-2*PI/n);
  	omegak.Re = 1.00;
  	omegak.Im = 0.00;
  	for(k=0;k<n/2;k++, omegak = prod(omegak,omega))
    {
      F[k] = add(EF[k], prod(omegak,OF[k]));
      F[k+sft] = sub(EF[k], prod(omegak,OF[k]));
    }

    return;
}

//To divide the coefficients obtained by inverse FFT by n
void get_final_poly(complex A[], int n)
{
  	int i;

  	for(i=0;i<n;i++)
  	{
    	A[i].Re /= n;
  	}

  	return;
}

//To print the number string
void print_number(complex A[], int n)
{
  	int i, numbers[n], temp = 0;

  	for(i=0;i<n;i++)
  	{
    	temp += floor(A[i].Re + 0.5);
    	numbers[i] = temp%10;
    	temp /= 10;  
  	}

  	for(i=n-1;i>=0;i--)
  	{
    	printf("%d", numbers[i]);
  	}

  	printf("\n");

  	return;
}
