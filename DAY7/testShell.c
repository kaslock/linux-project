#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int dataValid(char data[]) {
	
	int valid = 1;

	if (strlen(data) != 10) valid = 0;
	else if (data[0] != '0') valid = 0;
	else if (data[1] != 'x') valid = 0;
  
	for (int i = 2; i < strlen(data); i++) {
		if (data[i] >= '0' && data[i] <= '9') continue;
		if (data[i] >= 'A' && data[i] <= 'F') continue;
		valid = 0;
	}

	return valid;

}

void write(int lba, char data[]) {

	int valid = 1;
	char buf[100];

	valid = dataValid(data);
	if (lba < 0 || lba > 99) valid = 0;
	if (valid == 0) {
		printf("INVALID COMMAND\n");
		return;
	}
	sprintf(buf, "./ssd W %d %s", lba, data);
	system(buf);

}

void read(int lba) {

	int valid = 1;
	char buf[100];

	if (lba < 0 || lba > 99) valid = 0;
	if (valid == 0) {
                printf("INVALID COMMAND\n");
        	return;
        }
	sprintf(buf, "./ssd R %d", lba);
	system(buf);
	system("cat result.txt");

}

int main() {

	char *prompt = "TESTSHELL > ";
	char command[20];
	char buf[255];
	int lba;
	int valid;
	char data[20];
	do {
		printf("%s", prompt);
		scanf("%s", command);
		
		if (!strcmp(command, "write")) {
			scanf("%d %s", &lba, data);
			write(lba, data);
		}

		else if (!strcmp(command, "read")) {
			scanf("%d", &lba);
			read(lba);
		} 

		else if (!strcmp(command, "exit")) { break; }

		else if (!strcmp(command, "help")) {
			printf("Write     : write lba(0~99) data(0x00000000~0xFFFFFFFF)\n");
			printf("Read      : read lba(0~99)\n");
			printf("Exit      : exit\n");
			printf("Help      : help\n");
			printf("Fullwrite : fullwrite data(0x00000000~0xFFFFFFFF)\n");
			printf("Fullread  : fullread\n");
		} 

		else if (!strcmp(command, "fullwrite")) {
			scanf("%s", data);
			for (int i = 0; i < 100; i++) {
				write(i, data);
			}
		} 

		else if (!strcmp(command, "fullread")) {
			system("cat nand.txt");	
		}

		else if (!strcmp(command, "testapp1")) {
			// fullwrite
			for (int i = 0; i < 100; i++) {
				write(i, "0xFFFFFFFF");
			}
			// fullread
			system("cat nand.txt");	
		}

		else if (!strcmp(command, "testapp2")) {
			for (int i = 0; i < 6; i++) write(i, "0xAAAABBBB");
			for (int i = 0; i < 6; i++) write(i, "0x12345678");
			for (int i = 0; i < 6; i++) read(i);
		}

		else { printf("INVALID COMMAND\n"); }

	} while(1);

	return 0;
}
