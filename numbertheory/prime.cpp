#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<cmath>

using namespace std;
// linear
const int SULEN = 1000000;
bool flag[ SULEN ];
int prime[ SULEN ];
int sum[   SULEN ];//sum[i]表示i的质因子的和
void xianxingshai( void ){
	int count,i,j;
	fill( flag, flag+SULEN, true );
	fill( sum,	sum+SULEN,	0 );
	flag[0] = flag[1] = false;
	for( count = 0, i = 2; i < SULEN; i++ ){
		if( flag[i]  )
			prime[count++] = sum[i] = i;
		for( j = 0; j < count && i*prime[j] < SULEN; j++ ){
			flag[ i*prime[j] ] = false;
			if( i%prime[j] == 0 ){
				sum[ i*prime[j] ] = sum[i];
				break;
			}
			else
				sum[ i*prime[j] ] = sum[i] + prime[j];
		}
	}
}

// O(NlogN)

const int len = 1000000;
bool isprime[ len ];
void nlognprime( int n ){
	fill( isprime, isprime+len, true );
	isprime[0] = isprime[1] = false;
	int i, j, m = (int)sqrt(n+0.5);
	for( i = 2; i <= m; i++ )
		if( isprime[i] )
			for( j = i*i; j < n; j += i )
				isprime[j] = false;
}

// miller-rabin 素数测试 poj 3641可以用来练习

typedef long long LL;

//快速幂模。。。 求b=a^k%M，nt.cpp中已经包含了
LL fastmod(LL a,LL k,LL M){
    LL b = 1;
    while( k ){
        if( k&1 )
            b = a*b%M;
        a = (a%M)*(a%M)%M;
        k /= 2;
    }
    return b;
}
LL witness( LL a,LL n ){
    LL u = n-1,t = 0;
    while( !(u&LL(1)) ) {u>>=1;t++;}
    LL x1,x0 = fastmod(a,u,n);
    for( LL i = 1; i <= t; i++ ){
        x1 = x0*x0%n;
        if( x1 == 1 && x0 != 1 && x0 != n-1 )
            return 1;
        x0 = x1;
    }
    if( x0 != 1 ) return 1;
    else return 0;
}
bool miller_rabin(LL n ,LL s ){
    if( n==2 ) return true;
    if( n%2==0 || n < 2 ) return false;
    LL j,a;
    for( j = 1; j <= s; j++ ){
        a = rand()*(n-2)/RAND_MAX + 1;
        if( witness(a,n) ) return false;
    }
    return true;
}

int main(void){
	//null
	return 0;
}
