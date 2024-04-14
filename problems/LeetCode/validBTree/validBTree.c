#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

bool isValidBSTactual(struct TreeNode* root, int64_t min, int64_t max)
{
    if (root == NULL)
        return true;

    if (!(root->val > min) || !(root->val < max))
        return false;
    
    return (isValidBSTactual(root->right, root->val, max) && isValidBSTactual(root->left, min, root->val));
}

bool isValidBST(struct TreeNode* root) 
{
    return isValidBSTactual(root, INT64_MIN, INT64_MAX);
}

int main() { return 0; }
