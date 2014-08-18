
/* 
 
* Project 2: sorted list in a structured way
 
*/


#include <stdio.h>

#include "repository.h"



int Max_range=100;

unsigned long int next =1;



void Get_next_op( char *random_op, int *random_int, int range );

int  rand( void ); 

void srand( unsigned int seed );



main()
{

    unsigned int s;


    int    num_op;
 
   int    rand_key;

    char   rand_op;

    int    ret;

    int	   ret_data;

    int    i;


    unsigned long sum_data;

    int num_get, num_delete, num_insert;


    printf("Repository project\n");

    printf("Please enter the number of operations requested: ");
    scanf("%d", &num_op );
    printf("Please enter the max range of random numbers: ");
    scanf("%d", &Max_range );
    printf("Please enter a starting seed: ");
    scanf("%d", &s );
    printf("\nGenerating %d operations with range %d and random seed %d \n", num_op, Max_range, s);
    printf("-------------------------------------------------------------------------\n");

    srand( s );

    sum_data   = 0;

    num_get    = 0;
    num_delete = 0;
    num_insert = 0;

    Repository_init();
	printf("the project works here");

    for( i = 1; i <= num_op; i++ )
    {
        Get_next_op( &rand_op, &rand_key, Max_range );

	/* printf("%c %8d %d\n", rand_op, rand_key, Max_range ); */

	switch( rand_op )
	{
	    case 'G':
                num_get++;
		ret = Repository_get( rand_key, &ret_data );
		if( ret < 0 ) {
			printf("\nError in Get with return value %d \n", ret );
		}
		if( ret == 1 ) sum_data = sum_data + (ret_data%100);
		break;

	    case 'I':
                num_insert++;
		ret = Repository_insert( rand_key, i );
		if( ret < 0 ) {
			printf("\nError in Insert with return value %d \n", ret );
		}
		break;

	    case 'D':
                num_delete++;
		ret = Repository_delete( rand_key );
		if( ret < 0 ) {
			printf("\nError in Delete with return value %d \n", ret );
		}
		break;

	    default:
		printf("\nError!!!, Illegal operation %c\n", rand_op );
		return 0;
	}

        if( (i % (num_op/10)) == 0 )
	{
		printf("Printing after %d operations\n", i );
		if( Max_range > 100 ) Repository_print( 0 );
		else Repository_print( 1 );
	}
    }
    printf("Operation summary: get %d, delete %d, insert %d\n", num_get, num_delete, num_insert );
    printf("Sum of all Repository_get data modulo 100 is %d\n", sum_data );
}

void Get_next_op( char *random_op, int *random_int, int range )
{
    int  random_number;
    int  limit;

    random_number = rand() % 4;

    switch( random_number )
    {
	case 0:
	case 1:
		*random_op = 'G';
		break;
	case 2:
		*random_op = 'D';
		break;
	case 3:
		*random_op = 'I';
    }

    limit = (32768 / range ) * range;
    while( ( random_number = rand() ) >= limit ) ;

    *random_int = random_number % range + 1;
}

/* Pseudo random generator on 0..32767 */
int  rand(void)
{
    next = next *1103515245 + 12345;
    return (unsigned int)(next/65536)%32768;
}

void srand( unsigned int seed )
{
    next = seed;
}
