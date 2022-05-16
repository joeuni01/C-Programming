//HW5_2 20191023 최영린 컴퓨터학과 2학년
/*
read_heap(HeapType *h, char *filename) - 파일에서 읽어서 max Heap 에 저장한다.
write_heap_array(HeapType *h, char *filename) - max Heap 에 저장된 내용을 배열적 표현 그대로 파일에
출력한다.
write_descending_order(HeapType *h, char *filename) - max Heap 에 저장된 내용을 내림차순으로 파일에
출력한다. 
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;


// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void read_heap(HeapType *h, char *filename)
{
   // 필요한 변수
   int n;
   element new_;
   FILE *fp = fopen(filename, "r");
   if (fp == NULL) {
      fprintf(stderr, "파일 %s을 열 수 없음!\n", filename); return;
   }
   // 구현: while (fscanf(fp, "%d\n", &n) != EOF) {...} 을 사용한다.
   while (fscanf(fp, "%d\n", &n) != EOF)
   {
      new_.key = n;
      insert_max_heap(h, new_);
   }
   fclose(fp); 
}

void write_heap_array(HeapType *h, char *filename)
{
   // 필요한 변수
   FILE *fp;
   int i;
   if (filename == NULL) fp = stdout;
   else 
      fp = fopen(filename, "w");
   // 구현: fprintf(fp, "%d\n", ...)을 사용한다
   for (i = 1; i <= h->heap_size; i++)
      fprintf(fp, "%d\n", h->heap[i]);
}

int main(void)
{
	HeapType heap;
	element e1 = {20}, e2 = {40};
	init(&heap);
	read_heap(&heap, "input.txt");
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	write_heap_array(&heap, "heapArray.txt");
	//write_descending_order(&heap, "sorted.txt");
}