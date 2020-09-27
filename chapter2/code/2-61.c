
#define MASK 0xFF

#define A( x ) (!(~x))
#define B( x ) (!x)

int C ( int x ) {
	return ( x & MASK ) == MASK;
}

int D ( int x ) {
	int shift = ( sizeof ( int ) - 1 ) << 3;
	return ! ( ( x >> shift ) & MASK );
}

