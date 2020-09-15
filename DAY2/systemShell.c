#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {

	char *prompt = "SSAFY #";
	
	system("cat /proc/cpuinfo > ./infos/cpuinfo.txt");
	system("cat /proc/meminfo > ./infos/meminfo.txt");
	system("cat /proc/scsi/scsi > ./infos/diskinfo.txt");

	char buf[255];
	char buf2[255];
	do {
		printf("%s", prompt);
		scanf("%s", buf);

		if (strcmp(buf, "list") == 0) {
			printf("cpu\r\nmemory\r\ndisk\r\nexit\r\n");
		}

		if (strcmp(buf, "cpu") == 0) {
        	FILE *fp = fopen("./infos/cpuinfo.txt", "r");
			while(1) {
				char *p = fgets(buf2, 255, fp);
				if (p == NULL) break;
				if (strstr(p, "cores")) printf("%s", p);
				if (strstr(p, "MHz")) printf("%s", p);
			}
			fclose(fp);
       	 }

		if (strcmp(buf, "memory") == 0) {
        	FILE *fp = fopen("./infos/meminfo.txt", "r");
         	while(1) {
                char *p = fgets(buf2, 255, fp);
                if (p == NULL) break;
                if (strstr(p, "MemTotal")) printf("%s", p);
                if (strstr(p, "MemFree")) printf("%s", p);
            }   
			fclose(fp);
	   	}

		if (strcmp(buf, "disk") == 0) {
        	FILE *fp = fopen("./infos/diskinfo.txt", "r");
        	while(1) {
                char *p = fgets(buf2, 255, fp);
                if (p == NULL) break;
                if (strstr(p, "Model")) printf("%s", p);
            }       
			fclose(fp);
        }

		if (strcmp(buf, "exit") == 0) {
			system("toilet -f mono12 -F metal bye");
			exit(1);
		}

	} while(1);

	return 0;
}
