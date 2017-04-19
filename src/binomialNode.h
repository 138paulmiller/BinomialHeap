/*
 * bnode.h
 *
 *  Created on: Apr 14, 2017
 *      Author: 138
 */

#ifndef BINOMIALNODE_H_
#define BINOMIALNODE_H_
#define DEBUG false
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ostream>

/*
	bnode -
		child    - points to node with value such that child value > parent value
		sibling  - points to node with shared parent, creates Single linked list between children
 */
template <typename T>
class binomialNode
{
public:
	binomialNode(T v, binomialNode<T> * parent = 0);
	~binomialNode();
	void addChild(binomialNode<T>* child);
	binomialNode<T>* find(T v);
	int size(int& i);
	void print( std::ostream& out);
	T value;
	binomialNode<T>* sibling, *child, * parent;
	int order;
};



template <typename T>
binomialNode<T>::binomialNode(T v, binomialNode<T> * p)
{
	value = v;
	parent = p;
	sibling = child = 0;
	order=  0;
}
template <typename T>
binomialNode<T>::~binomialNode()
{
	//std::cout << "\nDeleting " << value;

	if(child)
		delete child;

	if(sibling)
		delete sibling;

}

template<typename T>
int binomialNode<T>::size(int & i)
{
	i ++;
	if(sibling)
		sibling->size(i);
	if(child)
		child->size(i);

	return i;
}


template <typename T>
void binomialNode<T>::addChild(binomialNode<T>* childNode)
{
	if(childNode)
	{
		childNode->sibling = 0;
		if(child)
		{
			binomialNode<T>* temp = child;
			while(temp->sibling)
				temp = temp->sibling;
			temp->sibling = childNode;
		}
		else
		{
			child = childNode;
		}
		//
		order++;
		childNode->parent = this;
	}
}
template <typename T>
binomialNode<T>* binomialNode<T>::find(T v)
{
	binomialNode<T>* found = 0;
	if(v == value)
		return this;
	else if(sibling)
	{
		found =  sibling->find(v);
	}
	if( value < v && ! found) //if v is larger, check children,
	{
		if(child)
		{
			found =  child->find(v);
		}
	}

	return found;
}
template <typename T>
void binomialNode<T>::print(std::ostream& out)
{
	out << "\nNode : " << std::setw(5) << value;
	if(DEBUG)
	{
		out << "\tOrder:  " << order;
		out << "\tParent  : " ;
		if(parent) out  << std::setw(5) << parent ->value;
		out << "\tSibling : " ;
		if(sibling) out  << std::setw(5) << sibling->value;
		out << "\tChild   : " ;
		if(child) out << std::setw(5) << child->value;
		if(sibling && sibling->order < order)
			out << "********ERROR IN SIBLING ORDERING!!!******";
	}
	if(sibling)
		sibling->print(out);
	if(child)
			child->print(out);

}


#endif /* BINOMIALNODE_H_ */
