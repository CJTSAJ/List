// ConsoleApplication5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Node//节点类
{
public:
	int value;
	Node* next;
	Node();//默认
	Node(int v) :value(v), next(NULL) {}
};

Node::Node() :value(0), next(NULL){}

class List
{
public:
	List();//默认初始化
	List(List&l);//构造函数
	List(const vector<int>&v);//用向量初始化
	List(int* arr, int array_size);//用指定大小的数组赋值
	int length()const;//返回链表的长度
	bool insert(int pos, int value);//在pos处插入一个节点
	int find(int value);//找出第一个值为value的节点的位置
	int remove(int value);//删去所有value的节点
	bool split(int pos, List&new_list);//分裂链表
	void combine(List& append_list);//合并两个链表
	void print_all();//打印链表所有节点
	~List();//析构函数
private:
	Node* head; Node* now; Node* then;
	int size;
};

List::List() :head(NULL), now(NULL), then(NULL){}

List::List(List&l)
{
	l.size = size; l.head = head;
	l.now = now; l.then = then;
}

List::List(const vector<int>&v)
{
	size = v.size();
	head = new Node;
	head->value = v[0];
	now = head;
	for (int i = 1; i < v.size(); i++)
	{
		then = new Node;
		then->value = v[i];
		now->next = then;
		now = then;
	}
}

List::List(int* arr, int array_size)
{
	size = array_size;
	head = new Node;
	head->value = arr[0];
	now = head;
	for (int i = 1; i < array_size; i++)
	{
		then = new Node;
		then->value = arr[i];
		now->next = then;
		now = then;
	}
}

int List::length()const
{
	return size;
}

bool List::insert(int pos, int value)
{
	Node* newnode = new Node(value);
	if (pos >= size)return false;
	now = head;
	for (int i = 0; i < pos-1; i++)now = now->next;
	newnode->next = now->next;
	now->next = newnode;
	size++;
	return true;
}

int List::find(int value)
{
	now = head;
	for (int i=0; i < size; i++)
	{
		if (now->value == value)return i;
		now = now->next;
	}
	return -1;
}

int List::remove(int value)
{
	int num = 0;
	now = head;
	while (now->value == value)
	{
		now = now->next;
		delete head;//删除该节点
		head = now;
		num++;
	}
	then = now->next;
	for (int i = 0; i < size - num - 1; i++)
	{
		if (then->value == value)
		{
			now->next = then->next;
			delete then;//删除该节点
			then = now->next;
			num++;
		}
		else
		{
			now = then;
			then = then->next;
		}
	}
	size -= num;
	return num;
}

bool List::split(int pos, List&new_list)
{
	if (pos >= size)return false;
	now = head;
	for (int i = 0; i < pos; i++)now = now->next;
	new_list.head = now->next;
	now->next = NULL;
	size = pos + 1;
	new_list.size = size - pos - 1;
	return true;
}

void List::combine(List& append_list)
{
	now = head;
	append_list.now = append_list.head;
	for (int i = 0; i < size - 1; i++)now = now->next;
	for (int i = 0; i < append_list.size; i++)
	{
		then = new Node(append_list.now->value);
		now->next = then;
		now = then;
		append_list.now = append_list.now->next;
	}
	size += append_list.length();
}

void List::print_all()
{
	now = head;
	for (int i = 0; i < size; i++)
	{
		cout << now->value << ' ';
		now = now->next;
	}
	cout << '\n';
}

List::~List()
{
	now = head;
	for (int i = 0; i < size; i++)
	{
		then = now->next;
		delete now;
		now = then;
	}
}

int main()
{
	fstream file("CJT.txt");
	int num;
	vector<int> v;
	while (!file.eof())
	{
		file >> num;
		v.push_back(num);
	}
	List list1(v);
	list1.print_all();
	return 0;
}

