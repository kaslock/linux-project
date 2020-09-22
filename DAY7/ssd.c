#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 

int main(int argc, const char* argv[]) { 
	
	char buf[100][12] = {0, };

	// valid check
	int valid = 1;

	int isRead = 0;
	int isWrite = 0;
	
	if (argc < 3) {
		printf("Too few parameters\n");
		return 1;
	}
	if (!strcmp(argv[1], "R") && argc == 3) isRead = 1;
	if (!strcmp(argv[1], "W") && argc == 4) isWrite = 1;

	int lba = atoi(argv[2]);
	
	if ((lba < 0 && lba >= 100) || (!isRead && !isWrite)) {
		printf("Invalid parameters\n");
		return 1;
	}
	
	// buffer init
	for (int i = 0; i < 100; i++)
		strcpy(buf[i], "0x00000000");

	FILE *nand = fopen("nand.txt", "r");
	if (nand == NULL) {
		system("touch nand.txt");
		nand = fopen("nand.txt", "w");
		for (int i = 0; i < 100; i++)
			fprintf(nand, "%s\n", buf[i]);
		printf("Make Nand\n");
		return 1;
	}
	
	for (int i = 0; i < 100; i++)
		fscanf(nand, "%s", buf[i]);
	
	if (isRead) {
		system("touch result.txt");
		FILE *fp = fopen("result.txt", "w");
		fprintf(fp, "[%d] %s\n", lba, buf[lba]);
		fclose(fp);
	}

	if (isWrite) {
		nand = fopen("nand.txt", "w");
		strcpy(buf[lba], argv[3]);
		for (int i = 0; i < 100; i++)
			fprintf(nand, "%s\n", buf[i]);
	}

	fclose(nand);
	return 0;
}
