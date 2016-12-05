/* HW6 read cafefully and follow all the instructions/comments
this program compiles and runs as is although it's not doing much.
DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
numbers but we want the same numbers for comparison purposes.

FLOATING point radix sort requires some substantial changes to this code
float n, lst[N],tmp[N];
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 100		/* default 100 elements */
//#define N 1048576		/* 2^30 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
#define N 33554432

void selection_sort();

void merge_sort();
void msort_recursive();

void int_radix_sort();
void float_radix_sort();
void swap();
void self_check();

//int rand(void);
//void srand();
//int rand_r();
void init_lst();
void print_lst();

int n, lst[N], tmp[N];

int main(int argc, char **argv) {

	long int del_sec, del_msec;
	struct timeval tv_s, tv_e;

	if (argc>1) n = atoi(argv[1]);
	else n = NELM;
	printf("n=%d\n", n);
	init_lst(lst, n);
	//print_lst(lst,n);

	int c=3;
	if(argc>2)c=atoi(argv[2]);
	
	gettimeofday(&tv_s, NULL);
	if(c==1)selection_sort(lst, n);
	if(c==2)merge_sort(lst,tmp,n);
	if(c==3)int_radix_sort(lst,tmp,n);
	//  float_radix_sort(lst,tmp,n);
	gettimeofday(&tv_e, NULL);

	/****
	PRINT elapsed time in sec and milli secs
	****/
	del_sec=tv_e.tv_sec-tv_s.tv_sec;
	del_msec=tv_e.tv_usec-tv_s.tv_usec;
	printf("elapsed time: %ldsec and %ld microsec (%ld microsec)\n",del_sec,del_msec,del_sec*1000000+del_msec);

	//print_lst(lst,n);
	printf("start checking...");
	self_check(lst, n);
	return 0;
}

void selection_sort(int list[], int n){
	// fill here
	int i,j;
	for(j=n;j>0;j--){
		for(i=1;i<j;i++){
			if(list[i-1]>list[i]){
				swap(list,i-1,i);
			}
		}
	}
}

void merge_sort(int list[], int temp[], int n){
	msort_recursive(list, temp, 0, n - 1);
}

//use recursion
void msort_recursive(int list[], int temp[], int left, int right){
	// fill here
	if(left>=right)return;
	int middle=(right+left)/2;
	msort_recursive(list,temp,left,middle);
	msort_recursive(list,temp,middle+1,right);
	int i,j=left,k=middle+1;
	for(i=left;i<=right;i++){
		if(!(k<=right)||(j<=middle && list[j]<list[k])){
			temp[i]=list[j];
			j++;
		}
		else{
			temp[i]=list[k];
			k++;
		}
	}
	for(i=left;i<=right;i++)list[i]=temp[i];
}

//fix the bucket size to 256. run 4 passes where each pass processes 8 bits
//use lst and tmp only. do not use any more memory of size n.
void int_radix_sort(int list[],int temp[],int n) {
	int group = 8;			/* 8 bits per pass (or round) */
	int bucket = 1 << group;	/* number of buckets = 256 */
	// fill here
	int mask=/*bucket-1*/0xFF;
	int cnt[bucket],map[bucket];
	int i,pass;
	for(pass=0;pass<32;pass+=group){
		for(i=0;i<bucket;i++)cnt[i]=0;
		for(i=0;i<n;i++)cnt[(list[i]>>pass)&mask]++;
		map[0]=0;
		for(i=1;i<bucket;i++)map[i]=map[i-1]+cnt[i-1];
		for(i=0;i<n;i++)temp[map[(list[i]>>pass)&mask]++]=list[i];
		for(i=0;i<n;i++)list[i]=temp[i];
	}
	int neg_index;
	for(i=0;i<n;i++){
		if(list[i]<0){
			neg_index=i;
			break;
		}
	}
	for(i=0;i<n;i++){
		if(i<neg_index)temp[n-neg_index+i]=list[i];
		else temp[i-neg_index]=list[i];
	}
	for(i=0;i<n;i++)list[i]=temp[i];
}

void print_lst(int *l, int n){
	int i;
	for (i = 0; i<n; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");
}

void init_lst(int *l, int n){
	int i;
	//  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
	//  printf ("seed=%d\n", seed);
	srand(1234);			/* SEED */
	for (i = 0; i<n; i++) {
		if(i%2)l[i] = rand();
		else l[i] = -rand();
	}
}

void self_check(int *list, int n) {
	int i, j, flag = OK, *listp;

	listp = list;
	for (i = 0; i<n - 1; i++)
	if (listp[i] > listp[i + 1]) { flag = NOK; break; }

	if (flag == OK) printf("sorted\n");
	else printf("NOT sorted at %d\n", i);
}

void swap(int list[], int index1, int index2){
	int temp=list[index1];
	list[index1]=list[index2];
	list[index2]=temp;
}
