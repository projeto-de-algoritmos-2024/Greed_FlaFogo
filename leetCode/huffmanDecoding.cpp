// } Driver Code Ends
/*
Structure of the node of Huffman tree is as
struct MinHeapNode
{
    char data;
    int freq;
    MinHeapNode *left, *right;
};
*/

class Solution {
  public:
    string decodeHuffmanData(struct MinHeapNode* root, string binaryString) 
    {   
        MinHeapNode* current = root;
        string result;
        for(char i : binaryString)
        {
            
            if(i == '0')
            {
                current = current -> left;
            }
            else
                current = current -> right;
            
            if(current -> left == NULL and current -> right == NULL)
            {
                result += current -> data;
                current = root;
                continue;
            }
        }
        
        return result;
    }
};