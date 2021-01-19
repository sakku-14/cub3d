#include <stdio.h>

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int main()
{
	int trgb = create_trgb(100, 200, 30, 255);
	printf("%x\n", trgb);
	printf("%x\n", get_t(trgb));
	printf("%x\n", get_r(trgb));
	printf("%x\n", get_g(trgb));
	printf("%x\n", get_b(trgb));
}
