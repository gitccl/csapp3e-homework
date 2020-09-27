#include <limits.h>
/* Divide by power of 2. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
	int neg = x & INT_MIN;
	neg && (x += (1 << k) - 1);
	return x >> k;
}