#include<stdio.h>

int main(int argc, char *argv[]){	//char **argv
	typedef unsigned int INT;
	INT mask = 255;	//11111111 = FF
	int cnt = 0, len = 0;
	while (cnt<argc){
		if (!*((*argv) + len++)){
			cnt++;
		}
	}
	int tmp = len % 4;
	char tmp2;
	printf("       +------+------+------+------+ FFFFFFFF\n");
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+         \n");
	if (tmp){
		printf("       |");
		for (int i = 0; i < 4 - tmp; i++){
			printf(" s.t. |");
		}
		for (int i = 0; i < tmp; i++){
			if (tmp2 = *((*argv) + --len))
				printf("  %c   |", tmp2);
			else
				printf("  \\0  |");
		}
		printf(" %08x\n", *(argv)+len);
		printf("       +------+------+------+------+         \n");
	}
	for (; len>0;){
		printf("       |");
		for (int i = 0; i < 4; i++){
			if (tmp2 = *((*argv) + --len))
				printf("  %c   |", tmp2);
			else
				printf("  \\0  |");
		}
		printf(" %08x\n", *(argv)+len);
		printf("       +------+------+------+------+         \n");
	}
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+         \n");
	for (int i = argc - 1; i >= 0; i--){	//argv==&argv[0]==argv+0
		printf("argv+%d |  %02x  |  %02x  |  %02x  |  %02x  | %08x\n", i, (INT)*(argv+i)>>24&mask, (INT)*(argv+i)>>16&mask, (INT)*(argv+i)>>8&mask, (INT)*(argv+i)&mask, argv+i);
		printf("       +------+------+------+------+         \n");
	}
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+         \n");
	printf("argv   |  %02x  |  %02x  |  %02x  |  %02x  | %08x\n", (INT)argv>>24&mask, (INT)argv>>16&mask, (INT)argv>>8&mask, (INT)argv&mask, &argv);
	printf("       +------+------+------+------+         \n");
	printf("argc   |  %02x  |  %02x  |  %02x  |  %02x  | %08x\n", (INT)argc>>24&mask, (INT)argc>>16&mask, (INT)argc>>8&mask, (INT)argc&mask, &argc);
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+         \n");
	printf("       +------+------+------+------+ 00000000\n");
	return 0;
}