/**
 * Do rotating left shift. Assume O <= n < w
 * Examples when x = 0x12345678 and w = 32:
 * n=4 -> 0x23456781, n=20 -> 0x67812345
 * 循环左移n位
*/
unsigned rotate_left(unsigned x, int n){
	int w = sizeof(int) << 3;
	return x << n | (x >> (w - n - 1) ) >> 1  ;
}