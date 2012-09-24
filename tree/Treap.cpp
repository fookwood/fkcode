#include<iostream>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;

typedef long long LL;

template<class Tp>
class Treap{
private:
	struct TreapNode{
		Tp value;
		int fix;
		TreapNode *left,*right;

		TreapNode() {}
		TreapNode(Tp v,int f = rand()):
			value(v),fix(f),left(NULL),right(NULL){
			extraInit();	
		}
		
		// extra information
		int size;
		LL sum[5];
		int getSize( TreapNode * p ) { return p == NULL ? 0 : p->size;}
		LL getSum( TreapNode * p, int n ){return p == NULL ? 0 : p->sum[n];}
		void extraInit(){fill(sum,sum+5,0);size=0;}
		void update(void){
			size = getSize(left) + getSize(right) + 1;
			for( int i = 0; i < 5; i++ )
				sum[i] = getSum(left,i);
			sum[ getSize(left)%5 ] += value;
			for( int i = 0; i < 5; i++)
				sum[ (getSize(left)+1+i)%5 ] += getSum(right,i);
		}
		// extra operation
	};
private:
	// 向左旋转
	void leftRotate( TreapNode * & p ){
		TreapNode *temp = p->right;
		p->right = temp->left;
		temp->left = p;
		p = temp;
		p->left->update();
		p->update();
	}
	// 向右旋转
	void rightRotate( TreapNode * & p ){
		TreapNode *temp = p->left;
		p->left = temp->right;
		temp->right = p;
		p = temp;
		p->right->update();
		p->update();
	}
	void insert( TreapNode * & p, Tp v ){
		if( p == NULL ){
			p = new TreapNode(v);
		}
		else if( v < p->value ){
			insert( p->left, v );
			if( p->left->fix < p->fix )
				rightRotate( p );
		}
		else{
			insert( p->right, v );
			if( p->right->fix < p->fix )
				leftRotate( p );
		}
		p->update();
	}
	void remove( TreapNode * & p, Tp v ){
		if( p == NULL ) return;
		if( v < p->value )
			remove( p->left, v );
		else if( p->value < v )
			remove( p->right, v );
		else{
			if( p->left == NULL || p->right == NULL ){
				TreapNode *t = p;
				p = (p->right==NULL)?p->left:p->right;
				delete t;
			}
			else{
				if( p->left->fix < p->right->fix ){
					rightRotate( p );
					remove( p->right, v );
				}else{
					leftRotate( p );
					remove( p->left, v );
				}
				
			}
		}
		if( p ) p->update();
	}
	bool find( TreapNode* p, Tp v ){
		if( p == NULL ) return false;
		if( v == p->value ) return true;
		if( v < p->value ) return find( p->left,v );
		else return find( p->right, v );
	}	
	void Destroy( TreapNode* p ){
		if( p == NULL ) return;
		Destroy( p->left );
		Destroy( p->right );
		delete p;
	}
	void out( TreapNode *p ){
		if( p == NULL ) return;
		out( p->left );
		cout <<  p->value << ' ';
		out( p->right );
	}
public:
	TreapNode * root;
	Treap() { root = NULL; } 
	~Treap() { Destroy( root );}
	
	bool empty() { return root == NULL; }
	void insert( Tp v ){ insert( root, v ); } 
	void remove( Tp v ){ remove( root, v ); }
	bool find( Tp v ){ return find(root,v);}
	void print( void ) { out( root );}
};

// Codeforces 85D sum of medians
int main(void){
	Treap<int> tree;
	int N, x;
	char op[10];
	
	scanf("%d",&N);
	while( N-- ){
		scanf("%s",op);
		if( op[0] == 'a' ){
			scanf("%d",&x);
			tree.insert( x );
		}
		else if( op[0] == 'd' ){
			scanf("%d",&x);
			tree.remove( x );
		}
		else
			cout << (tree.empty()?(LL)0:tree.root->sum[2]) << endl;
	}

	return 0;
}
