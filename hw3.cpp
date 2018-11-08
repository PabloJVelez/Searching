#include <iostream>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "ArgumentManager.h"
using namespace std;
// Date class to hold all of the Date attributes
class Date
{
public:
    int year;
    int month;
    int day;
    
    Date()
    {
        day = month = year = 1;
    }
    
    Date(string dob_)
    {
        year = stoi(dob_.substr(0, dob_.find('-')));
        dob_ = dob_.substr(dob_.find('-') + 1, dob_.length());
        month = stoi(dob_.substr(0, dob_.find('-')));
        dob_ = dob_.substr(dob_.find('-') + 1, dob_.length());
        day = stoi(dob_.substr(0, dob_.find('-')));
    }
    //function to print out the Date class
    string print()
    {
        
        string nYear = to_string(year);
        string nMonth;
        string nDay;
        
        if (month < 10)
            nMonth = "0" + to_string(month);
        else
            nMonth = to_string(month);
        if (day < 10)
            nDay = "0" + to_string(day);
        else
            nDay = to_string(day);
        
        return nYear + "-" + nMonth + "-" + nDay;
    }
    
    bool operator==(const Date& d) const
    {
        return year == d.year && month == d.month && day == d.day;
    }
    
    bool operator>(const Date& d) const
    {
        if (year > d.year)
            return true;
        if (year == d.year && month > d.month)
            return true;
        if (year == d.year && month == d.month && day > d.day)
            return true;
        
        return false;
    }
    
    bool operator<(const Date &d) const
    {
        if (year < d.year)
            return true;
        if (year == d.year && month < d.month)
            return true;
        if (year == d.year && month == d.month && day < d.day)
            return true;
        
        return false;
    }
    
    friend ostream &operator<<(ostream&stream, Date d);
    
};

ostream &operator<<(ostream &stream, Date d)
{
    stream << d.year << "-" << d.month << "-" << d.day;
    
    return stream;
}
//Student class to hold all the student attributes
class Student
{
public:
    string id;
    string first;
    string last;
    Date dob;
    string major;
    float gpa;
    
    Student()
    {
        id = "";
        first = "";
        last = "";
        major = "";
        gpa = 0.0;
    }
    
    Student(string id_, string first_, string last_, string dob_, string major_, float gpa_)
    {
        id = id_;
        first = first_;
        last = last_;
        dob = Date(dob_);
        major = major_;
        gpa = gpa_;
    }
    //function to print all the attributes of the Student class
    string print()
    {
        string nGPA = to_string(gpa).substr(0,to_string(gpa).find('.')+3);
        return id + ", " + first + ", " + last + ", " + dob.print() + ", " + major + ", " + nGPA;
    }
};

//function to sort all of the student ID's in order
void swap(Student *one, Student *two)
{
    Student temp = *one;
    *one = *two;
    *two = temp;
}
void Sort(Student arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j].id.compare(arr[j+1].id) > 0)
                swap(&arr[j], &arr[j+1]);
}
// Binary search function to search through the list of Id's
int binarySearch2(Student arr[], int l, int r, string id)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        
        if (arr[mid].id == id)
            return mid;
        if ((arr[mid].id).compare(id) > 0)
            return binarySearch2(arr, l, mid - 1, id);
        return binarySearch2(arr, mid + 1, r, id);
    }
    return -1;
}

int binarySearch(Student arr[],int l, int r, string id)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
    
        if (arr[mid].id == id)
        {
            return 1;
        }
        if ((arr[mid].id).compare(id) > 0)
            return 1 + binarySearch(arr, l, mid - 1, id);
        return 1 + binarySearch(arr, mid + 1, r, id);
    }
    
    return -1;
}

struct Node
{
    int spot;
    Node *link;
    
public:
    Node(int spot_)
    {
        spot = spot_;
        link=NULL;
    }
};


