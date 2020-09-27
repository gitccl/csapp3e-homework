int float_le(float x, float y)
{
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);

	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;

	/**
	 * +0 and -0
	 * x <= 0 && y >= 0
	 * x >= 0 && y >= 0 && ux <= uy
	 * x < 0 && y < 0 && ux >= uy
	 */
	return  ((ux << 1) == 0 && (uy << 1) == 0) || 	//
		  	(sx && !sy) ||							//
			(!sx && !sy && ux <= uy) ||				//
			(sx && sy && ux >= uy) ;				//
}

unsigned f2u(float x)
{
	return *(unsigned *)&x;
}