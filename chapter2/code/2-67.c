
int bad_int_size_is_32 () {
	int set_msb = 1 << 31;
	int beyond_msb = 1 << 32;
	return set_msb && ! beyond_msb;
}

/** 1
 *  int beyond_msb = 1 << 32;
 *  当int位32位时，左移32位超过了最大左移宽度，实际为 1 << (32 % 32) = 1 << 0 = 1
 */

/**
 * 判断 int 是否为32位
 * 该函数在 int 至少为32位的任何机器上都能正确地运行。
 */
int int_size_is_32 () {
	int set_msb = 1 << 31;
	int beyond_msb = set_msb << 1;
	return set_msb && ! beyond_msb;
}

/**
 * 判断 int 是否为32位
 * 该函数在 int 至少为16位的任何机器上都能正确地运行。
 */
int int_size_is_32_in16 () {
	/* 由于int可能为16位，因此最多只能左移15位 */
	int set_msb = ( ( 1 << 15 ) << 15 ) << 1;
	int beyond_msb = set_msb << 1;
	return set_msb && ! beyond_msb;
}