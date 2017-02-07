#include <stdio.h>
#include <stdlib.h>
#define end printf("\n")
#define forn(i,sz) for(int i = 0 ; i < (sz) ; i++)



int *memory(int *array,int n)
{
	array = (int *)malloc((n * n) * sizeof(int));
	return array;
}

void dealloc(int *val)
{
	free(val);
}

int *A11 , *A12 , *A21 , *A22 , *B11, *B12 , *B21, *B22 , *s1 , *s2 , *p1 , *p2 , *p3 , *p4 , *p5 , *p6 , *p7 ;
int *final ;

void init(int n)
{
	A11 = memory(A11,n) ; A12 = memory(A12,n) ; A21 = memory(A21,n) ; A22 = memory(A22,n);
	B11 = memory(B11,n) ; B12 = memory(B12,n) ; B21 = memory(B21,n) ; B22 = memory(B22,n);
	s1 = memory(s1,n) ; s2 = memory(s2,n) ;
	p1 = memory(p1,n) ; p2 = memory(p2,n) ; p3 = memory(p3,n) ; p4 = memory(p4,n);
	p5 = memory(p5,n) ; p6 = memory(p6,n) ; p7 = memory(p7,n) ;
	final = memory(final,n);
}

void freeinit()
{
	dealloc(A11);dealloc(A12);dealloc(A21);dealloc(A22);
	dealloc(B11);dealloc(B12);dealloc(B21);dealloc(B22);
	dealloc(s1);dealloc(s2);
	dealloc(p1);dealloc(p2);dealloc(p3);dealloc(p4);dealloc(p5);dealloc(p6);dealloc(p7);
	dealloc(final);
}


int* input(int *mat , int n)
{
	mat = memory(mat,n); 
	forn(i,n)
	{
		forn(j,n)
		{
			scanf("%d",mat+i*n+j);
		}
	}
	return mat;
}

void display(int *mat , int n)
{
	forn(i,n)
	{	
		forn(j,n)
		{
			printf("%d  ", *(mat+i*n+j) );
		}
		end;
	}
}

int* Brute(int *a,int *b,int n)
{
	int *c = memory(c,n); 
	forn(i,n)
	{
		forn(j,n)
		{
			forn(k,n)
			{
				c[i*n+j] += a[i*n+k] * b[k*n+j];
			}
		}
	}
	return c;
}

int* Add_Mat(int* A,int *B,int n)
{
	int *fl = memory(fl,n);
	forn(i,n)
	{
		forn(j,n)
		{
			fl[ i*n + j] = A[ i*n + j] + B[ i*n + j];
		}
	}
	return fl;
} 

int* Sub_Mat(int* A,int *B,int n)
{
	int *fm = memory(fm,n);
	forn(i,n)
	{
		forn(j,n)
		{
			fm[ i*n + j] = A[ i*n + j] - B[ i*n + j];
		}
	}
	return fm;
}

int * Strassen_Mat(int *a,int *b,int *final,int n)
{
	if(n == 1)
	{
		final[0] = a[0] * b[0];
	}
	else
	{
		forn(i,n/2)
		{
			forn(j,n/2)
			{
				A11[ i*(n/2) + j] = a[ i*(n) + j];
	            A12[ i*(n/2) + j] = a[ i*(n) + (j+ n/2) ];
	            A21[ i*(n/2) + j] = a[ (i+ n/2) * n + j ];
	            A22[ i*(n/2) + j] = a[ (i+ n/2) * n + (j+ n/2) ];
	            B11[ i*(n/2) + j] = b[ i*(n) + j];
	            B12[ i*(n/2) + j] = b[ i*(n) + (j+ n/2) ];
	            B21[ i*(n/2) + j] = b[ (i+ n/2) * n + j ];
	            B22[ i*(n/2) + j] = b[ (i+ n/2) * n + (j+ n/2) ];
			}
		}

		//Caculating  p1
		s1 = Sub_Mat(B12,B22,n/2);
		p1 = Strassen_Mat(A11,s1,p1,n/2);
		
		//Caculating  p2
		s1 = Add_Mat(A11,A12,n/2);
		p2 = Strassen_Mat(s1,B22,p2,n/2);
		
		//Caculating  p3
		s1 = Add_Mat(A21,A22,n/2);
		p3 = Strassen_Mat(s1,B11,p3,n/2);
		
		//Caculating  p4
		s1 = Sub_Mat(B21,B11,n/2);
		p4 = Strassen_Mat(A22,s1,p4,n/2);
		
		//Caculating  p5
		s1 = Add_Mat(A11,A22,n/2);
		s2 = Add_Mat(B11,B22,n/2);
		p5 = Strassen_Mat(s1,s2,p5,n/2);
		
		//Caculating  p6
		s1 = Sub_Mat(A12,A22,n/2);
		s2 = Add_Mat(B21,B22,n/2);
		p6 = Strassen_Mat(s1,s2,p6,n/2);

		//Caculating  p7
		s1 = Sub_Mat(A11,A21,n/2);
		s2 = Add_Mat(B11,B12,n/2);
		p7 = Strassen_Mat(s1,s2,p7,n/2);

		forn(i,n/2)
		{
			forn(j,n/2)
			{	
				final[ i*n + j] = p5[ i*n + j] + p4[ i*n + j] - p2[ i*n + j] + p6[ i*n + j];
				final[ i*n + (j+ n/2) ] = p1[ i*n + j] + p2[ i*n + j];
				final[ (i+ n/2) * n + j ] = p3[ i*n + j] + p4[ i*n + j];
				final[ (i+ n/2) * n + (j+ n/2) ] = p1[ i*n + j] + p5[ i*n + j] - p3[ i*n + j] - p7[ i*n + j];
			}	
		}
	}
	return final;
}

int main()
{
	int i,j,n,sw;
	int *mat1 = NULL , *mat2 = NULL , *matF = NULL;
	system("clear");
	do
	{
		printf("\n Press 1 for Input Matrix \n Press 2 for Display Matrix \n Press 3 for Brute Forces \n Press 4 for Strassen's Algo \n Press 5 Free Memory \n Press 6 EXIT \n Enter YOUR Choice = ");
		scanf("%d",&sw);end;
		switch(sw)
		{
			case 1: printf("\n Enter the Size of a Matrix \n");
					scanf("%d",&n);
					if(n < 1)
					{
						printf("Invalid Size");end;
						break;
					}
					printf("Enter First Matrix \n");
					mat1 = input(mat1,n);
					printf("\n Enter Second Matrix \n");
					mat2 = input(mat2,n);
					break;
			case 2: if(!mat1 || !mat2)
					{
						printf("Empty matrix");end;
						break;
					}
					printf("\n First Matrix \n");
					display(mat1,n);
					printf("\n Second Matrix \n");
					display(mat2,n);
					end;
					break;
			case 3: if(!mat1 || !mat2)
					{
						printf("Empty matrix");end;
						break;
					}
					matF = Brute(mat1,mat2,n);
					display(matF,n);
					break;
			case 4: if(!mat1 || !mat2)
					{
						printf("Empty matrix");end;
						break;
					}
					init(n);
					matF = Strassen_Mat(mat1,mat2,matF,n);
					display(matF,n);
					break;
			case 5: freeinit();
					dealloc(mat1);dealloc(mat2);dealloc(matF);
					break;
		}
	}while(sw != 6);
}


