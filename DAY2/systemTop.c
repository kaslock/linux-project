#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


float cpuUsage() {

        FILE *fp = fopen("/proc/stat", "r");
        char buf[255];
        fgets(buf, 255, fp);
        char *ptr = strtok(buf, " ");
        int cnt = 0;
        int cpuArr[100];
        while(ptr != NULL) {
            cpuArr[cnt] = atoi(ptr);
            ptr = strtok(NULL, " ");
       	    cnt++;
       	}
        int cpuTotal = cpuArr[1] + cpuArr[2] + cpuArr[3] + cpuArr[4];
        int cpuUsed = cpuArr[1] + cpuArr[2] + cpuArr[3];
		
	fclose(fp);
	float cpuRate = cpuUsed*100.0 / cpuTotal;
	return cpuRate;
}

float memoryUsage() {
	
	FILE *fp = fopen("/proc/meminfo", "r");
        char buf[255];
	
	fgets(buf, 255, fp);
  	char *ptr1 = strtok(buf, " ");
	ptr1 = strtok(NULL, " ");	
        int memTotal = atoi(ptr1);

	fgets(buf, 255, fp);
        char *ptr2 = strtok(buf, " ");
        ptr2 = strtok(NULL, " ");
	int memFree = atoi(ptr2);

        fclose(fp);

	float memRate = (memTotal - memFree)*100.0 / memTotal;
	return memRate;
}

float diskUsage() {

	system("df | grep sda1 > ./infos/diskusage.txt");
	FILE *fp = fopen("./infos/diskusage.txt", "r");
        char buf[255];
        fgets(buf, 255, fp);
	int cnt = 0;
	int diskArr[100];
        char *ptr = strtok(buf, " ");

	while(ptr != NULL) {
            diskArr[cnt++] = atoi(ptr);
            ptr = strtok(NULL, " ");
        }

	return diskArr[4];

} 
int main() {

	while(1) {
		
		system("clear");
		
		float cpu = cpuUsage();
		float mem = memoryUsage();
		float disk = diskUsage();


		printf("CPU USAGE   : [");
		for (int i = 0; i < 100; i++) {
			if (cpu - i > 0) printf("#");
			else printf("-");
		}
		printf("] %.2f%% \r\n", cpu);
		printf("MEMORY USAGE: [");
		for (int i = 0; i < 100; i++) {
                        if (mem - i > 0) printf("#");
                        else printf("-");
                }
		printf("] %.2f%% \r\n", mem);
		printf("DISK USAGE  : [");
		for (int i = 0; i < 100; i++) {
                        if (disk - i > 0) printf("#");
                        else printf("-");
                }
		printf("] %.2f%% \r\n", disk);
		
		sleep(1);

	}
	return 0;
}
