/**
 * 用逻辑右移实现算术右移
 * 将xsra的高k位置零即可
 */
unsigned srl ( unsigned x , int k ) {
	unsigned xsra = ( int ) x >> k;
	/* 将 xsra 的高k位置零 */
	int w = sizeof ( x ) << 3;
	unsigned mask = ~ ( ( (int) -1 ) << ( w - k ) );
	return xsra & mask;
}

/**
 * 用算术右移实现逻辑右移
 * 如果x >= 0, 答案就是xsrl
 * 如果x <= 0, 将xsrl的高k位置1
 */
int sra ( int x , int k ) {
	int xsrl = ( unsigned ) x >> k;
	int w = sizeof ( x ) << 3;

	/* 构造一个mask, 如果x >= 0, mask = 0; 否则mask的高k位为1 */
	unsigned mask = ( ( (int) -1 ) << ( w - k ) ) ;
	int msb = ( x & (1 << (w - 1)) );
	mask &= (!msb) - 1;
	return xsrl | mask;
}