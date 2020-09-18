#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		printf("The number of parameter is not 2.\n");
		return 1;
	}

	char buf1[255];
	char buf2[255];
	sprintf(buf1, "echo %s/*.c > cfiles", argv[1]);
	system(buf1);

	FILE *fp = fopen("cfiles", "r");
	fgets(buf1, 255, fp);
	
	sprintf(buf2, "echo \"ADD_EXECUTABLE(gogo %s)\" > CMakeLists.txt", buf1);
	system(buf2);
	system("cmake ./CMakeLists.txt");
	system("make");
	system("./gogo");
	
	return 0;
}
