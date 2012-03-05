#include<iostream>
template<typename Object>
class List{
private:
	struct Node;	//存放节点信息	
	int theSize;	//List包含的元素的个数
	Node *head,*tail; //当容器为空的时候，有两个节点
	
	void init(); 
public:
	class const_iterator; //const迭带器
	class iterator;			//迭带器

	List();//constructor
	List( const List & rhs );
	~List();
	const List & operator= (const List & rhs );
	//the "Big Three"

	//basic routines, easy to understand by name 
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
	
};
//implements ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ below ~~
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
List<Object>::List(){ init();}

template<typename Object>
List<Object>::List( const List & rhs ){
	init();
	*this = rhs;
}

template<typename Object>
List<Object>::~List(){
	clear();
	delete head;
	delete tail;
}

template<typename Object>
const List<Object> & List<Object>::operator= ( const List<Object> & rhs ){
	if( this == &rhs ) return *this;
	clear();
	for( const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr )
		push_back( *itr );
	return *this;
}

template<typename Object>
typename List<Object>::iterator List<Object>::begin() 
	{ return iterator( List<Object>::head->next ); }
template<typename Object>
typename List<Object>::iterator List<Object>::end() 
	{ return iterator( List<Object>::tail ); }
template<typename Object>
typename List<Object>::const_iterator List<Object>::begin() const 
	{ return const_iterator( List<Object>::head->next); }
template<typename Object>
typename List<Object>::const_iterator List<Object>::end() const 
	{ return const_iterator( List<Object>::tail); }

template<typename Object>
int List<Object>::size() const { return theSize; }
template<typename Object>
bool List<Object>::empty() const { return size() == 0; }
template<typename Object>
void List<Object>::clear() { while( !empty() ) pop_front(); }

template<typename Object>
Object & List<Object>::front() { return *begin(); }
template<typename Object>
Object & List<Object>::back() { return *--end(); }
template<typename Object>
const Object & List<Object>::front() const { return *begin(); }
template<typename Object>
const Object & List<Object>::back() const { return *--end(); }

template<typename Object>
void List<Object>::push_front( const Object & x ) { insert( begin(), x ); }
template<typename Object>
void List<Object>::push_back( const Object & x ) { insert( end(), x ); }
template<typename Object>
void List<Object>::pop_front() { erase( begin() ); }
template<typename Object>
void List<Object>::pop_back() { erase( end() ); }
	
template<typename Object>
typename List<Object>::iterator List<Object>::insert
	( List<Object>::iterator itr, const Object & x ){
	Node *p = itr.current;
	theSize++;
	return List<Object>::iterator(p->prev=p->prev->next=new Node( x,p->prev,p ) );
}

template<typename Object>
typename List<Object>::iterator List<Object>::erase
	( List<Object>::iterator itr ){
	Node *p = itr.current;
	iterator retVal( p->next );
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	theSize--;
	return retVal;
}

template<typename Object>
typename List<Object>::iterator List<Object>::erase
	( List<Object>::iterator start,List<Object>::iterator end ){
	for( iterator itr = start; itr != end; )
		itr = erase( itr );
	return end;
}

template<typename Object>
class List<Object>::const_iterator{
public:
	const_iterator():current(NULL){}

	Object & operator* () { return retrieve(); }
	const Object & operator* () const { 
		current = current->next;
		return *this;
	}
	const_iterator operator-- () { 
		current = current->prev;
		return *this;
	}
	const_iterator operator++ (){
		current = current->next;
		return *this;
	}
	const_iterator operator-- (int){
		const_iterator old = *this;
		--( *this );return old;
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
	iterator & operator-- (){
		const_iterator::current = 
			const_iterator::current->prev;
		return *this;
	}	
	iterator & operator++ (){
		const_iterator::current = 
			const_iterator::current->next;
		return *this;
	}
	iterator operator--(int){
		iterator old = *this;
		++( *this );
		return old;
	}
	iterator  operator++ (int) {
		iterator old = *this;
		++( *this );
		return old;
	}
	protected:
	iterator( Node *p ) : const_iterator(p){}
	friend class List<Object>;
};

int main ()
{
	List<int> L;
	for( int i = 0; i < 10; i++ )
		L.push_back( i*i );
	for( int i = 0; i < 10; i++ )
		L.insert( L.end(), i*i );
		

	for( List<int>::iterator it = L.begin(); it != L.end(); it++ )
		std::cout << *it << ' ';
	std::cout << std::endl;
	L.erase( --L.end() );
	
	std::cout << L.size() << std::endl;
	for( List<int>::const_iterator it = L.begin(); it != L.end(); ++it )
		std::cout << *it << ' ';
	std::cout << std::endl;
	return 0;

}
