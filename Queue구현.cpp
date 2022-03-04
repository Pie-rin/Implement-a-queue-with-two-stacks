/*<������ �����ڵ�>, <���ο� queue�ڵ�>, <main�Լ�> ������ �ۼ��� ���α׷�.
  ���� 2���� �̿��Ͽ� <���ο� queue�ڵ�>�� �ۼ���*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  //=====�����ڵ� ����=====
#define MAX_STACK_SIZE 100
#define STRING_SIZE 20	//���ڿ��� ũ��

typedef struct {	//element ����
	char str[STRING_SIZE];	//charŸ�� �迭(string)�� ������ ����
} element;

//���� ����� ����
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

//���� �ʱ�ȭ �Լ�
void init_stack(StackType* s) {
	s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(StackType* s) {
	return (s->top == -1);
}

//��ȭ ���� ���� �Լ�
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

//�����Լ�
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

//�����Լ�
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

//��ũ�Լ�
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
//=====�����ڵ��� ��=====


//=====���� 2���� �̿��� ť �ڵ� ����=====
typedef struct {
	StackType s1, s2;
} MyQueueType;

//ť �ʱ�ȭ �Լ�
void init_queue(MyQueueType* q) {
	q->s1.top = -1;
	q->s2.top = -1;
}

//ť ����Լ�
void queue_print(MyQueueType* q) {
	MyQueueType q_sample = { q->s1 , q->s2 };	//q�� q_sample�� ������

	printf("����#1�� ������ �ִ� ������:\n");
	while (!is_empty(&(q_sample.s1))) {	//s1�� �� ������
		printf("%s\n", pop(&(q_sample.s1)).str);	//s1�� pop�Ͽ� ����Ѵ�.
	}

	printf("����#2�� ������ �ִ� ������:\n");
	while (!is_empty(&(q_sample.s2))) {	//s2�� �� ������
		printf("%s\n", pop(&(q_sample.s2)).str);	//s2�� pop�Ͽ� ����Ѵ�.
	}
	printf("=========================\n");
}

//ť �����Լ�
void queue_push(MyQueueType* q, element item) {
	push(&(q->s1), item);	//��� ����
	printf("Queue�� \'%s\' �Է�\n\n", item.str);
	queue_print(q);	//����Լ��� ȣ���Ѵ�.
}

//ť �����Լ�
element queue_pop(MyQueueType* q) {
	if (is_empty(&(q->s2))) {	//s2�� ����ִٸ�
		while (!is_empty(&(q->s1))) {	//s1�� �� ������
			push(&(q->s2), pop(&(q->s1)));	//s1�� pop�Ͽ� s2�� ���ʴ�� �ִ´�.
		}
	}
	element item = pop(&(q->s2));
	printf("Queue���� \'%s\' ���\n\n", item.str);
	queue_print(q);	//����Լ��� ȣ���Ѵ�.
	return item;
}
//=====���� 2���� �̿��� ť �ڵ� ��=====


int main(void) {
	MyQueueType q;
	init_queue(&q);	//ť �ʱ�ȭ

	//queue�� ���� element���� �̸� �迭�� �����.
	element capital[10] = { "����", "����췽", "Ÿ�̺���", "�̰�����", "�Ͻ��׸���",
						"������", "�θ�", "�ĸ�", "������", "������" };

	//push, pop �ݺ�
	queue_push(&q, capital[0]);
	queue_push(&q, capital[1]);
	queue_pop(&q);
	queue_push(&q, capital[2]);
	queue_push(&q, capital[3]);
	queue_push(&q, capital[4]);
	queue_push(&q, capital[5]);
	queue_pop(&q);
	queue_pop(&q);
	queue_push(&q, capital[6]);
	queue_pop(&q);
	queue_push(&q, capital[7]);
	queue_push(&q, capital[8]);
	queue_push(&q, capital[9]);
	queue_pop(&q);
	queue_pop(&q);
	queue_pop(&q);
	queue_pop(&q);
	queue_pop(&q);
	queue_pop(&q);

	return 0;
}