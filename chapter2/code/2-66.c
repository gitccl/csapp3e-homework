/*
 * Generate mask indicating leftmost 1 in x. Assume w=32
 * For example, 0xFF00 -> 0x8000, and 0x6000 -> 0x4000.
 * If x = 0, then return 0
 */
int leftmost_one(unsigned x){
	/* 将x的最高非零位至最低为都置为1. 如 0x6000 -> 0x7FFF
	 * 然后取 x ^ (x >> 1)就能将最高位后的所有1置0
	 */
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x ^ (x >> 1);
}