class LinkedList
{
public:
    Node *head;
    Node *tail;
    
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    
    void add(int spot)
    {
        Node *tmp = new Node(spot);
        if (head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->link = tmp;
            tail = tail->link;
        }
    }
    bool empty()
    {
        return (head == NULL);
    }
    void remove()
    {
        if(!empty())
        {
            Node *temp = head;
            head = head->link;
            delete temp;
        }
    }
    
    ~LinkedList()
    {
        while (!empty())
        {
            remove();
        }
    }
    
};

template <class T>
struct TreeNode
{
public:
    T key;
    LinkedList index;
    TreeNode<T> *left;
    TreeNode<T> *right;
    int height;
    
    TreeNode(T key_, int index_)
    {
        key = key_;
        left = NULL;
        right = NULL;
        height = 1;
        index.add(index_);
    }
    
};

template<class T>
int height(TreeNode<T> *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

template<class T>
class Tree
{
public:
    TreeNode<T> *root;
    int size = 0;
    
    Tree()
    {
        root = NULL;
    }
    
    TreeNode<T> *rightRotate(TreeNode<T> *&y)
    {
        TreeNode<T> *x = y->left;
        TreeNode<T> *T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        
        return x;
    }
    
    TreeNode<T> *leftRotate(TreeNode<T> *&x)
    {
        TreeNode<T> *y = x->right;
        TreeNode<T> *T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        return y;
    }
    
    int getBalance(TreeNode<T> *x)
    {
        if (x == NULL)
            return 0;
        return height(x->left) - height(x->right);
    }
    
    TreeNode<T> *insert(T type, int index)
    {
        root = insert(root, type, index);
        return root;
    }
    
    TreeNode<T> *insert(TreeNode<T> *&node, T key, int index)
    {
        if (node == NULL)
        {
            size++;
            return new TreeNode<T>(key, index);
        }
        if (node->key == key)
            (node->index).add(index);
        else if (node->key > key)
            node->left = insert(node->left, key, index);
        else if (node->key < key)
            node->right = insert(node->right, key, index);
        
        node->height = 1 + max(height(node->left), height(node->right));
        
        int balance = getBalance(node);
        
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }

    
    int search(T key)
    {
        return search(key, root);
    }
    
    int search (T key, TreeNode<T> *leaf)
    {
        int searchNum = 0;
        if (leaf == NULL)
            return -1;
        while (leaf != NULL)
        {
        if (key == leaf->key)
            return 1 + searchNum;
        else if (key < leaf->key)
            leaf = leaf->left;
        else
            leaf = leaf->right;
            searchNum++;
        }
        return searchNum;
    }
    void print()
    {
        print(root);
    }
    
    void print(TreeNode<T> *root)
    {
        if (root == NULL)
            return;
        cout << root->key << endl;
        print(root->left);
        print(root->right);
    }
    
    ~Tree()
    {
        Erase(root);
    }
    
    void Erase(TreeNode<T> *tree)
    {
        if(tree != NULL)
        {
            Erase(tree->left);
            Erase(tree->right);
            delete tree;
        }
    }
};

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    string dbFile = am.get("A");
    string kyFile = am.get("B");
    string outfilename = am.get("C");
    
    Student array[100];
    int arrayCount = 0;
    
    Tree<string> idTree;
    Tree<string> firstTree;
    Tree<string> lastTree;
    Tree<Date> dateTree;
    Tree<string> majorTree;
    Tree<float> gpaTree;
    
    ifstream read(dbFile);
    if (read.is_open())
    {
        string line;
        int index = 0;
        while (getline(read, line))
        {
            if (line.length() == 0)
                break;
            
            istringstream ss(line);
            string token;
            
            string data[6];
            int count = 0;
            while (getline(ss, token, ','))
            {
                if (token[0] == ' ')
                    token = token.substr(1, token.length() - 1);
                data[count++] = token;
                
            }
            
            Student s = Student(data[0], data[1], data[2], data[3], data[4], stof(data[5]));
            array[arrayCount++] = s;
        }
    }
    //sorting the array
    Sort(array, arrayCount);
    //loading the student attributes into their trees
    for (int i = 0; i < arrayCount; i++)
    {
        idTree.insert(array[i].id, i);
        firstTree.insert(array[i].first, i);
        lastTree.insert(array[i].last, i);
        dateTree.insert(array[i].dob, i);
        majorTree.insert(array[i].major, i);
        gpaTree.insert(array[i].gpa, i);
    }
    
    ofstream writeOut(outfilename.c_str());
    //going to loop through every key in the key file. once its recieved, it'll loop through the array
    ifstream readKey(kyFile);
    if (readKey.is_open())
    {
        string line;
        while (getline(readKey, line))
        {
            if (line.length() == 0)
                break;
            
            string category = line.substr(0, line.find(':'));
            string findKey = line.substr(line.find(':') + 2, line.length());
            
            if (category == "ID")
            {
                int findIndex = binarySearch2(array, 0, arrayCount, findKey);
                if (findIndex != -1)
                    writeOut << array[findIndex].print() << endl;
                else
                    writeOut << "No record found for " << category << " " << findKey << endl;
                int accesses = 1 + binarySearch(array, 0, arrayCount, findKey);
                writeOut << "Without index: " << accesses << " accesses" << endl;
                writeOut << endl;
            }
            else
            {
                int accesses = 0;
                bool found = false;
                bool foundAll = false;
                for (int i = 0; i < arrayCount; i++)
                {
                    accesses++;
                    if (category == "FIRSTNAME" && array[i].first == findKey)
                        found = true;
                    else if (category == "LASTNAME" && array[i].last == findKey)
                        found = true;
                    else if (category == "DOB" && array[i].dob == Date(findKey))
                        found = true;
                    else if (category == "MAJOR" && array[i].major == findKey)
                        found = true;
                    else if (category == "GPA" && array[i].gpa == stof(findKey))
                        found = true;
                    //if the category searched is found it'll print out what was found
                    if (found)
                    {
                        writeOut << array[i].print() << endl;
                        writeOut << "Without index: " << accesses << " accesses" << endl;
                        
                        writeOut << "With index: ";
                        if (category == "FIRSTNAME")
                            writeOut << 1 + firstTree.search(findKey) << " accesses" << endl;
                        else if (category == "LASTNAME")
                            writeOut << 1 + lastTree.search(findKey) << " accesses" << endl;
                        else if (category == "DOB")
                            writeOut << 1 + dateTree.search(Date(findKey)) << " accesses" << endl;
                        else if (category == "MAJOR")
                            writeOut << 1 + majorTree.search(findKey) << " accesses" << endl;
                        else if (category == "GPA")
                            writeOut << 1 + gpaTree.search(stof(findKey)) << " accesses" << endl;
                        
                        foundAll = true;
                        found = false;
                        
                        writeOut << endl;
                    }
                }
                //if not found then this will be run for every id searched
                if (!foundAll)
                {
                    writeOut << "No record found for " << category << " " << findKey << endl;
                    writeOut << "Without index: " << accesses << " accesses" << endl;
                    writeOut << "With index: ";
                    if (category == "FIRSTNAME")
                        writeOut <<  1 + firstTree.search(findKey) << " accesses" << endl;
                    else if (category == "LASTNAME")
                        writeOut << 1 + lastTree.search(findKey) << " accesses" << endl;
                    else if (category == "DOB")
                        writeOut << 1 + dateTree.search(Date(findKey)) << " accesses" << endl;
                    else if (category == "MAJOR")
                        writeOut << 1 + majorTree.search(findKey) << " accesses" << endl;
                    else if (category == "GPA")
                        writeOut << 1 + gpaTree.search(stof(findKey)) << " accesses" << endl;
                    writeOut << endl;
                }
            }
        }
    }

    writeOut.close();
    return 0;
}
