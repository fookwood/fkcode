#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>

using namespace std;

/*
///////////////////////////////////
左式堆 - 可合并堆 
push pop merge - O(lgN)
///////////////////////////////////
*/
template<class T> 
class Leftist{
public:
	struct LeftistNode{
		T value;
		LeftistNode *left,*right;
		int npl;
		LeftistNode( T v, 
					 LeftistNode * l = NULL,
					 LeftistNode * r = NULL,
					 int n = 0 ):
			value(v),left(l),right(r),npl(n){}
	};

	Leftist():root(NULL){}
	~Leftist(){ destroy( root ); }

	void merge( Leftist & rhs ){
		if( this == &rhs )
			return;
		root = merge( root, rhs.root );
		rhs.root = NULL;
	}
	void push( T x ) { root = merge( root, new LeftistNode(x) ); }
	T    top( void ) { return root->value; }
	bool empty(void) { return root == NULL; }
	void pop(void){
		LeftistNode *p = root;
		root = merge( root->left, root->right );
		delete p;
	}
private:
	void destroy( LeftistNode * p ){
		if( p == NULL ) return;
		destroy( p->left  );
		destroy( p->right );
		delete p;
	}
	LeftistNode * merge( LeftistNode * hBig, LeftistNode * hSmall ){
		if( hBig == NULL ) return hSmall;
		if( hSmall == NULL ) return hBig;
		if( hBig->value < hSmall->value )
			swap( hBig, hSmall );
		if( hSmall->left == NULL ) 
			hSmall->left = hBig;
		else{
			hSmall->right = merge( hSmall->right, hBig );
			if( hSmall->left->npl < hSmall->right->npl )
				swap( hSmall->left, hSmall->right );
			hSmall->npl = hSmall->left->npl + 1;
		}
		return hSmall;
	}

	LeftistNode * root;
};
// SJTU OJ 1050
Leftist<int> heap[ 300000 ];
int N, M, t, a, b;
int main(void){

	scanf("%d%d",&N,&M);
	for( int i = 0; i < N; i++ ){
		scanf("%d",&t);
		heap[i].push(t);
	}

	for( int i = 0; i < M; i++ ){
		scanf("%d",&t);
		if( t == 0 ){
			scanf("%d%d",&a,&b);
			heap[a].merge( heap[b] );
		}
		if( t == 1 ){
			scanf("%d",&a);
			if( heap[a].empty() ) { puts("-1"); continue;}
			printf("%d\n",heap[a].top());
			heap[a].pop();
		}
		if( t == 2 ){
			scanf("%d%d",&a,&b);
			heap[a].push(b);
		}
	}

	return 0;
}
