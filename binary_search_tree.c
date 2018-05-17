#include <stdio.h>
#include <stdlib.h>

typedef int element_t;
#define e_t element_t

typedef struct ll {
	e_t val;
	struct ll *left;
	struct ll *right;
} tree_t;

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
	} else {
	//	tree_t *previous = NULL;
	//	tree_t *current = *root;
	//	while(current) {/*find the position to insert*/
	//		previous = current;
	//		if(val > current->val) {
	//			current = current->right;
	//		} else if (val < current->val) {
	//			current = current->left;
	//		} else { /* val is already in tree*/
	//			return -1;	
	//		}
	//	}
	//	previous = newnode;
		tree_t **link = root;
		while(*link) {
			if(val > (*link)->val) {
				*link = (*link)->right;
			} else if(val < (*link)->val) {
				*link = (*link)->left;
			} else {
				return -1;
			}
		}
		*link = newnode;
	}
	return 0;
}

int tree_delete(e_t val)
{

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

void tree_print(tree_t *root)
{

}

int main(int argc, char **argv)
{
	return 0;
}
