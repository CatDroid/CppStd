// ���������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "string.h"
#include "stdlib.h"
 
/*

�����������Ӣ�Binary Search Tree����
Ҳ�ƶ�����������
�����������Ӣ�ordered binary tree����
�����������Ӣ�sorted binary tree��

*/

typedef int Type;

typedef struct BSTreeNode {
	Type   key;					// �ؼ���(��ֵ)
	struct BSTreeNode *left;    // ����
	struct BSTreeNode *right;	// �Һ���
	struct BSTreeNode *parent;	// �����
	void * data;				// ָ������ 
}BSNode, *BSTree;



BSNode* createNode(Type key, BSNode *parent, BSNode *left, BSNode* right , void* data ) {
	BSNode* p = (BSNode *)malloc(sizeof(BSNode));
	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;
	return p;
}

BSNode* createEmptyNode(Type key, void* data) {
	BSNode* p = (BSNode *)malloc(sizeof(BSNode));
	p->key = key;
	p->left = NULL;
	p->right = NULL;
	p->parent = NULL;
	p->data = data;
	return p;
}

typedef struct{
	int width;
	int height;
	float size;
	Type key;
} BSData;

BSData* makeData(int w, int h, float s, Type k) {
	BSData* p = (BSData *)malloc(sizeof(BSData));
	p->width = w; p->height = h; p->size = s; p->key = k; 
	return p; 
}


// ǰ�����������������������	
// ǰ�к�  ָʾ ���ڵ��ӡ˳�� 
// ������ ��˳���
void preorder_bstree(BSTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->key); 
		preorder_bstree(tree->left);
		preorder_bstree(tree->right);
	}
}
void inorder_bstree(BSTree tree)
{
	if (tree != NULL)
	{
		inorder_bstree(tree->left);
		printf("%d ", tree->key);
		inorder_bstree(tree->right);
	}
}
void postorder_bstree(BSTree tree)
{
	if (tree != NULL)
	{
		postorder_bstree(tree->left);
		postorder_bstree(tree->right);
		printf("%d ", tree->key);
	}
}


/*
	���tree=NULL ��ǰ�ڵ���Ϊ���ڵ� ������
	���tree!=NULL ���ز���tree  
	
	*/
bool insert(BSTree& tree, Type key, void* data) {
	BSNode* node = createEmptyNode(key, data);

	BSNode* parent = NULL;
	BSNode* nextRoot = tree;
	
	while (nextRoot != NULL) {
		parent = nextRoot;
		if (key >  nextRoot->key) {
			nextRoot = nextRoot->right;
		}
		else if (key < nextRoot->key) {
			nextRoot = nextRoot->left;
		}
		else {
			printf("ERROR: key�ظ���!\n");
			return false ;
		}
	}

	if (parent == NULL ) {
		tree = node;
	} else {
		if ( key > parent->key  ) {
			parent->right = node; 
		} else {
			parent->left = node;
		}
		node->parent = parent;
	}

	return true ;

}

BSNode* max(BSTree tree) {
	if (tree == NULL) return NULL;
	BSNode* next = tree;
	while (next->right != NULL) {
		next = next->right;
	}
	return next;
}

BSNode* min(BSTree tree) {
	if (tree == NULL) return NULL;
	BSNode* next = tree;
	while (next->left != NULL) {
		next = next->left;
	}
	return next;
}

BSNode* search(BSTree tree, Type key) {
	
	BSNode* next = tree;
	while (next != NULL) {
		if (key == next->key   ) {
			return next;
		}else if (key > next->key) {
			next = next->right;
		}else if (key < next->key) {
			next = next->left;
		}
	}
	return NULL;
	
}

void dumpNode(BSNode* node) {
	if (node == NULL) {
		printf("node is null\n");
		return;
	}

	printf("key %d ", node->key );
	BSData* data = (BSData*) (node->data);
	if (data != NULL) {
		printf("width %d height %d size %f\n",  data->width, data->height , data->size );
	}else {
		printf("data = null\n");
	}
}



/*
�ڵ��ǰ�����ڵ�valֵС�ڸýڵ�valֵ����ֵ���Ľڵ� 	(��ʵ��:�൱���������ֵ�� ��һ����ֵ �Ľ��)

�ڵ�ĺ�̣��ڵ�valֵ���ڸýڵ�valֵ����ֵ��С�Ľڵ�	(��ʵ��:�൱���������ֵ�� ��һ����ֵ �Ľ��)
*/

