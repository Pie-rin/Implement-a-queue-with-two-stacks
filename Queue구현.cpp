/*<기존의 스택코드>, <새로운 queue코드>, <main함수> 순으로 작성한 프로그램.
  스택 2개를 이용하여 <새로운 queue코드>를 작성함*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  //=====스택코드 시작=====
#define MAX_STACK_SIZE 100
#define STRING_SIZE 20	//문자열의 크기

typedef struct {	//element 정의
	char str[STRING_SIZE];	//char타입 배열(string)을 가지고 있음
} element;

//이하 교재와 같음
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

//스택 초기화 함수
void init_stack(StackType* s) {
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(StackType* s) {
	return (s->top == -1);
}

//포화 상태 검출 함수
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

//삽입함수
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

//삭제함수
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

//피크함수
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
//=====스택코드의 끝=====


//=====스택 2개를 이용한 큐 코드 시작=====
typedef struct {
	StackType s1, s2;
} MyQueueType;

//큐 초기화 함수
void init_queue(MyQueueType* q) {
	q->s1.top = -1;
	q->s2.top = -1;
}

//큐 출력함수
void queue_print(MyQueueType* q) {
	MyQueueType q_sample = { q->s1 , q->s2 };	//q를 q_sample에 복사함

	printf("스택#1이 가지고 있는 데이터:\n");
	while (!is_empty(&(q_sample.s1))) {	//s1이 빌 때까지
		printf("%s\n", pop(&(q_sample.s1)).str);	//s1을 pop하여 출력한다.
	}

	printf("스택#2가 가지고 있는 데이터:\n");
	while (!is_empty(&(q_sample.s2))) {	//s2가 빌 때까지
		printf("%s\n", pop(&(q_sample.s2)).str);	//s2을 pop하여 출력한다.
	}
	printf("=========================\n");
}

//큐 삽입함수
void queue_push(MyQueueType* q, element item) {
	push(&(q->s1), item);	//요소 삽입
	printf("Queue에 \'%s\' 입력\n\n", item.str);
	queue_print(q);	//출력함수를 호출한다.
}

//큐 삭제함수
element queue_pop(MyQueueType* q) {
	if (is_empty(&(q->s2))) {	//s2가 비어있다면
		while (!is_empty(&(q->s1))) {	//s1이 빌 때까지
			push(&(q->s2), pop(&(q->s1)));	//s1을 pop하여 s2에 차례대로 넣는다.
		}
	}
	element item = pop(&(q->s2));
	printf("Queue에서 \'%s\' 출력\n\n", item.str);
	queue_print(q);	//출력함수를 호출한다.
	return item;
}
//=====스택 2개를 이용한 큐 코드 끝=====


int main(void) {
	MyQueueType q;
	init_queue(&q);	//큐 초기화

	//queue에 넣을 element들을 미리 배열로 만든다.
	element capital[10] = { "서울", "예루살렘", "타이베이", "싱가포르", "암스테르담",
						"베를린", "로마", "파리", "오슬로", "프라하" };

	//push, pop 반복
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