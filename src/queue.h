#include <iostream>

template<class T>
struct QueuElement{
	T key;
	QueuElement* next;
	QueuElement(T x){
		key = x;
		next = NULL;
	}
};

template<class T>
struct Queue{
	QueuElement<T> *head, *tail;
	int size;
	Queue(){
		head=tail=NULL;
		this->size=0;
	}
	Queue(T x){
		QueuElement<T>* ena = new QueuElement<T>(x);
		
		head = tail = ena;
		this->size=1;
		
	}

	void push(T x){
		//dimiourgia antikeimenou
		QueuElement<T>* ena = new QueuElement<T>(x);
		
		if (head==NULL){
			head = tail = ena;
		}
		tail->next=ena;
		tail=ena;
		this->size++;
	}
	T pop(){
		T value;
		if (head!=NULL){
			QueuElement<T>* temp =  head;
			value=head->key;
			head=temp->next;			
			delete(temp);
		}
		if (head==NULL){
			tail=NULL;
		}
		this->size--;
		return value;
	}
	void empty(){
		while (this->size>0){
			std::cout<<this->pop()<<" ";
		}
	}
	
};