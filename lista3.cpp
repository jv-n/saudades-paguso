#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class node
{
    public:
    int id;
    int peso;
    int rank;
    int bf;
    int altura;
    node* left;
    node* right;
};

node* add(node* root, int id_val, int byte_val);
int ranking(node* root, int val);
node* rotate_left(node* root);
node* rotate_right(node* root);
void WEI(node* root, int id, int height);

int main ()
{
    string line;
    string num1;
    int id;
    int total_stream;
    string function;

    node* root = nullptr;
    
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

            root = add(root, id, wei);

            cout << total_stream << endl;            

        } else if(function == "RNK")
        {
            options >> num1;
            id = stoi(num1);
            cout << ranking(root, id) << endl;
        } else if (function == "WEI")
        {
            options >> num1;
            id = stoi(num1);
            int height = 0;
            WEI(root, id, height);
        }
    } while (function!= "END");

    return 0;
}

int height(node *N)
{
	if (N == nullptr)
		return 0;
	return N->altura;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

int getBalance(node *N)
{
	if (N == nullptr)
		return 0;
	return height(N->right) - height(N->left);
}

node* add(node* root, int id_val, int byte_val)
{
    if(root == nullptr)
    {
        node* temp = new node();
        temp->left = nullptr;
        temp->right = nullptr;
        temp->id = id_val;
        temp->peso = byte_val;
        temp->rank = 0;
        temp->bf = 0;
        temp->altura = 1;
        return (temp);
    }
    if(root->id == id_val)
    {
        root->peso+=byte_val;
        root->altura = 0;
        return root;
    }
    if(id_val<root->id)
    {
        root->rank = root->rank + byte_val;
        root->left = add(root->left, id_val, byte_val);
    } else
    root->right = add(root->right, id_val, byte_val);

    root->altura = 1 + max(height(root->right), height(root->left));

    root->bf = getBalance(root);

    if(root->bf > 1 && id_val > root->right->id)
    {
        return rotate_left(root);
    }
    if(root->bf < -1 && id_val < root->left->id)
    {
        return rotate_right(root);
    }
    if(root->bf > 1 && id_val < root->right->id)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    if(root->bf < -1 && id_val > root->left->id)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    return root;
}

node* rotate_left(node* root)
{
    node *y = root->right;
	node *T2 = y->left;

	y->left = root;
    y->rank += (root->rank + root->peso);
	root->right = T2;

	root->altura = max(height(root->left),
					height(root->right)) + 1;
	y->altura = max(height(y->left),
					height(y->right)) + 1;

    y->bf = getBalance(y);

	return y;
}
node* rotate_right(node* root)
{
    node *x = root->left;
	node *T2 = x->right;
	
	x->right = root;
    root->rank -= (x->peso + x->rank);
	root->left = T2;

	root->altura = max(height(root->left),
					height(root->right)) + 1;
	x->altura = max(height(x->left),
					height(x->right)) + 1;

	x->bf = getBalance(x);

	return x;

}

/*int getWeight(node* x)
{
    node* cur = new node();
    cur = x;
    int weight;
    while(cur->right!=nullptr)
    {
        weight += (cur->peso + cur->rank);
        cur = cur->right;
    }
    return weight;
}*/

int ranking(node* root, int val)
{
    node* cur = new node();
    cur = root;

    while(cur->id!= val)
    {
        if(val<cur->id)
        {
            cur = cur->left;
        }
        else 
        {
            cur = cur->right;
        }
        if(cur == nullptr)
        {
            return 0;
        }
    }

    return cur->rank;
}

void WEI(node* root, int id, int height)
{
    node* cur = new node();
    cur = root;

    if(cur->id > id && cur->left != nullptr)
    {
        height++;
        WEI(cur->left, id, height);
    }
    if(cur->id < id && cur->right != nullptr)
    {   
        height++;
        WEI(cur->right, id, height);
    }
    if((cur->left == nullptr && cur->id > id)||(cur->right == nullptr && cur->id < id))
    {
        cout << "0 -1" << endl;
    }
    if(cur->id == id)
    {
        cout << cur->peso << " " << height << endl;
    }
    if(cur->id == id && cur->peso == 0)
    {
        cout << "0 -1" << endl;
    }
}