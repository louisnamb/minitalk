#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<string.h> 

static void bin2char(int *binary)
{
	int i;
	char sum;
    int placeval;
	sum = 0;
	i = 7;
    placeval = 1;
	while (i >= 0)
	{
        sum += (binary[i]) * placeval;
		placeval = placeval * 2;
        if (i - 1 == 0)
            placeval = -128;
        i--;
    }
	write(1, &sum, 1);
}

int main(void) {
   // char str[5] = "🌍"; // -16:-97:-116:-115 or 11110000 : 10011111 : 10001100 : 10001101
    char str[6] = "Louis"; // 72 01001000
    int num[8] = {0, 1, 0, 0, 1, 1, 0, 0};
    bin2char(num);
    return (0);
}