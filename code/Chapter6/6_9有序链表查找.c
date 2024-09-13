#include<stdio.h>
#include<malloc.h>
#include <sys/time.h>
struct Node {
	int value;
	struct Node* next;//指针指向结构体
};
//使用数组来创建一个链表
struct Node* list_create(int data[], int n) {
		//创建头结点
	struct Node* list = (struct Node*)malloc(sizeof(struct Node));
	struct Node* p = list;
	for (int i = 0; i < n; i++) {
				//创建新节点
		struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
					//设置数据
		tmp->value = data[i];
		p->next = tmp;
		p = p->next;
			}
	p->next = NULL;
	return list;
	}
	int list_search(struct Node* list,int value) {
		struct Node* p;
		for (p = list->next; p; p = p->next) {
				if (p->value == value) {
					return 1;
				}
			}
		return 0;
	}
	void list_visit(struct Node* list) {
		for (struct Node* p = list->next; p; p = p->next) {
			printf("%d ", p->value);
		}
	}
	int main(void) {
		struct timeval start, end;
		int ret;
		int n = 10000000;
		int* num = malloc(n*sizeof(int));
		for (int i = 0; i < n; i++) {
			num[i] = i;
		}
		struct Node* list = list_create(num, n);
		//list_visit(list);
		gettimeofday(&start,NULL);
		ret = list_search(list, n-1);
		if (1 == ret)
			printf("查找成功！");
		else
			printf("查找失败！");
		gettimeofday(&end, NULL);
		double timeuse = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
		printf("time=%f\n", timeuse);
		free(num);
		return 0;
	}