#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>

using namespace std;

template<class T>
class AVL{
	struct AvlNode{
		T data;
		int height;
		AvlNode *left, *right;
		AvlNode( T n, AvlNode *l = NULL, AvlNode *r = NULL, int h = 0):
			left(l),right(r),data(n),height(h){}
	};
public:
	AVL():head(NULL){}
	~AVL(){ destroy(head); }
	void insert( const T & x ) { insert( x, head ); }
	void print( void ){ print(head);}
	bool contains( const T & x ){return contains(x,head);}
private:
	bool contains( const T & x, AvlNode * p ){
		if( p == NULL ) return false;
		if( p->data == x ) return true;
		if( x < p->data ) return contains( x, p->left );
		else return contains( x, p->right );
	}
	void destroy( AvlNode * p ){
		if( p == NULL ) return;
		destroy( p->left );
		destroy( p->right);
		delete p;
	}
	void print( AvlNode * p ){
		if( p == NULL ) return;
		print( p->left );
		cout << p->data << ' ' ;
		print( p->right );
	}
	void singleRotateLeft( AvlNode * & p ){
		AvlNode * l = p->left;
		p->left = l->right;
		l->right = p;
		p->height = max( height(p->left), height(p->right) ) + 1;
		l->height = max( height(l->left), height(l->right) ) + 1;
		p = l;
	}
	void singleRotateRight( AvlNode * & p ){
		AvlNode * l = p->right;
		p->right = l->left;
		l->left = p;
		p->height = max( height(p->left), height(p->right) ) + 1;
		l->height = max( height(l->left), height(l->right) ) + 1;
		p = l;
	}
	void doubleRotateLeft( AvlNode * & p ){
		singleRotateRight( p->left );
		singleRotateLeft(  p );
	}
	void doubleRotateRight( AvlNode * & p ){
		singleRotateLeft(  p->right );
		singleRotateRight( p );
	}
	void insert( const T & x, AvlNode * & p ){
		if( p == NULL )
			p = new AvlNode(x);
		else if( x < p->data ){
			insert( x, p->left );
			if( height( p->left ) - height( p->right ) == 2 )
				x<p->left->data ? singleRotateLeft(p) : doubleRotateLeft(p);
		}
		else if( p->data < x ){
			insert( x, p->right );
			if( height( p->right ) - height( p->left ) == 2 )
				p->right->data<x ? singleRotateRight(p) : doubleRotateRight(p);
		}
		p->height = max( height(p->left), height(p->right) ) + 1;
	}

	int height( AvlNode * p ){
		return p==NULL? -1 : p->height;
	}

	AvlNode * head;
};

int main(void){

	AVL<int> tree;
	for( int i = 0; i < 100; i++ )
		tree.insert( rand()%100 );
	int cnt = 0;
	for( int i = 0; i < 100; i++ )
		if( tree.contains(i) ) cnt++;
	cout << cnt << endl;
	tree.print();
	return 0;
}
