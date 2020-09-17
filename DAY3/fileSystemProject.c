#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char map[100][12];

void init()
{
	FILE* fp = fopen("nand.txt", "a+");
	fseek(fp, 0, SEEK_END); //파일 포인터를 맨 끝으로 이동
	int size = ftell(fp); //파일 포인터 위치를 리턴

	// 파일이 비어있으면 0을 채워서 출력
	if (size == 0) {
		for (int i = 0; i < 100; i++) {
			fprintf(fp, "0x00000000\n");
		}
	}

	fseek(fp, 0, SEEK_SET); //파일 포인터 다시 맨 위로 이동	
	for (int i = 0; i < 100; i++) { // 맵 배열에 파일을 기록
		fscanf(fp, "%s", map[i]);
	}
	fclose(fp);
}

int main()
//int main(int argc, const char *argv[])
{
	//개발용 Test Code
	int argc = 4;
	//const char* argv[] = { "ssd", "W", "100", "0xAABBCCDD" };
	const char* argv[] = { "ssd", "R", "100"};
	//
	// 유효성 검사
	int ret = isValid(argc, argv);
	if (ret == 0) return -1;

	int isRead = 0;
	int isWrite = 0;
	
	int lba = atoi(argv[2]);
	char data[12] = { 0 };

	// 읽기인지 쓰기인지 확인
	if (!strcmp(argv[1], "R")) isRead = 1;
	if (!strcmp(argv[1], "W")) {
		isWrite = 1;
		strcpy(data, argv[3]);
	}

	//초기화 단계
	init();

	// read or write 수행
	if (isRead == 1) {
		FILE *fp = fopen("result.txt", "r");
		readFromNand(fp, lba); //Read
		fclose(fp);
	}

	if (isWrite == 1) {
		FILE *fp = fopen("nand.txt", "w");		
		writeToNand(fp, lba, data); //Write
		fclose(fp);
	}

	return 0;
}

