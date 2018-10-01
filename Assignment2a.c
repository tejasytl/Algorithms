#include <stdio.h>
#include <stdlib.h>

int counter = 1;

void fill_L(int row_blank, int column_blank, int row_start, int row_end, int column_start, int column_end);

int main()
{
	int n,row_blank,column_blank;

	printf("\nEnter the grid size: ");
	scanf("%d", &n);
	
	printf("\nNote: The grid's indices start from zero.\nSo, the coordinates of missing tile are in the range 0 - %d.\n",n-1);
	printf("\nEnter the x-coordinate and y-coordinate of missing tile respectively with spaces: ");
	scanf("%d %d", &row_blank, &column_blank);
	
	printf("\n");
	printf("Configuration 1:\n");
	printf("*\n**\n\n");
	
	printf("\n");
	printf("Configuration 2:\n");
	printf("**\n*\n\n");
	
	printf("\n");
	printf("Configuration 3:\n");
	printf(" *\n**\n\n");
	
	printf("\n");
	printf("Configuration 4:\n");
	printf("**\n *\n\n");
	
	fill_L(row_blank,column_blank,0,n-1,0,n-1);
	printf("\n");
	return 0;
}

void fill_L(int row_blank, int column_blank, int row_start, int row_end, int column_start, int column_end)
{	
	int row_mid = (row_end+row_start)/2;
	int column_mid = (column_end+column_start)/2;

	if(row_end-row_start == 1)
	{
		if(row_blank == row_start)
		{
			if(column_blank == column_start)
			{
				printf("%d: Configuration 3: (%d,%d)\n",counter++, row_start+1, column_start+1);
			}
			else
			{
				printf("%d: Configuration 1: (%d,%d)\n",counter++, row_start+1, column_start);
			}
		}
		else
		{
			
			if(column_blank == column_start)
			{	
				printf("%d: Configuration 4: (%d,%d)\n",counter++, row_start, column_start+1);
			}
			else
			{
				printf("%d: Configuration 2: (%d,%d)\n",counter++, row_start, column_start);
			}
		}
		return ;
	}		
	
	if(row_blank <= row_mid)
	{
		if(column_blank <= column_mid)
		{
			printf("%d: Configuration 3: (%d,%d)\n",counter++, row_mid+1, column_mid+1);
			fill_L(row_blank,column_blank,row_start,row_mid,column_start,column_mid);
			fill_L(row_mid,column_mid+1,row_start,row_mid,column_mid+1,column_end);
			fill_L(row_mid+1,column_mid,row_mid+1,row_end,column_start,column_mid);
			fill_L(row_mid+1,column_mid+1,row_mid+1,row_end,column_mid+1,column_end);
			return ;
		}
		else
		{
			printf("%d: Configuration 1: (%d,%d)\n", counter++, row_mid+1, column_mid);
			fill_L(row_mid,column_mid,row_start,row_mid,column_start,column_mid);
			fill_L(row_blank,column_blank,row_start,row_mid,column_mid+1,column_end);
			fill_L(row_mid+1,column_mid,row_mid+1,row_end,column_start,column_mid);
			fill_L(row_mid+1,column_mid+1,row_mid+1,row_end,column_mid+1,column_end);			
			return ;
		}
	}
	else
	{
		if(column_blank <= column_mid)
		{
			printf("%d: Configuration 4: (%d,%d)\n",counter++, row_mid+1, column_mid);
			fill_L(row_mid,column_mid,row_start,row_mid,column_start,column_mid);
			fill_L(row_mid,column_mid+1,row_start,row_mid,column_mid+1,column_end);
			fill_L(row_blank,column_blank,row_mid+1,row_end,column_start,column_mid);			
			fill_L(row_mid+1,column_mid+1,row_mid+1,row_end,column_mid+1,column_end);			
			return ;
		}
		else
		{
			printf("%d: Configuration 2: (%d,%d)\n",counter++, row_mid, column_mid);
			fill_L(row_mid,column_mid,row_start,row_mid,column_start,column_mid);
			fill_L(row_mid,column_mid+1,row_start,row_mid,column_mid+1,column_end);
			fill_L(row_mid+1,column_mid,row_mid+1,row_end,column_start,column_mid);
			fill_L(row_blank,column_blank,row_mid+1,row_end,column_mid+1,column_end);
			return ;
		}
	}
}
			
