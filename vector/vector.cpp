#include<iostream>
#include<algorithm>
template<typename Object>
class Vector{
private:
	int theSize; //the elements it contains
	int theCapacity;
	Object *objects;
public:
	explicit Vector( int initSize = 0 ):
		theSize( initSize ),theCapacity( initSize + SPACE_CAPACITY ){
		objects = new Object[ theCapacity ]; 
	}
	Vector( const Vector & rhs ):objects( NULL ){
		operator=( rhs );
	}//copy constructor
	~Vector(){
		delete [] objects;
	}

	const Vector & operator= ( const Vector & rhs ){
		if( this != &rhs ){
			delete [] objects;
			theSize = rhs.size();
			theCapacity = rhs.capacity();

			objects = new Object[ capacity() ];
			for( int k = 0; k < theSize; k++ ) 
				objects[k] = rhs.objects[k];
		}
		return *this;
	}// above is the "big three"

	void resize( int newSize ){
		if( newSize > theCapacity )
			reserve( newSize*2 + 1 ); //in case the size is 0
		theSize = newSize;
	}

	void reserve( int newCapacity ){
		if( newCapacity < theSize ) return;

		Object *oldArray = objects;
		objects = new Object[ newCapacity ];
		for( int k = 0; k < theSize; k++ )
			objects[k] = oldArray[k];
		theCapacity = newCapacity;
		delete [] oldArray;
	}

	Object & operator[] ( int index ) { return objects[ index ]; }
	const Object & operator[] ( int index ) const { return objects[ index ]; }
	
	bool empty() const { return size() == 0; }
	int size() const { return theSize; }
	int capacity() const { return theCapacity; }

	void push_back( const Object & x ){
		if( theSize == theCapacity )
			reserve( 2*theCapacity + 1 );
		objects[ theSize++ ] = x;
	}

	void pop_back() { theSize--; }
	const Object & back() const { return objects[ theSize-1 ]; }

	typedef Object * iterator;//use native pointer as iterator
	typedef const Object * const_iterator;

	iterator begin() { return &objects[0]; }
	const_iterator begin() const { return &objects[0]; }
	iterator end()	 { return &objects[ theSize ]; }
	const_iterator end()   const { return &objects[ theSize ]; }
	
	enum{ SPACE_CAPACITY = 16 };
};

int main() {
	
	Vector<int> V;
	for( int i = 0; i < 100; i++ )
		V.push_back( i );
	V.push_back(1);
	
	const Vector<int> v( V );
	std::sort(V.begin(), V.end());
	for( Vector<int>::const_iterator it = V.begin(); 
			it != V.end(); it++ )
		std::cout << *it << std::endl;
	return 0;
}
