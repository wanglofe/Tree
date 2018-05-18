#include <stdio.h>
#include <stdlib.h>

typedef int element_t;
#define e_t element_t

// tree *tmp = someval; 修改自身的值
// tree *tmp = root; tmp->right = someval;修改的是数据结构的值(->right是结构本身的值)

//#define _DEBUG

#ifdef _DEBUG
#define DEBUG(fmt, arg...) printf(fmt, ##arg)
#else
#define DEBUG(fmt, arg...)
#endif

typedef struct tree {
	e_t val;
	struct tree *left;
	struct tree *right;
} tree_t;

typedef enum traverse_method {
	PREORDER,
	INORDER,
	POSTORDER
} tm_t;
static void preorder_traverse(tree_t *root);
static void inorder_traverse(tree_t *root);
static void postorder_traverse(tree_t *root);

int tree_insert(tree_t **root, e_t val);
int tree_delete(tree_t **root, e_t val);
int tree_destroy(tree_t **root);
tree_t *tree_find(tree_t *root, e_t val);
void tree_traverse(tree_t *root, tm_t tm);

static void tree_noempty_insert(tree_t *root, tree_t *newnode)
{
	tree_t *current = root;
	while(current) {
		if(newnode->val > current->val) {
			if(!current->right) {
				current->right = newnode;
				break;
			}	
			current = current->right;	
		} else if(newnode->val < current->val) {
			if(!current->left) {
				current->left = newnode;
				break;
			}	
			current = current->left;	
		} else {
			//do nothing		
		} 
	}
}

int tree_insert(tree_t **root, e_t val)
{
	/*create a new node for inserted structure*/
	tree_t *newnode = malloc(sizeof(tree_t));
	if(!newnode) {
		return -1;
	}
	newnode->val = val;
	newnode->left = NULL;
	newnode->right = NULL;
	if(!(*root)) {/*empty tree*/
		*root = newnode;
		DEBUG("[%p]: %d \n", *root, (*root)->val);
	} else {
//		tree_t **link = root;
//		while(*link) {
//			if(val > (*link)->val) {
//				*link = (*link)->right;
//			} else if(val < (*link)->val) {
//				*link = (*link)->left;
//			} else {
//				return -1;
//			}
//		}
//		*link = newnode;
//		DEBUG("[%p]: %d \n", *link, (*link)->val);

//		tree_t *previous = NULL;
//		tree_t *current = *root;
//		while(current) {
//			previous = current;
//			if(val > current->val) {
//				current = current->right;	
//			} else if(val < current->val) {
//				current = current->left;	
//			} else {
//				return -1;
//			} 
//		}
//		previous = newnode;
//		DEBUG("[%p]: %d \n", previous, previous->val);
		
		tree_noempty_insert(*root, newnode);

	}
	DEBUG("root address: %p\n", *root);
	return 0;
}

int tree_isempty(tree_t *root)
{
	return root == NULL;
}

int tree_delete(tree_t **root, e_t val)
{
	if(tree_isempty(*root)) {
		return -1;
	}
	tree_t *position = tree_find(*root, val);
	if(!position) {
		return -1;
	}
	if(!position->right && !position->left) {
			
	}
}

int tree_destroy(tree_t **root)
{
	tree_t *tmp = *root;
	if(*root) {
		if((*root)->right) {
			tree_destroy(&(*root)->right);
		} 
		if((*root)->left) {
			tree_destroy(&(*root)->left);	
		}
		free(tmp);	
	}
	*root = NULL;
}

tree_t *tree_find(tree_t *root, e_t val)
{
	tree_t *tmp = root;
	while(tmp) {
		if(tmp->val == val) {
			return tmp;
		} else if (tmp->val > val) {
			tmp = tmp->left;
		} else {
			tmp = tmp->right;	
		}
	}
	return NULL;
}

static void preorder_traverse(tree_t *root)
{
	tree_t *tmp = root;
	if(tmp) {
		printf("%d ", tmp->val);
		preorder_traverse(tmp->left);
		preorder_traverse(tmp->right);
	}
}

static void inorder_traverse(tree_t *root)
{
	tree_t *tmp = root;
	if(tmp) {
		inorder_traverse(tmp->left);
		printf("%d ", tmp->val);
		inorder_traverse(tmp->right);
	}
}

static void postorder_traverse(tree_t *root)
{
	tree_t *tmp = root;
	if(tmp) {
		postorder_traverse(tmp->left);
		postorder_traverse(tmp->right);
		printf("%d ", tmp->val);
	}
}


void tree_traverse(tree_t *root, tm_t tm)
{
	switch(tm) {
	case PREORDER:
		preorder_traverse(root);
		break;
	case INORDER:
		inorder_traverse(root);
		break;
	case POSTORDER:
		postorder_traverse(root);
		break;
	default:
		break;
	}
	putchar('\n');
}

int main(int argc, char **argv)
{
	tree_t *root;
	int i;
	for(i=0; i<10; i++) {
		tree_insert(&root, i);
	}
	tree_traverse(root, PREORDER);	
	tree_traverse(root, INORDER);	
	tree_traverse(root, POSTORDER);	

	tree_destroy(&root);
	tree_traverse(root, PREORDER);	

	return 0;
}
