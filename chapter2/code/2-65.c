
/**
 * Return 1 when x contains an odd number of 1s; 0 otherwise. Assume w=32.
 * 通过不断的异或来消除偶数个1
 */
int odd_ones ( unsigned x ) {
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return x & 0x1;
}
