/* We traverse the tree and keep track at each node whether the left path or the
 * right path leads to a higher sum. The maximum path connects two leaf nodes
 * via an ancestor of them. Based on that observation we update the max. Since
 * each node of the tree is visited only once the complexity is θ(n). Space
 * complexity is θ(n).
 */

#include <numeric>

// { Driver Code Starts
#include <bits/stdc++.h>

using namespace std;

// Tree Node
struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int val) {
    data = val;
    left = right = NULL;
  }
};

// Function to Build Tree
Node *buildTree(string str) {
  // Corner Case
  if (str.length() == 0 || str[0] == 'N')
    return NULL;

  // Creating vector of strings from input
  // string after spliting by space
  vector<string> ip;

  istringstream iss(str);
  for (string str; iss >> str;)
    ip.push_back(str);

  // Create the root of the tree
  Node *root = new Node(stoi(ip[0]));

  // Push the root to the queue
  queue<Node *> queue;
  queue.push(root);

  // Starting from the second element
  int i = 1;
  while (!queue.empty() && i < ip.size()) {

    // Get and remove the front of the queue
    Node *currNode = queue.front();
    queue.pop();

    // Get the current Node's value from the string
    string currVal = ip[i];

    // If the left child is not null
    if (currVal != "N") {

      // Create the left child for the current Node
      currNode->left = new Node(stoi(currVal));

      // Push it to the queue
      queue.push(currNode->left);
    }

    // For the right child
    i++;
    if (i >= ip.size())
      break;
    currVal = ip[i];

    // If the right child is not null
    if (currVal != "N") {

      // Create the right child for the current Node
      currNode->right = new Node(stoi(currVal));

      // Push it to the queue
      queue.push(currNode->right);
    }
    i++;
  }

  return root;
}

int maxPathSum(Node *);

int main() {
  int tc;
  scanf("%d ", &tc);
  while (tc--) {
    string treeString;
    getline(cin, treeString);
    Node *root = buildTree(treeString);
    cout << maxPathSum(root) << "\n";
  }
  return 0;
} // } Driver Code Ends

int maxPath(Node *node, int *max) {
  if (node == NULL) {
    return std::numeric_limits<int>::min();
  }

  int leftPath = maxPath(node->left, max);
  int rightPath = maxPath(node->right, max);

  if (leftPath == std::numeric_limits<int>::min() &&
      rightPath == std::numeric_limits<int>::min()) {
    return node->data;
  }

  //    *max=currPath>*maxcurrPath:*max;

  if (leftPath != std::numeric_limits<int>::min() &&
      rightPath != std::numeric_limits<int>::min()) {

    int maxCurrent = node->data + leftPath + rightPath;
    *max = maxCurrent > *max ? maxCurrent : *max;
  }

  int currPath = node->data;
  currPath += leftPath > rightPath ? leftPath : rightPath;
  return currPath;
}

int maxPathSum(Node *root) {

  int max = std::numeric_limits<int>::min();
  maxPath(root, &max);
  return max;
}
