#include <vector>
#include <unordered_map>

class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }
    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution {
public:
    Node* cloneGraph(Node* node) {
        
        if(!node)
        {
            return nullptr;
        }
        
        Node *newNode = new Node(node->val);
        
        m_copyOfNode.insert({node, newNode});   // Mark this node as visited, and store the copy
        
        for(Node *node_ : node->neighbors)
        {
            if(m_copyOfNode.count(node_) == 0)  // If this neighbor has not been visited
            {
                newNode->neighbors.emplace_back(cloneGraph(node_)); 
            }
            else
            {
                // Note this is different than traversal, we still need to add the copy of visited node to the adjacency list, while in traversal we simply skip visited node
                newNode->neighbors.emplace_back(m_copyOfNode[node_]);   
            }

        }
        return newNode;
    }
    
private:
    std::unordered_map<Node *, Node *> m_copyOfNode;
};