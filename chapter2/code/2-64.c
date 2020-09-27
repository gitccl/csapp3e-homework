/**
 * Return 1 when any odd bit of x equals 1; 0 otherwise. Assume w=32
 */
int any_odd_one(unsigned x){
	/* 假设最低位为第0位 */
	return (x & 0xAAAAAAAA) != 0;
}