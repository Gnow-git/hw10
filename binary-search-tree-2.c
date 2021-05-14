/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {					// 트리를 위한 노드 구조체 선언
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20			// 스택의 최대 사이즈를 20으로 지정
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();							// 스택의 pop과 push에 대한 함수
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20			// 큐의 최대 사이즈를 20으로 지정
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();						// 큐의 deQueue와 enQueue에 대한 함수
void enQueue(Node* aNode);


int initializeBST(Node** h);			// 트리 초기화

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */		// 재귀 호출을 통한 In order 이진트리 순회 함수
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */		// 반복(스택)을 통한 In order 이진트리 순회 함수
void levelOrder(Node* ptr);	          /* level order traversal */			// level 통한 이진트리 순회 함수
int insert(Node* head, int key);      /* insert a node to the tree */		// 노드 삽입 함수
int deleteNode(Node* head, int key);  /* delete the node for the key */		// 노드 제거 함수
int freeBST(Node* head); /* free all memories allocated to the tree */		// 노드 할당 메모리 해제 함수

/* you may add your own defined functions if necessary */


//void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
		printf("\t[-----[이 명 국]  [2017038100]-----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			//printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {					// 이진트리 초기화

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));			// 노드에 대한 메모리 할당
	(*h)->left = NULL;	/* root */				// 서브 노드 값이 없으므로 root 노드의 왼쪽 노드 NULL 지정
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;									// 스택에 대한 초기 top 값 지정

	front = rear = -1;							// 큐에 대한 front, rear 값 지정

	return 1;
}



void recursiveInorder(Node* ptr)			// 재귀 호출을 통한 이진트리 순회
{
	if(ptr == NULL)return;
	else {
		recursiveInorder(ptr->left);		// 왼쪽 서브 이동
		printf(" [%d] ", ptr->key);			// 왼쪽 서브가 null 경우 해당 노드 key 값 출력
		recursiveInorder(ptr->right);		// 오른쪽 서브로 이동
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)			// 반복(스택)을 통한 이진트리 순회
{
	Node* ptr;								// ptr 노드 생성
	top = 0;

	ptr = node;								// 노드 값 ptr로 지정
	while(1){
		while(ptr != NULL){
			push(ptr);						// ptr(노드) push 후 왼쪽 서브로 이동
			ptr = ptr->left;
		}

		ptr = pop();						// ptr 이 null일 경우 pop
		if(ptr == NULL) break;				// pop할게 없을 경우 break
		printf(" [%d] ", ptr->key);			// pop된 노드의 값 출력
		ptr = ptr->right;					// 오른쪽 서브로 이동
	}
	
	
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)					// 큐를 이용하여 노드의 레벨에 맞춰 순회되는 함수
{
	Node* node;
	front;
	rear;

	if(ptr == NULL){						// 순회할 노드가 없을 경우 return
		return;
	}

	enQueue(ptr);							// 큐에 루트 노드를 넣는다.

	while(1) {
		node = deQueue();					// 노드를 반환한다.
		if(node == NULL){
			break;
		}

		printf(" [%d] ", node->key);		// 노드의 데이터를 출력
		if(node->left != NULL){				// 왼쪽 노드가 NULL이 아닐경우
			enQueue(node->left);			// 노드의 left를 큐에 넣는다.
		}
		if(node->right != NULL){			// 오른쪽 노드가 NULL이 아닐경우
			enQueue(node->right);			// 노드의 right를 큐에 넣는다.
	
		}
		
	}

}


int insert(Node* head, int key)					// 노드를 추가하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));		//newNode라는 노드 생성
	newNode->key = key;									// 초기 생성이므로 left right NULL 처리
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {						// head에 left가 없을 경우 새로운 노드로 추가
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;							// ptr 노드를 head->left가 가리키는 값으로 설정

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)							// 입력한 key가 ptr의 key보다 클 경우 
			ptr = ptr->right;						// ptr의 오른쪽이 가리키는 값을 ptr로 설정
		else
			ptr = ptr->left;						// ptr의 왼쪽이 가리키는 값을 ptr로 설정
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)						// 부모의 값이 입력 값보다 큰경우
		parentNode->left = newNode;					// 부모의 왼쪽에 새 노드 삽입
	else
		parentNode->right = newNode;				// 부모의 오른쪽에 새 노드 삽입
	return 1;
}


