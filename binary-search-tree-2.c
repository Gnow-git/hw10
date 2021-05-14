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



typedef struct node {					// Ʈ���� ���� ��� ����ü ����
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20			// ������ �ִ� ����� 20���� ����
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();							// ������ pop�� push�� ���� �Լ�
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20			// ť�� �ִ� ����� 20���� ����
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();						// ť�� deQueue�� enQueue�� ���� �Լ�
void enQueue(Node* aNode);


int initializeBST(Node** h);			// Ʈ�� �ʱ�ȭ

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */		// ��� ȣ���� ���� In order ����Ʈ�� ��ȸ �Լ�
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */		// �ݺ�(����)�� ���� In order ����Ʈ�� ��ȸ �Լ�
void levelOrder(Node* ptr);	          /* level order traversal */			// level ���� ����Ʈ�� ��ȸ �Լ�
int insert(Node* head, int key);      /* insert a node to the tree */		// ��� ���� �Լ�
int deleteNode(Node* head, int key);  /* delete the node for the key */		// ��� ���� �Լ�
int freeBST(Node* head); /* free all memories allocated to the tree */		// ��� �Ҵ� �޸� ���� �Լ�

/* you may add your own defined functions if necessary */


//void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
		printf("\t[-----[�� �� ��]  [2017038100]-----]\n");
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

int initializeBST(Node** h) {					// ����Ʈ�� �ʱ�ȭ

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));			// ��忡 ���� �޸� �Ҵ�
	(*h)->left = NULL;	/* root */				// ���� ��� ���� �����Ƿ� root ����� ���� ��� NULL ����
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;									// ���ÿ� ���� �ʱ� top �� ����

	front = rear = -1;							// ť�� ���� front, rear �� ����

	return 1;
}



