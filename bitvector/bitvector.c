#include<stdio.h>
#include<string.h>

#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define N 1000000

int a[ 1 + N/BITSPERWORD ];

void clear() { memset( a, 0, sizeof(a) ); } 
void set( int i ) {		a[ i>>SHIFT	] |= ( 1<<( i&MASK ) ); }
void clr( int i ) {		a[ i>>SHIFT ] &= ~(1<<( i&MASK ) ); }
int test( int i ) {
		return			a[ i>>SHIFT ] &  ( 1<<( i&MASK ) ); }

int main(void){
	int i;
	clear();
	for( i = 0; i < 100; i++ )
		set( i*2 );
	for( i = 0; i < 200; i++ )
		printf("%d",test(i)?1:0 );
	puts("");
	return 0;
}
