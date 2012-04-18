#include<stdio.h>
#include<string.h>
//can be replaced by enum in Bitvector
#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F

template<int N>
class Bitvector{
	int a[ 1 + N/BITSPERWORD ];
public:
	Bitvector(){ clear(); }
	
	void clear() { memset( a, 0, sizeof(a) ); } 
	void set( int i ) {		
		a[ i>>SHIFT	] |= ( 1<<( i&MASK ) ); 
	}
	void clr( int i ) {		
		a[ i>>SHIFT ] &= ~(1<<( i&MASK ) );
	}
	int test( int i ) {
		return			
		a[ i>>SHIFT ] &  ( 1<<( i&MASK ) ); 
	}
};
int main(void){
	int i;
	Bitvector<200> v;
	for( i = 0; i < 100; i++ )
		v.set( i*2 );
	for( i = 0; i < 200; i++ )
		printf("%d",v.test(i)?1:0 );
	puts("");
	return 0;
}
