/*
Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.

The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        GetSum(root);
        std::vector<int> sums;
        for(auto &sum : m_sumOfSubtrees)
        {
            if(sum.second == maxCount)
            {
                sums.emplace_back(sum.first);
            }
        }
        return sums;
    }
    
private:
    int maxCount = 0;
    std::unordered_map<int, int> m_sumOfSubtrees;
    
    int GetSum(TreeNode *root)
    {
        if(!root)
        {
            return 0;
        }
        
        int sum = root->val + GetSum(root->left) + GetSum(root->right);
        
        m_sumOfSubtrees[sum]++;
        
        maxCount = max(maxCount, m_sumOfSubtrees[sum]);
        
        return sum;
    }
    
};