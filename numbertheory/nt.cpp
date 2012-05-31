#include<iostream>
#include<vector>
using namespace std;

/******

  unfinished...   
			
		--fookwood

******/

typedef long long LL;

LL abs( LL a, LL b ){
	if( a > b ) return a-b;
	return b-a;
}

LL rightmod( LL a, LL n ){
	return (a%n+n)%n;
}

LL gcd( LL a, LL b ){
	return b == 0 ? a : gcd( b, a%b );
}

LL kgcd( LL a, LL b ){
	if( !a ) return b;
	if( !b ) return a;
	if( !(a&1) && !(b&1) ) return kgcd( a/2, b/2 ) << 1;
	else if( !(b&1) ) return kgcd( a, b>>1 );
	else if( !(a&1) ) return kgcd( a>>1, a );
	else return kgcd( abs(a-b), min(a,b) );
}

LL ext_euclid( LL a, LL b, LL &x, LL &y ){
	LL t,d;
	if( b == 0 ){
		x = 1;
		y = 0;
		return a;
	}
	d = ext_euclid( b, a%b, x, y );
	t = x;
	x = y;
	y = t - (a/b)*y;
	return d;
}

vector<LL> modf( LL a, LL b, LL n ){
	LL x,y;
	LL d = ext_cuclid( a, n, x, y );
	vector<LL> v;
	if( b%d ) return v;
	x = rightmod( x*b/d, n );
	for( int i = 0; i < d; i++ )
		v.push_back( rightmod(x+i*(n/d),n) );
	return v;
}

LL CRT( LL *a, LL *n, LL k ){
	LL i, N = 1, ans = 0;
	LL t;
	for( i = 0; i < k; i++ )
		N *= n[i];
	for( i = 0; i < k; i++ ){
		t = N/n[i]*modf( N/n[i], 1, n[i] );
		ans = (ans + a[i]*t ) % N;
	}
	return ans;
}

LL fastmod( LL a, LL k, LL M ){
	LL b = 1ll;
	while( k ){
		if( k&1 )
			b = a*b%M;
		a = (a%M)*(a%M)%M;
		k >> 1;
	}
	return b;
}

LL euler( LL n ){
	LL i, m = (int)sqrt( n + 0.5 ), ans = n;
	for( i = 2; i <= m; i++ )
		if( n%i == 0 ){
			ans = ans/i*(i-1);
			while( n%i == 0 ) n /= i;
		}
	if( n > 1 ) ans = ans/n*(n-1);
	return ans;
}


int main(void){
	

	return 0;
}

