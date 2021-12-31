#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct CharNode
{
    unsigned char character;
    unsigned int frequency;
} CharNode;

typedef struct MinHeapNode
{
    char data;
    unsigned int freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, unsigned freq)
    {
        this->data = data;
        this->freq = freq;
        this->left = this->right = nullptr;
    }
} MinHeapNode;

struct compare
{
    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return (l->freq > r->freq);
    }
};

static bool open_input_file(ifstream &input, const char *inputFileName)
{
    input.open(inputFileName);
    if(!input.is_open())
    {
        return false;
    }
    return true;
}

void get_huffman_code(MinHeapNode *root, string code)
{
    if(!root)
    {
        return;
    }
    if(root->data != '\0')
    {
        cout<<root->data<<" : "<<code<<endl;
    }
    get_huffman_code(root->left, code + "1");
    get_huffman_code(root->right, code + "0");
}

int main(int argc, char const *argv[])
{
    ifstream inputFile;
    if(!open_input_file(inputFile, "input.txt"))
    {
        cout<<"Error: open input file failed!"<<endl;
        return -1;
    }

    char buf = inputFile.get();
    CharNode nodeArr[256] = {{0, 0}};
    while(inputFile.good())
    {
        cout<<buf;
        nodeArr[buf].character = buf;
        nodeArr[buf].frequency ++;
        buf = inputFile.get();
    }
    cout<<endl;

    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    
    for(int idx=0; idx<256; idx++)
    {
        if(nodeArr[idx].frequency>0)
        {
            cout <<"Node "<<idx<<":["<<nodeArr[idx].character<<", "<<nodeArr[idx].frequency<<"]\n";
            MinHeapNode *node = new MinHeapNode(nodeArr[idx].character, nodeArr[idx].frequency);
            minHeap.push(node);
        }
    }

    MinHeapNode *leftNode = nullptr, *rightNode = nullptr, *topNode = nullptr;
    while(minHeap.size()!=1)
    {
        leftNode = minHeap.top();
        minHeap.pop();
        rightNode = minHeap.top();
        minHeap.pop();

        topNode = new MinHeapNode('\0', leftNode->freq + rightNode->freq);
        topNode->left = leftNode;
        topNode->right = rightNode;
        minHeap.push(topNode);
    }
    get_huffman_code(topNode, "");

    inputFile.close();
    return 0;
}
