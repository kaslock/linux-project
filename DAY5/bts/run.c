#include <stdio.h>
#include "coco.h"

int main()
{
	for(int i = 0; i < 10; i++) {
		printf("%d %d", sum(i, i), sum(i * 2, i * 2));
		printf("\n");
	}

	return 0;
}

