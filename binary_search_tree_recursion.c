// Author:	Kevin
// Date:	20180520


#include <stdio.h>
#include <stdlib.h>

typedef int element_t;
#define e_t element_t

typedef struct tree {
	e_t val;
	struct tree *left;
	struct tree *right;
} tree_t;

typedef enum {
	PREORDER,
	INORDER,
	POSTORDER
} traverseMethod_t;
#define tm_t traverseMethod_t

#define error(s) fprintf(stdout, "[%s]: %s\n", __func__, s)

#define debug(fmt, arg...) printf(fmt, ##arg)

tree_t 	*tree_insert(tree_t *root, e_t val);
tree_t 	*tree_delete(tree_t *root, e_t val);
void 	tree_destroy(tree_t *root);
tree_t 	*tree_find(tree_t *root, e_t val);
void 	tree_print(tree_t *root, tm_t method);
tree_t 	*tree_findMin(tree_t *root);
tree_t 	*tree_findMax(tree_t *root);

static void tree_preOrderTraverse(tree_t *root);
static void tree_inOrderTraverse(tree_t *root);
static void tree_postOrderTraverse(tree_t *root);

int main(int argc, char **argv)
{
	tree_t *root = NULL;
	
	int i;
	for(i=0; i<10; i++) 
		root = tree_insert(root, i);
	tree_print(root, PREORDER);
	tree_print(root, INORDER);
	tree_print(root, POSTORDER);
	
	tree_t *cell;
	cell = tree_findMin(root);
	printf("min address: %p\n", cell);
	cell = tree_findMax(root);
	printf("max address: %p\n", cell);
	cell = tree_find(root, 5);
	printf("val 5 address: %p\n", cell);

	root = tree_delete(root, 6);
	tree_print(root, INORDER);
	root = tree_delete(root, 6);
	
	cell = tree_find(root, 6);
	printf("val 6 address: %p\n", cell);

	tree_destroy(root);
	tree_print(root, INORDER);
	return 0;
}


tree_t *tree_insert(tree_t *root, e_t val)
{
	if(!root) {
		root = malloc(sizeof(tree_t));
		if(!root) {
			error("error malloc");
			exit(-1);
		}
		root->val = val;
		root->left = NULL;
		root->right = NULL;
		debug("tree_insert: %p, %d\n", root, root->val);	
	}
	else if(root->val > val) {
		root->left = tree_insert(root->left, val);
	}
	else {
		root->right = tree_insert(root->right, val);
	}
	return root;
}

tree_t *tree_delete(tree_t *root, e_t val)
{
	if(!root) {
		error("element no found");
	}
	else if(root->val > val) {
		root->left = tree_delete(root->left, val);
	}
	else if(root->val < val) {
		root->right = tree_delete(root->right, val);
	}
	else {//found it here
		if(root->left && root->right) {//two children
			tree_t *cell = tree_findMin(root->right);
			root->val = cell->val;
			root->left = cell->left;
			root->right = tree_delete(root->right, cell->val);	
		}
		else {//one or zero child
			tree_t *cell = root;
			if(!root->left && !root->right) {
				root = NULL;
			} 
			else if(root->left){
				root = root->left;	
			}
			else {
				root = root->right;
			}
			free(cell);
		}
	}
	return root;
}

void tree_destroy(tree_t *root)
{
	if(root) {
		if(root->left) {
			tree_destroy(root->left);
		}
		if(root->right) {
			tree_destroy(root->right);
		}
		free(root);
	}
}

tree_t *tree_find(tree_t *root, e_t val)
{
	if(!root) {
		return NULL;
	}
	if(root->val == val) {
		return root;
	}
	else if(root->val > val) {
		root = tree_find(root->left, val);
	} 
	else {
		root = tree_find(root->right, val);
	} 
	return root;
}

void tree_print(tree_t *root, tm_t method)
{
	switch(method) {
		case PREORDER:
			fprintf(stdout, "[preorder]: ");
			tree_preOrderTraverse(root);
			break;
		case INORDER:
			fprintf(stdout, "[inorder]: ");
			tree_inOrderTraverse(root);
			break;
		case POSTORDER:
			fprintf(stdout, "[postorder]: ");
			tree_postOrderTraverse(root);
			break;
		default:
			error("no such order");
			break;
	}
	putchar('\n');
}

tree_t *tree_findMin(tree_t *root)
{
	if(!root) {
		return NULL;
	}
	while(root->left) {
		root = root->left;
	}	
	return root;
}

tree_t *tree_findMax(tree_t *root)
{
	if(!root) {
		return NULL;
	}
	if(!root->right){
		return root;
	} 
	else {
		root = tree_findMax(root->right);	
	}
	return root;
}

static void tree_preOrderTraverse(tree_t *root)
{
	if(root) {
		fprintf(stdout, "%d ", root->val);
		tree_preOrderTraverse(root->left);
		tree_preOrderTraverse(root->right);
	}
}

static void tree_inOrderTraverse(tree_t *root)
{
	if(root) {
		tree_preOrderTraverse(root->left);
		fprintf(stdout, "%d ", root->val);
		tree_preOrderTraverse(root->right);
	}
}

static void tree_postOrderTraverse(tree_t *root)
{
	if(root) {
		tree_preOrderTraverse(root->left);
		tree_preOrderTraverse(root->right);
		fprintf(stdout, "%d ", root->val);
	}
}
