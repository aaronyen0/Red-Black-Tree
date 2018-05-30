#pragma once

enum eTreeColor{eTreeColor_Red, eTreeColor_Black};

typedef struct RBNode{
	long long int val;
	eTreeColor color;
	void* data;
	struct RBNode* parent;
	struct RBNode* left;
	struct RBNode* right;
}sRBNode;



void RemoveTree();
int CheckBlackPoint(sRBNode* node);
void PrintTree(sRBNode* node, int level);
sRBNode* CreateRBNode(long long int val, sRBNode* parent);
sRBNode* Insert(long long int val);

sRBNode* Grandparent(sRBNode *n);
sRBNode* Uncle(sRBNode *n);
void Insert_case1(sRBNode *n);
void Insert_case2(sRBNode *n);
void Insert_case3(sRBNode *n);
void Insert_case4(sRBNode *n);
void Insert_case5(sRBNode *n);
void Rotate_right(sRBNode *p);
void Rotate_left(sRBNode *p);
