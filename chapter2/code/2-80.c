#include <limits.h>

int threefourths(int x) {
	int former = x & ~0x3;
	int later = x & 0x3;

	/* former / 4 * 3 */
	former >>= 2;
	former = (former << 1) + former;

	/* later * 3 / 4 */
	later = (later << 1) + later;
	int neg = x & INT_MIN;
	neg && (later += (1 << 2) - 1);
	later >>= 2;

	return former + later;
}