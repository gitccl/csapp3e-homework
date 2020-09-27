#include <stdint.h>


/**
 * 设 x′ 和 y′ 分别是 x 和 y 的无符号类型值.
 * 书上的公式2-18如下
 * x' * y' = x*y + (x_{w-1}*y + y_{w-1}*x)*2^w + (x_{w-1}*y_{w-1})*2^{2w}
 * 由于取得是高w位，因此一个数乘于2^w, 那么这个数就处于高w位中。同时2^{2w}不会改变位的表示
 * 因此答案就是 signed_high_prod(x, y) + x_{w-1}*y + y_{w-1}*x
 */
unsigned unsigned_high_prod ( unsigned x , unsigned y ) {
	int w = sizeof(x) << 3;
	int sign_x = x >> ( w - 1 ) ;	// x_{w-1}
	int sign_y = y >> ( w - 1 ) ;    // y_{w-1}

	/* 后面两个乘法不用可以不用加(int)y * sign_x， sign_x要么为0要么为1 */
	return signed_high_prod ( ( int ) x , ( int ) y ) + y * sign_x + x * sign_y;
}

/**
 * 下面两个函数用于对拍
 */
int signed_high_prod( int x, int y) {
	int64_t mul = (int64_t) x * y;
	return mul >> 32;
}


unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
	uint64_t mul = (uint64_t) x * y;
	return mul >> 32;
}