//片断1∶数组的间接访问
#include <stdio.h>
#define NUM_KEYS 8
int main() {
	int i,key;
	int key_array[NUM_KEYS];
	int bucket_ptrs[NUM_KEYS];
	int key_buff2[NUM_KEYS];
	int shift = 1;
	for (i = 0; i < NUM_KEYS; i++) {
		key_array[i] = i;
		bucket_ptrs[i] = i;
		key_buff2[i] = 0;
	}
	for (i = 0; i < NUM_KEYS; i++) {
		key = key_array[i];
		key_buff2[bucket_ptrs[key >> shift]++] = key;
	}
	for (i = 0; i < NUM_KEYS; i++) {
		printf("%d  ", key_buff2[i]);
	}
}
//片断2:指针链表
#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct ListNode {
	int  Element;     
	struct ListNode* next;     
}Node, * PNode;
Node* initLink() {
    Node* p = (Node*)malloc(sizeof(Node));//创建一个头结点
    Node* temp = p;//声明一个指针指向头结点，用于遍历链表
    for (int i = 1; i < 10; i++) {
        Node* a = (Node*)malloc(sizeof(Node));
        a->Element = i;
        a->next = NULL;
        temp->next = a;
        temp = temp->next;
    }
    return p;
}
void display(Node* p) {
    Node* temp = p;//将temp指针重新指向头结点
    while (temp->next) {
        temp = temp->next;
        printf("%d  ", temp->Element);
    }
    printf("\n");
}
int selectElem(Node* p, int M) {
    Node* temp;
    for (; p->next; p = p->next) {
        if (p->Element == M) {
            temp = p;
            return 1;
        }
    }
    return -1;
}
int main() {
    printf("初始化链表为：\n");
    Node* p = initLink();
    display(p);
    int temp = selectElem(p, 5);
    if(temp==1)
        printf("已查找到\n");
    else 
        printf("查找失败\n");
}