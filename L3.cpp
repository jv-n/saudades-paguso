#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

class Node
{
	public:
	int key;
	int peso;
	int rank;
	Node *left;
	Node *right;
	int height;
};

int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

Node* newNode(int key, int wei)
{
	Node* node = new Node();
	node->key = key;
	node->peso = wei;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}

Node *rotate_right(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	y->rank -= x->peso;
	y->rank -= x->rank;

	x->right = y;
	y->left = T2;


	y->height = max(height(y->left),
					height(y->right)) + 1;
	x->height = max(height(x->left),
					height(x->right)) + 1;


	return x;
}

Node *rotate_left(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;


	y->left = x;
	x->right = T2;

	x->height = max(height(x->left),
					height(x->right)) + 1;
	y->height = max(height(y->left),
					height(y->right)) + 1;

	y->rank += x->peso;
	y->rank += x->rank;

	return y;
}

int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key, int wei)
{
	if (node == NULL)
		return(newNode(key, wei));

	if (key < node->key)
	{
		node->rank+=wei;
		node->left = insert(node->left, key, wei);
	}
	else if (key > node->key)
		node->right = insert(node->right, key, wei);
	else node->peso+=wei;

	node->height = max(height(node->left),
						height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rotate_right(node);

	if (balance < -1 && key > node->right->key)
		return rotate_left(node);

	if (balance > 1 && key > node->left->key)
	{
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

int ranking (Node *root, int id)
{
	Node* cur = root;

	while(cur->key!=id)
	{
		if(cur->key>id && cur->left!= NULL)
		{
			cur = cur->right;
		}
		if(cur->key<id && cur->right!= NULL)
		{
			cur = cur->left;
		}
		if(cur->key>id && cur->left== NULL)
		{
			return 0;
		}
		if(cur->key<id && cur->right== NULL)
		{
			return 0;
		}
	}

	return (cur->rank);
}

void weifunc (Node* root, int id, int height)
{
	Node* cur = root;
	bool entro;

	while(cur->key!=id)
	{
		if(cur->key>id && cur->left != NULL)
		{
			height++;
			cur = cur->left;
		}
		else if(cur->key<id && cur->right != NULL)
		{
			height++;
			cur = cur->right;
		}
		else if(cur->key>id && cur->right == NULL)
		{
			height = -1;
			cout << "0 " << height << endl;
			entro = true;
			break;
		}
		else if(cur->key<id && cur->left == NULL)
		{
			height = -1;
			cout << "0 " << height << endl;
			entro = true;
			break;
		}
	}

	if(cur->key == id)
	{
		cout << cur->peso << " " << height << endl;
	} else if(cur->key != id && !entro)
	{
		cout << "0 -1" << endl;
	}
}

int main()
{
	Node *root = NULL;
	string line;
    string num1;
    int id;
    int total_stream;
    string function;
	
	do{
        getline(cin, line);

        stringstream options(line);
    
        options >> function;
        
        if(function == "ADD")
        {
            options >> num1;
            id = stoi(num1);
            string num2;
            options >> num2;
            int wei = stoi(num2);

            total_stream+=wei;

            root = insert(root, id, wei);

            cout << total_stream << endl;            

        } 
		else if(function == "RNK")
        {
            options >> num1;
            id = stoi(num1);
            cout << ranking(root, id) << endl;
        } 
		else if (function == "WEI")
        {
            options >> num1;
            id = stoi(num1);
			int height = 0;
			weifunc(root, id, height);            
        }
    } while (function!= "END");

	
	return 0;
}