int deleteNode(Node* head, int key)					// 노드를 제거하는 함수
{
	Node* parent, *p, *succ, *succ_parent;
	Node* child;
	parent = NULL;
	p = head->left;

	while((p != NULL)&&(p-> key != key )){		// 삭제할 노드의 위치 탐색
		parent = p;
		if(key < p->key)
			p = p->left;
		else p = p -> right;
	}
	if(p == NULL ){								// 삭제할 노드가 없을 경우
		printf("No node for key [%d]");
		return 0;
	}

	if((p->left == NULL) && (p-> right == NULL)){	// 삭제한 노드가 leap 노드인 경우
		if(parent != NULL){
			if(parent -> left == p)
				parent->left = NULL;
			else parent -> right = NULL;
		}\

		else head = NULL;
	}

	else if((p->left== NULL) || (p->right == NULL)){	// 삭제할 노드가 자식 노드를 한 개 가지고 있는 경우
		if(p->left != NULL)								// 삭제할 노드가 왼쪽 자식 노드를 가지고 있다면
			child = p -> left;							// 물려주기 위해 왼쪽 자식 노드에 child로 설정
		else child = p -> right;						// 물려주기 위해 오른쪽 자식 노드에 child로 설정no

		if (parent != NULL){
			if (parent -> left == p)
				parent -> left = child;					// 삭제할 노드의 부모 노드와 자식 노드를 연결한다.
			else parent -> right = child;
		}
		else head = child;
	}

	else{												// 삭제할 노드가 자식 노드를 두 개 가지고 있는 경우
		succ_parent = p;
		succ = p -> right;								// 삭제할 노드의 오른쪽 서브 트리부터 탐색 시작
		while(succ-> left != NULL){						// left 노드가 널일때까지 반복
			succ_parent = succ;							
			succ = succ -> left;						// 왼쪽 자식 노드가 없는 노드를 포인터 succ으로 지정(오른쪽 서브트리에서 가장 작은 값)
		}
		if(succ_parent -> right == succ)
			succ_parent -> right = succ -> right;			// succ의 오른쪽 노드를 부모의 오른쪽 노드와 연결한다.
		else
		 succ_parent -> left = succ -> right;			// succ의 오른쪽 노드를 부모 왼쪽 노드에 연결한다.
		p->key = succ->key;								// succ의 값을 p 값으로 옮겨준다
		p = succ;
	}
	free(p);											// 메모리 해제를 통한 노드 삭제
}


void freeNode(Node* ptr)								// Node에 할당된 메모리를 해제하는 함수
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)				// 이진트리에 할당된 메모리 해제하는 함수
{

	if(head->left == head)			// 루트 노드일경우 루트 노드를 해제
	{	
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()		// 노드 pop에 대한 함수
{
	Node* node = NULL;
	if(top == -2){
		return node;
	}

	node = stack[top];
	top--;
	return node;

}

void push(Node* aNode)	// 노드 push에 대한 함수
{
	if(top >= MAX_STACK_SIZE-1){
		return;
	}
	top++;
	stack[top] = aNode;
}



Node* deQueue()						// 순차 큐에 노드를 반환하는 함수
{
	Node* node = NULL;

	if(front == rear){
		return node;
	}

	front++;
	node = queue[front];			// 큐에 있는 노드를 반환한다.
	return node;
}

void enQueue(Node* aNode)			// 순차 큐에 노드를 삽입하는 함수
{
	if(rear == MAX_QUEUE_SIZE){
		return;
	}
	rear++;
	queue[rear] = aNode;			// 노드를 큐에 넣는다.
}





