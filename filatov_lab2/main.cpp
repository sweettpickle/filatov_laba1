#include <iostream>

using namespace std;


class Node;
class NodeTree;


class Node{ //узел списка сыновей
public:
    Node *second;
    NodeTree *myself;
    int data;

    Node(int data = 0, Node *second = nullptr, NodeTree *myself = nullptr)
    {
        this->data = data;
        this->second = second;
        this->myself = myself;
    }

};

class list //список сыновей
{
public:
    list();
    void push_list(int data, NodeTree *myself, int k);

    Node *first;
};


list::list() {
    first = new Node(-1);
    first->second = new Node(-1);
}



void list::push_list(int data, NodeTree *myself, int k) {
    if (k == 1){
        first->data = data;
        first->myself = myself;
    }
    else if (k == 2)
    {
        first->second->data = data;
        first->second->myself = myself;
    }
}



class NodeTree{
public:
    NodeTree *next;
    list *sons;
    int value;

    NodeTree(int value = 0, NodeTree *next = nullptr, list *sons = nullptr)
    {
        this->value = value;
        this->next = next;
        this->sons = new list();
    }

};


class tree
{
public:
    tree();
    void push(int value);
    void pre_push(int value, NodeTree* current);
    void uni_obr(tree &b);
    void pre_uni_obr(NodeTree* root);
    void cout_pr();
    void pre_cout_pr(NodeTree* root);
    void cout_sim();
    void pre_cout_sim(NodeTree* root);


private:
    NodeTree *head;
};

tree::tree(){
    head = nullptr;
}

void tree::push(int value)
{
    if (head == nullptr){
       head = new NodeTree(value);
    }
    else
    {
        NodeTree *current = this->head;
        if (value < current->value){
            if (current->sons->first->data == -1){
                current->next = new NodeTree(value);
                current->sons->push_list(value, current->next, 1);
            }
            else{
               pre_push(value, current->sons->first->myself);
            }
        }
        if (value > current->value){
            if (current->sons->first->second->data == -1){
                current->next = new NodeTree(value);
                current->sons->push_list(value, current->next, 2);
            }
            else
            {
                pre_push(value, current->sons->first->second->myself);
            }
        }
    }

}


void tree::pre_push(int value, NodeTree* current){
    if (value < current->value){
        if (current->sons->first->data == -1){
            current->next = new NodeTree(value);
            current->sons->push_list(value, current->next, 1);
        }
        else{
            pre_push(value, current->sons->first->myself);
        }
    }
    if (value > current->sons->first->data){
        if (current->sons->first->second->data == -1){
            current->next = new NodeTree(value);
            current->sons->push_list(value, current->next, 2);
        }
        else{
            pre_push(value, current->sons->first->second->myself);
        }
    }
}

void tree::pre_uni_obr(NodeTree* root){
    if (!root){
        return;
    }

    pre_uni_obr(root->sons->first->myself);
    pre_uni_obr(root->sons->first->second->myself);
    push(root->value);
}


void tree::uni_obr(tree &b){
    if (!b.head){
        return;
    }

    pre_uni_obr(b.head->sons->first->myself);
    pre_uni_obr(b.head->sons->first->second->myself);
    push(b.head->value);
}



void tree::pre_cout_pr(NodeTree* root){
    if (!root){
        return;
    }

    cout << root->value << ", ";
    pre_cout_pr(root->sons->first->myself);
    pre_cout_pr(root->sons->first->second->myself);
}


void tree::cout_pr(){
    if (!head){
        return;
    }

    cout << head->value << ", ";
    pre_cout_pr(head->sons->first->myself);
    pre_cout_pr(head->sons->first->second->myself);
}


void tree::pre_cout_sim(NodeTree* root){
    if (!root){
        return;
    }

    pre_cout_pr(root->sons->first->myself);
    cout << root->value << ", ";
    pre_cout_pr(root->sons->first->second->myself);
}


void tree::cout_sim(){
    pre_cout_pr(head->sons->first->myself);
    cout << head->value << ", ";
    pre_cout_pr(head->sons->first->second->myself);
}



int main()
{
    setlocale(LC_ALL, "ru");

    tree a;
    tree b;
    a.push(12);
    a.push(9);
    a.push(14);
    a.push(6);

    b.push(10);
    b.push(7);
    b.push(11);
    b.push(3);
    b.push(17);
    b.push(1);

    a.uni_obr(b);

    a.cout_pr();
    cout << endl;
    b.cout_sim();

    return 0;
}