void recursiveInorder(Node* ptr)			// ��� ȣ���� ���� ����Ʈ�� ��ȸ
{
	if(ptr == NULL)return;
	else {
		recursiveInorder(ptr->left);		// ���� ���� �̵�
		printf(" [%d] ", ptr->key);			// ���� ���갡 null ��� �ش� ��� key �� ���
		recursiveInorder(ptr->right);		// ������ ����� �̵�
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)			// �ݺ�(����)�� ���� ����Ʈ�� ��ȸ
{
	Node* ptr;								// ptr ��� ����
	top = 0;

	ptr = node;								// ��� �� ptr�� ����
	while(1){
		while(ptr != NULL){
			push(ptr);						// ptr(���) push �� ���� ����� �̵�
			ptr = ptr->left;
		}

		ptr = pop();						// ptr �� null�� ��� pop
		if(ptr == NULL) break;				// pop�Ұ� ���� ��� break
		printf(" [%d] ", ptr->key);			// pop�� ����� �� ���
		ptr = ptr->right;					// ������ ����� �̵�
	}
	
	
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)					// ť�� �̿��Ͽ� ����� ������ ���� ��ȸ�Ǵ� �Լ�
{
	Node* node;
	front;
	rear;

	if(ptr == NULL){						// ��ȸ�� ��尡 ���� ��� return
		return;
	}

	enQueue(ptr);							// ť�� ��Ʈ ��带 �ִ´�.

	while(1) {
		node = deQueue();					// ��带 ��ȯ�Ѵ�.
		if(node == NULL){
			break;
		}

		printf(" [%d] ", node->key);		// ����� �����͸� ���
		if(node->left != NULL){				// ���� ��尡 NULL�� �ƴҰ��
			enQueue(node->left);			// ����� left�� ť�� �ִ´�.
		}
		if(node->right != NULL){			// ������ ��尡 NULL�� �ƴҰ��
			enQueue(node->right);			// ����� right�� ť�� �ִ´�.
	
		}
		
	}

}


int insert(Node* head, int key)					// ��带 �߰��ϴ� �Լ�
{
	Node* newNode = (Node*)malloc(sizeof(Node));		//newNode��� ��� ����
	newNode->key = key;									// �ʱ� �����̹Ƿ� left right NULL ó��
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {						// head�� left�� ���� ��� ���ο� ���� �߰�
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;							// ptr ��带 head->left�� ����Ű�� ������ ����

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
		if(ptr->key < key)							// �Է��� key�� ptr�� key���� Ŭ ��� 
			ptr = ptr->right;						// ptr�� �������� ����Ű�� ���� ptr�� ����
		else
			ptr = ptr->left;						// ptr�� ������ ����Ű�� ���� ptr�� ����
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)						// �θ��� ���� �Է� ������ ū���
		parentNode->left = newNode;					// �θ��� ���ʿ� �� ��� ����
	else
		parentNode->right = newNode;				// �θ��� �����ʿ� �� ��� ����
	return 1;
}


int deleteNode(Node* head, int key)					// ��带 �����ϴ� �Լ�
{
	Node* parent, *p, *succ, *succ_parent;
	Node* child;
	parent = NULL;
	p = head->left;

	while((p != NULL)&&(p-> key != key )){		// ������ ����� ��ġ Ž��
		parent = p;
		if(key < p->key)
			p = p->left;
		else p = p -> right;
	}
	if(p == NULL ){								// ������ ��尡 ���� ���
		printf("No node for key [%d]");
		return 0;
	}

	if((p->left == NULL) && (p-> right == NULL)){	// ������ ��尡 leap ����� ���
		if(parent != NULL){
			if(parent -> left == p)
				parent->left = NULL;
			else parent -> right = NULL;
		}\

		else head = NULL;
	}

	else if((p->left== NULL) || (p->right == NULL)){	// ������ ��尡 �ڽ� ��带 �� �� ������ �ִ� ���
		if(p->left != NULL)								// ������ ��尡 ���� �ڽ� ��带 ������ �ִٸ�
			child = p -> left;							// �����ֱ� ���� ���� �ڽ� ��忡 child�� ����
		else child = p -> right;						// �����ֱ� ���� ������ �ڽ� ��忡 child�� ����no

		if (parent != NULL){
			if (parent -> left == p)
				parent -> left = child;					// ������ ����� �θ� ���� �ڽ� ��带 �����Ѵ�.
			else parent -> right = child;
		}
		else head = child;
	}

	else{												// ������ ��尡 �ڽ� ��带 �� �� ������ �ִ� ���
		succ_parent = p;
		succ = p -> right;								// ������ ����� ������ ���� Ʈ������ Ž�� ����
		while(succ-> left != NULL){						// left ��尡 ���϶����� �ݺ�
			succ_parent = succ;							
			succ = succ -> left;						// ���� �ڽ� ��尡 ���� ��带 ������ succ���� ����(������ ����Ʈ������ ���� ���� ��)
		}
		if(succ_parent -> right == succ)
			succ_parent -> right = succ -> right;			// succ�� ������ ��带 �θ��� ������ ���� �����Ѵ�.
		else
		 succ_parent -> left = succ -> right;			// succ�� ������ ��带 �θ� ���� ��忡 �����Ѵ�.
		p->key = succ->key;								// succ�� ���� p ������ �Ű��ش�
		p = succ;
	}
	free(p);											// �޸� ������ ���� ��� ����
}


void freeNode(Node* ptr)								// Node�� �Ҵ�� �޸𸮸� �����ϴ� �Լ�
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)				// ����Ʈ���� �Ҵ�� �޸� �����ϴ� �Լ�
{

	if(head->left == head)			// ��Ʈ ����ϰ�� ��Ʈ ��带 ����
	{	
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()		// ��� pop�� ���� �Լ�
{
	Node* node = NULL;
	if(top == -2){
		return node;
	}

	node = stack[top];
	top--;
	return node;

}

void push(Node* aNode)	// ��� push�� ���� �Լ�
{
	if(top >= MAX_STACK_SIZE-1){
		return;
	}
	top++;
	stack[top] = aNode;
}



Node* deQueue()						// ���� ť�� ��带 ��ȯ�ϴ� �Լ�
{
	Node* node = NULL;

	if(front == rear){
		return node;
	}

	front++;
	node = queue[front];			// ť�� �ִ� ��带 ��ȯ�Ѵ�.
	return node;
}

void enQueue(Node* aNode)			// ���� ť�� ��带 �����ϴ� �Լ�
{
	if(rear == MAX_QUEUE_SIZE){
		return;
	}
	rear++;
	queue[rear] = aNode;			// ��带 ť�� �ִ´�.
}





