/**
 * Return 1 when x can be represented as an n-bit, 2's-complement
 * number; 0 otherwise
 * Assume 1 <= n <= w
 * 例如n=8, 从截断的角度考虑.
 * int转为char值不变, 即 (char)x == x;
 * 对于任意的n，将x截断为n位后仍然和x相等，那么x就能用n位的二进制补码表示
 * 截断为n位就是 x << (w - n) >> (w - n)。(算术右移，不会改变原来的值)
 */
int fits_bits_1 ( int x , int n ) {
	int w = sizeof ( x ) << 3;
	int t = ( ( x << ( w - n ) ) >> ( w - n ) );
	return t == x;
}

/**
 * 再次的观察后可发现，x 能用 n 位的二进制补码表示的条件为
 * x 的前 w - n + 1 位要么全为 1, 要么全为 0.
 */
int fits_bits_2 ( int x , int n ) {
	int t = x >> ( n - 1 );
	return ! t || ! ~ t;
}

/**
 * 函数是正确的，但不符合条件，可以用于对拍。
 */
int fits_bits_3 ( int x , int n ) {
	int low = - ( 1U << ( n - 1 ) );
	int up = ( 1U << ( n - 1 ) ) - 1;
	return x >= low && x <= up;
}