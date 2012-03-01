#include<iostream>

template<typename Object>
class List{
private:
	struct Node;
	
	int theSize;
	Node *head,*tail;
	
	void init();
public:
	class const_iterator;
	class iterator;

	List();
	List( const List & rhs );
	~List();
	/*const List & operator= (const List & rhs );
	
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	int size() const;
	bool empty() const;
	void clear();

	Object & front();
	Object & back();
	const Object & front() const;
	const Object & back()  const;

	void push_front( const Object & x );
	void push_back(  const Object & x );
	void pop_front();
	void pop_back();

	iterator insert( iterator itr, const Object & x );
	iterator erase( iterator itr );
	iterator erase( iterator start, iterator end );
	*/
};
//  implements ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ below ~~
template<typename Object>
struct List<Object>::Node{
	Object data;
	Node *prev;
	Node *next;
	Node( const Object & d = Object(), Node *p = NULL, Node *n = NULL ):
		data(d),prev(p),next(n){}
};

template<typename Object>
void List<Object>::init(void){
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}

template<typename Object>
List<Object>::List(){
	init();
}

template<typename Object>
List<Object>::List( const List & rhs ){
	init();
	*this = rhs;
}
/*
template<typename Object>
List<Object>::~List(){
	clear();
	delete head;
	delete tail;
}

template<typename Object>
const List<Ojbect> & List<Object>::operator= ( const List<Object> & rhs ){
	if( this == &rhs ) return *this;
	clear();
	for( const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr )
		push_back( *itr );
	return *this;
}
*/

template<typename Object>
class List<Object>::const_iterator{
public:
	const_iterator():current(NULL){}

	Object & operator* () { return retrieve(); }
	const Object & operator* () const { 
		current = current->next;
		return *this;
	}
	const_iterator operator++ (){
		current = current->next;
		return *this;
	}
	const_iterator operator++ (int){
		const_iterator old = *this;
		++( *this );
		return old;
	}
	bool operator== (const const_iterator & rhs ) const 
		{ return current == rhs.current; }
	bool operator!= (const const_iterator & rhs ) const
		{ return !( *this == rhs ); }
		
protected:
	Node *current;
	Object & retrieve() const { return current->data; }
	const_iterator( Node *p ):current(p){}
	friend class List<Object>;
};

template<typename Object>
class List<Object>::iterator:public const_iterator{
public:
	iterator(){}

	Object & operator* () 
		{ return const_iterator::retrieve(); }
	const Object & operator* () const 
		{ return const_iterator::operator*(); }

	iterator & operator++ (){
		const_iterator::current = 
			const_iterator::current->next;
		return *this;
	}
	iterator & operator++ (int) {
		iterator old = *this;
		++( *this );
		return old;
	}
protected:
	iterator( Node *p ) : const_iterator(p){}
	friend class List<Object>;
};


int main(){return 0;}
