#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {

	system("dmesg > test.txt");
	FILE *fp = fopen("test.txt", "r");
	char buf[255];

	while(1) {
		char *p = fgets(buf, 255, fp);
		if (p == NULL) break;
		char *check1 = strstr(p, "sd");
		if (check1  != NULL) {
			char *check2 = strstr(p, "]");
			if ((*(check2-1) -'0') % 2 == 0) {
				printf("%s", p);
			}
		}
	}

	fclose(fp);
	return 0;

}
