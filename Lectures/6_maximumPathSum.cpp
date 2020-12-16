//We traverse the tree and keep track at each node whether the left path or the right path leads to a higher sum.
//The maximum path connects two leaf nodes via an ancestor of them. Based on that observation we update the max
//Since each node of the tree is visited only once the complexity is O(n)
int maxPath(Node* node,int* max){
    if(node == NULL){
return std::numeric_limits<int>::min();
    }
    
    int leftPath=maxPath(node->left,max);
    int rightPath=maxPath(node->right,max);
    
    if(leftPath==std::numeric_limits<int>::min() && rightPath==std::numeric_limits<int>::min()){
            return node->data;
}

//    *max=currPath>*maxcurrPath:*max;
    
        if(leftPath!=std::numeric_limits<int>::min() && rightPath!=std::numeric_limits<int>::min()){

    int maxCurrent=node->data+leftPath+rightPath;
    *max=maxCurrent>*max?maxCurrent:*max;
        }
        
            int currPath=node->data;
    currPath+=leftPath>rightPath?leftPath:rightPath;
        return currPath;
}

int maxPathSum(Node* root)
{ 

int max=std::numeric_limits<int>::min();
maxPath(root,&max);
    return max;
}