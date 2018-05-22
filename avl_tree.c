#include <stdio.h>
#include <stdlib.h>

#define error(s) fprintf(stdout, "[%s]: %s\n", __func__, s)
#define max(a,b) (a)>(b)?(a):(b)

typedef int e_t;
typedef struct avl {
	e_t val;
	struct avl *left;
	struct avl *right;
	int height;
} avl_t;

int main(int argc, char *argv)
{

}

static int Height(avl_t *node)
{
	if(!node) {
		return -1;//empty
	}
	else {
		return node->height;	
	}
}

// This function can be called only if K2 has a left child
// Perform a rotate between a node(K2) and its left child
// update heights, then return new root
static avl_t *singleRotateWithLeft(avl_t *K2)
{
	avl_t *K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(Height(K2->left), Height(K2->right)) + 1;	
	K1->height = max(Height(K1->left), K2->height) + 1;	
	return K1;//new root
}

static avl_t *singleRotateWithRight(avl_t *K2)
{

}


// This function can be called only if K3 has a left
// child and K3 s left child has a right child
// Do the left-right double rotation
// Update heights, then return new root
static avl_t *doubleRotateWithRight(avl_t *K3)
{
	// rotate between K1 and K2
	K3->left = singleRotateWithRight(K3->left);
	// rotate between K3 and K2
	return singleRotateWithLeft(K3);
}

static avl_t *doubleRotateWithLeft(avl_t *K3)
{

}

avl_t *avl_insert(avl_t *root, e_t val)
{
	if(!root) {
		root = malloc(sizeof(avl_t));	
		if(!root) {
			error("error malloc");
			return NULL;
		}
		root->val = val;
		root->left = NULL;
		root->right = NULL;
		root->height = 0;
	}
	else if(root->val > val) {//left insert
		root->left = avl_insert(root->left, val);
		//rebalance tree if necessary
		if(Height(root->left)-Height(root->right) == 2){
			if(root->left->val > val/*root->left->left*/) {
				root = singleRotateWithLeft(root);
			} 
			else {
				root = doubleRotateWithLeft(root);	
			}
		}
	}
	else if(root->val < val) {//insert right
		root->right = avl_insert(root->right, val);	
		//rebalance tree if necessary
		if(Height(root->right)-Height(root->left) == 2){
			if(root->right->val < val) {
				root = singleRotateWithRight(root);
			} 
			else {
				root = doubleRotateWithRight(root);	
			}
		}
	}
	else {
		//do nothing
	}
	root->height = max(Height(root->left), Height(root->right)) + 1;

	return root;
}
