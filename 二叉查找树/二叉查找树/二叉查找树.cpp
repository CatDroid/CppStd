// 二叉查找树.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "string.h"
#include "stdlib.h"
 
/*

二叉查找树（英语：Binary Search Tree），
也称二叉搜索树、
有序二叉树（英语：ordered binary tree），
排序二叉树（英语：sorted binary tree）

*/

typedef int Type;

typedef struct BSTreeNode {
	Type   key;					// 关键字(键值)
	struct BSTreeNode *left;    // 左孩子
	struct BSTreeNode *right;	// 右孩子
	struct BSTreeNode *parent;	// 父结点
	void * data;				// 指向数据 
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

/* 二叉树的基本的遍历规则有三种：前序遍历，中序遍历和后序遍历 
	 定义:
	 http://www.itzhai.com/preorder-binary-tree-traversal-inorder-traversal-and-postorder-traversal-of-algorithm-2.html#read-more
	 前序遍历在第一次遇到结点时立即访问，中序遍历第二次遇到结点时访问，后序遍历则到第三次遇到结点时才访问。
	 前序遍历：根左右   中序遍历：左根右   后序遍历：左右根
	 规律：
		1.前序 第一个元素是 根节点
		2.中序 根节点元素 前面的元素是位于 左子树   后面的元素是位于 右子树
		3.前序 第二个元素是 左子树的根节点   
		4.前序 左子树元素的 下一个元素 是 右子树的根节点

		5.其他元素  在前序 AB  中序 BA  那么A是根节点 B是A的左节点

	练习：从前序和中序 得到 后序
	https://www.nowcoder.com/questionTerminal/d06c0640861a4523a6edec11512200bd
*/


// 前序遍历、中序遍历、后序遍历	
// 前中后  指示 根节点打印顺序 
// 中序是 有顺序的
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
	如果tree=NULL 当前节点作为根节点 并返回
	如果tree!=NULL 返回参数tree  
	
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
			printf("ERROR: key重复了!\n");
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
节点的前驱：节点val值小于该节点val值并且值最大的节点 	(其实是:相当于这个结点键值的 上一个键值 的结点)

节点的后继：节点val值大于该节点val值并且值最小的节点	(其实是:相当于这个结点键值的 下一个键值 的结点)
*/

BSNode* beforeOne(BSNode* node) {
	if (node == NULL) return NULL;

	if (node->left != NULL) {
		return max(node->left); // 如果左节点存在  这个结点的键值 上一个 就是 左子树的最大键值
	}

	BSNode* c = node;
	BSNode* p = node->parent;
	while (p != NULL && p->right != c) {
		c = p;
		p = p->parent;
	}
	return p; // 可能没有 

/*
	e.g
	30 的前继 是 11	 ; 80 (80 是右节点) 的前继 是 64 ;  32 (32 是左节点) 的前继是 30
	30 的后继 是 32

			  64
			/    \
	  >>>  30      80
		 /    \
	    10     40
		 \    /   \
		 11   35   41
			 /  \
			32   36

	如果二叉查找树中的某个结点有两个子女，则其后继没有左子女，其前趋没有右子女 

前驱节点:
	若一个节点有左子树，那么该节点的前驱节点是其左子树中val值最大的节点（也就是左子树中所谓的rightMostNode）
	若一个节点没有左子树，那么判断该节点和其父节点的关系
	a. 若该节点是其父节点的右边孩子，那么该节点的前驱结点即为其父节点。
	b. 若该节点是其父节点的左边孩子，那么需要沿着其父亲节点一直向树的顶端寻找，
	直到找到一个节点P，P节点是其父节点Q的右边孩子  (如32  一直找到30, 40的父节点是30 30的右节点是40)
	那么Q就是该节点的后继节点

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

// 算法导论  第12章 二叉查找树 (2)查找、插入与删除
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
		deadone =  min(node->right); // 后继   就是与当前node的value值 最接近的node
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
	
	if (deadone->parent != NULL) {	// 更新parent的 left或者right 
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
