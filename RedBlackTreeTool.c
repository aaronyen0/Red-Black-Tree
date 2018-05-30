#include <stdlib.h>
#include "RedBlackTreeTool.h"

sRBNode* gRoot = NULL;

int gCount = 0;

void RemoveTree(){
	sRBNode* node =  gRoot, *next;
	gCount = 0;
	while(node != NULL){
		next = node->left;
		node->left = NULL;
		if(next == NULL){
			next = node->right;
			node->right = NULL;
			if(next == NULL){
				next = node->parent;
				//printf("Count = %d, Free(%d, %d)\n", ++gCount, node->val, (*(int*)node->data));
				free(node);
			}
		}
		node = next;
	}
	gCount = 0;
	gRoot = NULL;
}

int CheckBlackPoint(sRBNode* node){
	int num1, num2;
	if(node == NULL){
		return 1;
	}else{
		num1 = CheckBlackPoint(node->left);
		num2 = CheckBlackPoint(node->right);
		if(num1 != num2){
			printf("num1 != num2\n");
		}else{
			//printf("num1 = num2\n");
			if(node->color == eTreeColor_Black){
				return num1 + 1;
			}else{
				return num1;
			}
		}
	}
	return -1;
}

void PrintTree(sRBNode* node, int level){
	for(int i = 0; i < level; ++i){
		printf("%s", "|  ");
	}

	if(node == NULL){
		printf("%s", "+- ");
		printf("<null>\n");
		return;
	}else{
		printf("%s", "+- ");
		
		if(node->color == eTreeColor_Red){
			printf("<Lv%d, R, %d>\n", level, node->val);
		}else{
			printf("<Lv%d, B, %d>\n", level, node->val);
		}
		PrintTree(node->left, level + 1);
		PrintTree(node->right, level + 1);
		return;
	}
}

sRBNode* CreateRBNode(long long int val, sRBNode* parent){
	sRBNode* node = (sRBNode*)malloc(sizeof(sRBNode));
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->data = NULL;

	node->val = val;
	node->color = eTreeColor_Red;

	return node;
}

sRBNode* Insert(long long int val){
	sRBNode *node = gRoot, *parent = NULL;
	while(node != NULL){
		parent = node;
		if(val < node->val){
			node = node->left;
		}else if(val > node->val){
			node = node->right;
		}else{
			//更新data
			return node;
		}
	}

	node = CreateRBNode(val, parent);
	if(parent == NULL){
		gRoot = node;
	}else{
		if(val < parent->val){
			parent->left = node;
		}else{//(node->val < val){
			parent->right = node;
		}
	}
	Insert_case1(node);
	return node;
}

sRBNode* Grandparent(sRBNode *n){
    return n->parent->parent;
}

sRBNode* Uncle(sRBNode *n){
    if(n->parent == Grandparent(n)->left){
        return Grandparent (n)->right;
	}
    else{
        return Grandparent (n)->left;
	}
}

void Insert_case1(sRBNode *n){
    if(n->parent == NULL){
        n->color = eTreeColor_Black;
	}
    else{
        Insert_case2 (n);
	}
}

void Insert_case2(sRBNode *n){
    if(n->parent->color == eTreeColor_Black){
        return; /* 树仍旧有效*/
	}
    else{
        Insert_case3 (n);
	}
}

void Insert_case3(sRBNode *n){
    if(Uncle(n) != NULL && Uncle (n)->color == eTreeColor_Red) {
        n->parent->color = eTreeColor_Black;
        Uncle (n)->color = eTreeColor_Black;
        Grandparent (n)->color = eTreeColor_Red;
        Insert_case1(Grandparent(n));
    }
    else{
        Insert_case4 (n);
	}
}

void Insert_case4(sRBNode *n){
    if(n == n->parent->right && n->parent == Grandparent(n)->left) {
        Rotate_left(n->parent);
        n = n->left;
    } else if(n == n->parent->left && n->parent == Grandparent(n)->right) {
        Rotate_right(n->parent);
        n = n->right;
    }
    Insert_case5 (n);
}

void Insert_case5(sRBNode *n){
    n->parent->color = eTreeColor_Black;
    Grandparent(n)->color = eTreeColor_Red;
    if(n == n->parent->left && n->parent == Grandparent(n)->left) {
        Rotate_right(Grandparent(n));
    } else {
        /* Here, n == n->parent->right && n->parent == grandparent (n)->right */
        Rotate_left(Grandparent(n));
    }
}


void Rotate_left(sRBNode *p){
	sRBNode *fa = p->parent;
	sRBNode *rc = p->right;
	sRBNode *gs = rc->left;

	if(fa != NULL){
		if(fa->right == p){
			fa->right = rc;
		}else{
			fa->left = rc;
		}
		rc->parent = fa;
	}else{
		gRoot = rc;
		rc->parent = NULL;
	}

	rc->left = p;
	p->parent = rc;

	p->right = gs;
	if(gs != NULL){
		gs->parent = p;
	}
}

void Rotate_right(sRBNode *y){

    sRBNode *x = y->left;           // 把x設成y的leftchild

    y->left = x->right;         // 把x的rightchild放到y的leftchild    
    if (x->right != NULL){           // 若x的rightchild不為NIL, 將其parent指向y
        x->right->parent = y;
    }
    x->parent = y->parent;                // 將x的parent指向原先y的parent
                                          // 以下一組if-else將修改原先y的parent之child
    if (y->parent == NULL){               // 若y原先是root, x將成為新的root
        gRoot = x;          
    }              
    else if (y == y->parent->left){  // 若原先y是其parent之leftchild, 
        y->parent->left = x;         // x就成為其新的parent之leftchild
    }
    else{                                 // 若原先y是其parent之rightchild, 
        y->parent->right = x;        // x就成為其新的parent之rightchild
    }
    x->right = y;                    // 將y設為x之rightchild
    y->parent = x;                        // 將x設為y之parent
}

