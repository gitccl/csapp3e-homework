typedef unsigned packet_t;

/**
 * Extract byte from word. Return as signed integer.
 */
int xbyte ( packet_t word , int bytenum ) {
	int w = sizeof ( word );
	int shift = ( w - 1 - bytenum ) << 3;
	/* 先将待提取的字节移到最高位，然后算术右移即可 */
	int x = word << shift;
	return x >> ( ( w - 1 ) << 3 );
}