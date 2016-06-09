#pragma once
#include <stddef.h>
//This class ensures that any other class has only one instance and a global point of access to it

template <class T>
class Singleton{
public:
	static void Create(){
		if (inst == NULL){
			inst = new T();
		}
	}

	static void Delete(){
		delete inst;
	}

	static T& Instance(){
		if (inst == NULL){
			Create();
		}
		return *inst; 
	}
protected:
	Singleton(){};
	virtual ~Singleton(){};

	static T* inst;
};

template<class T> T* Singleton<T>::inst = NULL;