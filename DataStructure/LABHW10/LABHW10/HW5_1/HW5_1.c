//HW5_1 20191023 �ֿ��� ��ǻ���а� 2�г�
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


// ���� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}
// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.
// ���� �Լ�
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void preorder(HeapType *h, int root)
{
	if (root <= h->heap_size ) {
		printf("%d ", h->heap[root].key);  // ��� �湮
		preorder(h, root * 2);// ���ʼ���Ʈ�� ��ȸ
		preorder(h, root * 2 + 1);// �����ʼ���Ʈ�� ��ȸ
	}
}

void print_heap(HeapType *h)
{
   int i, level = 1;
   
   for (i = 1; i <= h->heap_size; i++)
   {
      if (i == level)
      {
         printf("\n");
         level *= 2;
      }
      printf("%d ", h->heap[i].key);
   }
   printf("\n");
}


int find(HeapType *h, int root, int key)
{
   if (root <= h->heap_size) 
   {
      if (h->heap[root].key == key)
         return root;
      else
         return find(h, root + 1, key);
   }
   return 0;
}

void print_sorted_value(HeapType heap)
{
   element heapList[MAX_ELEMENT];
   HeapType *h;
   int i;

   h = create();
   init(h);

   for (i = 1; i <= heap.heap_size; i++)
      insert_max_heap(h, heap.heap[i]);

   for (i = 1; i <= heap.heap_size; i++)
      heapList[i] = delete_max_heap(h);

   for (i = 1; i <= heap.heap_size; i++)
      printf("%d ", heapList[i].key);
   printf("\n");
}

void modify_priority(HeapType *h, int oldkey, int newkey)
{
   int parent, child, index;
   element temp;

   index = find(h, 1, oldkey);
   h->heap[index].key = newkey;

   parent = index;
   child = index * 2;

   while (child <= h->heap_size)
   {
      if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
         child++;
      temp = h->heap[parent];
      h->heap[parent] = h->heap[child];
      h->heap[child] = temp;
      parent = child;
      child *= 2;
   }
}

int main(void)
{
	 element e1={10}, e2={5}, e3={30}, eA = {9}, eB = {19}, eC = {39};
	 element e4, e5, e6;
	 int index;
	 int key, oldKey, newKey;
	 HeapType heap; // ���� ����

	 init(&heap); // �ʱ�ȭ

	 printf("Step1: ���Ե� 10, 5, 30 �� �߰������� 9, 19, 39 �� <����> �Ѵ�");
	 insert_max_heap(&heap, e1);
	 insert_max_heap(&heap, e2);
	 insert_max_heap(&heap, e3);
	 insert_max_heap(&heap, eA);
	 insert_max_heap(&heap, eB);
	 insert_max_heap(&heap, eC);

	 printf("\nStep2: preorder, print_heap �Լ� �׽�Ʈ\n");
	 preorder(&heap, 1);
	 printf("\n\n");

	 print_heap(&heap);
	 e4 = delete_max_heap(&heap);
	 printf("\n����: ��Ʈ�� ������\n", e4.key);
	 print_heap(&heap);

	 printf("\nStep3: find �Լ� �׽�Ʈ\n");
	 printf("ã�� key �Է�(-1 for exit):");
	 scanf("%d", &key);
	 
	while (key != -1) {
		if ((index = find(&heap, 1, key)) == 0)
			printf("%d �� ����\n", key);
		 else
			 printf("%d �� [%d]�� ����\n", key, index);
		 printf("ã�� key �Է�(-1 for exit):");
		 scanf("%d", &key);
	 }

	 printf("\nStep4: print_sorted_value �Լ� �׽�Ʈ\n");
	 print_sorted_value(heap);

	 printf("\nStep5: modify_priority �Լ� �׽�Ʈ\n");
	 printf("�ٲ� key �Է�(-1 for exit):");
	 scanf("%d", &oldKey);
	 while (oldKey != -1) {
		 printf("�� key �Է�:");
		 scanf("%d", &newKey);
		 modify_priority(&heap, oldKey, newKey);
		 print_heap(&heap);
		 printf("�ٲ� key �Է�(-1 for exit):");
		 scanf("%d", &oldKey);
	 }
	
} 