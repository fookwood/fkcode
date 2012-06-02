#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

typedef long long LL;
//求绝对值
LL abs( LL a ){
	return a > 0 ? a : -a;
}

//计算机中的%运算跟数论中的不太一样
LL rightmod( LL a, LL n ){
	return (a%n+n)%n;
}

//求最大公约数的欧几里得算法
LL gcd( LL a, LL b ){
	return b == 0 ? a : gcd( b, a%b );
}

//利用二进制的快速gcd，算法导论后面好像有这个东西
LL kgcd( LL a, LL b ){
	if( !a ) return b;
	if( !b ) return a;
	if( !(a&1) && !(b&1) ) return kgcd( a/2, b/2 ) << 1;
	else if( !(b&1) ) return kgcd( a, b>>1 );
	else if( !(a&1) ) return kgcd( a>>1, b );
	else return kgcd( abs(a-b), min(a,b) );
}

//扩展欧几里得，ax+by=gcd(a,b)的可行的x,y解
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

//求模线性方程 ax=b(mod n)的所有解
vector<LL> modf( LL a, LL b, LL n ){
	LL x,y;
	LL d = ext_euclid( a, n, x, y );
	vector<LL> v;
	if( b%d ) return v;
	x = rightmod( x*b/d, n );
	for( LL i = 0; i < d; i++ )
		v.push_back( rightmod(x+i*(n/d),n) );
	return v;
}

//a表示ai，n表示互质的ni，k为个数
LL CRT( LL *a, LL *n, LL k ){
	LL i, N = 1, ans = 0;
	LL t;
	for( i = 0; i < k; i++ )
		N *= n[i];
	for( i = 0; i < k; i++ ){
		t = N/n[i]*(modf( N/n[i], 1, n[i] )[0]);
		ans = (ans + a[i]*t ) % N;
	}
	return ans;
}

//快速幂模
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

//欧拉函数
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

//质因数分解，求所有可能的组合
class DivPrime{
public:
	vector<LL> Factor;
	vector< pair<LL,LL> > V;
	LL N;

	vector< pair<LL,LL> > divprime( LL n ){
		LL i, k = n;
		N = n;
		for( i = 2; i*i <= k; i++ )
			if( n % i == 0 ){
				LL cnt = 0;
				while( n%i == 0 ) n/=i,cnt++;
				V.push_back( make_pair(i,cnt) );
			}
		if( n > 1 )
			V.push_back( make_pair(n,1) );
		return V;
	}
	void finddiv( LL th, LL ji, LL count ){
		if( th == count ){
			Factor.push_back( ji );
			return;
		}
		LL i, m;
		for( i = 0, m = 1; i <= V[th].second; i++ ){
			finddiv( th+1, ji*m, count );
			m *= V[th].first;
		}
	}
	LL div( void ){
		finddiv( 0, 1, V.size() );
		return Factor.size();
	}

};
int main(void){
	
	// null 

	return 0;
}

