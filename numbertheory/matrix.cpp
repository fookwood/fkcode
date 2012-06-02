#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
//copyright by fish_ball
//revised by fookwood
class Mat {
public:
    int XS,YS;
    double G[20][20];
    Mat() {}
    Mat(int XS,int YS):XS(XS),YS(YS) {memset(G, 0, sizeof(G));}
};

//矩阵乘法
const Mat operator * (const Mat& a, const Mat& b) {
    Mat c(a.XS,b.YS);
    for(int i = 0; i < c.XS; ++i)
        for(int j = 0; j < c.YS; ++j)
            for(int k = 0; k < a.YS; ++k)
                c.G[i][j] += a.G[i][k] * b.G[k][j];
    return c;
}
//矩阵二分幂
const Mat pow(const Mat& a, int N) {
    if(N == 1) return a;
    Mat c = pow(a, N / 2);
    c = c * c;
    if(N % 2) c = c * a;
    return c;
}
//求第n个fibonacci数
int fib( int n ){
	Mat c(2,2);
	c.G[0][0] = c.G[0][1] = c.G[1][0] = 1;
	c = pow( c, n );
	return c.G[0][1];
}
int main(void)  {return 0;}
