/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/

static int getmax(Node* root)
{
    int r = root->data;
    if (root->left) {
        int left = getmax(root->left);
        if (left < 0) {
            // problem detected lower down
            return -1;
        }
        if (left >= root->data) {
            return -1;
        }
    }
    if (root->right) {
        int right = getmax(root->right);
        if (right < 0) {
            // problem detected lower down
            return -1;
        }
        if (right <= root->data) {
            return -1;
        }
        r = right;
    }
    return r;
}

static int getmin(Node* root)
{
    int r = root->data;
    if (root->left) {
        int left = getmin(root->left);
        if (left < 0) {
            // problem detected lower down
            return -1;
        }
        if (left >= root->data) {
            return -1;
        }
        r = left;
    }
    if (root->right) {
        int right = getmin(root->right);
        if (right < 0) {
            // problem detected lower down
            return -1;
        }
        if (right <= root->data) {
            return -1;
        }
    }
    return r;
}

bool checkBST(Node* root) {
    if (getmin(root) < 0) {
        return false;
    }
    if (getmax(root) < 0) {
        return false;
    }
    return true;
}