BSNode* beforeOne(BSNode* node) {
	if (node == NULL) return NULL;

	if (node->left != NULL) {
		return max(node->left); // �����ڵ����  ������ļ�ֵ ��һ�� ���� ������������ֵ
	}

	BSNode* c = node;
	BSNode* p = node->parent;
	while (p != NULL && p->right != c) {
		c = p;
		p = p->parent;
	}
	return p; // ����û�� 

/*
	e.g
	30 ��ǰ�� �� 11	 ; 80 (80 ���ҽڵ�) ��ǰ�� �� 64 ;  32 (32 ����ڵ�) ��ǰ���� 30
	30 �ĺ�� �� 32

			  64
			/    \
	  >>>  30      80
		 /    \
	    10     40
		 \    /   \
		 11   35   41
			 /  \
			32   36

	�������������е�ĳ�������������Ů��������û������Ů����ǰ��û������Ů 

ǰ���ڵ�:
	��һ���ڵ�������������ô�ýڵ��ǰ���ڵ�������������valֵ���Ľڵ㣨Ҳ��������������ν��rightMostNode��
	��һ���ڵ�û������������ô�жϸýڵ���丸�ڵ�Ĺ�ϵ
	a. ���ýڵ����丸�ڵ���ұߺ��ӣ���ô�ýڵ��ǰ����㼴Ϊ�丸�ڵ㡣
	b. ���ýڵ����丸�ڵ����ߺ��ӣ���ô��Ҫ�����丸�׽ڵ�һֱ�����Ķ���Ѱ�ң�
	ֱ���ҵ�һ���ڵ�P��P�ڵ����丸�ڵ�Q���ұߺ���  (��32  һֱ�ҵ�30, 40�ĸ��ڵ���30 30���ҽڵ���40)
	��ôQ���Ǹýڵ�ĺ�̽ڵ�

*/

}

BSNode* afterOne(BSNode* node) {

	if (node == NULL) return NULL;

	if (node->right != NULL) {
		return min(node->right);
	}

	BSNode* p = node->parent;
	BSNode* c = node;

	while (p != NULL && p->left != c) {
		p = p->parent;
	}
	return p;
}

// �㷨����  ��12�� ��������� (2)���ҡ�������ɾ��
// http://blog.csdn.net/dc_726/article/details/7391869
//
bool remove(BSTree& tree, Type key ) {
	BSNode* node = search(tree , key );
	if (node == NULL) {
		printf("No Such Key\n");
		return false;
	}

	BSNode* deadone ;
	if (node->left != NULL && node->right != NULL) { 
		deadone =  min(node->right); // ��� 
	} else {
		deadone = node ; 
	}

	BSNode* child = NULL;
	if ( deadone->left != NULL ) {
		child = deadone->left;
	} else {
		child = deadone->right;
	}

	if (child != NULL) {
		child->parent = deadone->parent;
	}
	
	if (deadone->parent != NULL) {
		if (deadone->parent->left == deadone) {
			deadone->parent->left = child;
		} else {
			deadone->parent->right = child;
		}
	} else {
		tree = child;
	}

	if ( deadone != node ){
		node->key = deadone->key; 
		free(node->data);
		node->data = deadone->data;
	} else {
		free(node->data);
	}
	free(deadone);
	 
	/*
			  64
			/    \
	  >>>  30      80
		 /    \
	    10     40
		 \    /   \
		 11   35   41
			 /  \
			32   36
	         \
			  34
	*/

	return true; 
}


void destory(BSTree& tree) {
	if (tree == NULL) return;
	destory( tree->left );
	destory( tree->right );
	printf("Destory:"); dumpNode(tree);
	delete(tree->data);
	delete(tree);
	 
	tree = NULL;
}


int main()
{
	BSNode* root = NULL;

	insert(root,	456 ,	makeData(10, 20, 15.7,  456));
	insert(root,	12 ,	makeData(10, 20, 15.7,	12) );
	insert(root,	500,	makeData(20, 40, 19.7,	500));
	insert(root,	600,	makeData(7,  20, 78.2,	600));
	insert(root,	460,	makeData(99, 2,  68.1,	460 ));
	insert(root,	92,		makeData(3 , 8,  61.1,	92));
	insert(root,	71,		makeData(78, 1,  8.1,	71));
	insert(root,	601,	makeData(34, 7,  9.0,	601));

	inorder_bstree(root); printf("\n");

	
	BSNode* maxOne = max(root);
	printf("max:"); dumpNode(maxOne);
	BSNode* minOne = min(root);
	printf("min:"); dumpNode(minOne);
	BSNode* found = search(root , 92);
	printf("key:"); dumpNode(found);

	found = beforeOne(search(root, 92));
	printf("before 92 :"); dumpNode(found);

	found = beforeOne(search(root, 12));
	printf("before 12 :"); dumpNode(found);

	found = afterOne( search(root, 460) );
	printf("after 460 :"); dumpNode(found);

	found = afterOne(search(root, 456));
	printf("after 456 :"); dumpNode(found);

	remove(root,500);
	inorder_bstree(root); printf("\n");

	remove(root, 456);
	inorder_bstree(root); printf("\n");

	remove(root, 71);
	inorder_bstree(root); printf("\n");

	destory(root);

    return 0;
}

/*
		   456
		/       \ 
	   12       500
	     \     /   \ 
		 92	  460	 600
	     /             \
	   71				601
*/
