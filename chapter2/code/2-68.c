
/**
 * 编写一个函数，生成一个掩码，将其最低 n 位置为 1 。其中 1 ≤ n ≤ w 。注意 n=w 的情况。
 */
int lower_one_mask(int n) {
	int w = sizeof(int) << 3;
	return ((unsigned) -1) >> ( w - n );
}