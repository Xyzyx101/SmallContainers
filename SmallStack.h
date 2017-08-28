// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <array>

template<typename T, int N>
class SmallStack
{
public:
	SmallStack() : Itr{ Data.begin() }
	{
		Data.fill(T{});
	};
	~SmallStack() {};
	inline void Push(T element);
	inline T Pop();
	/*inline*/ T Top() const;
	inline bool Empty() const;
	inline size_t Size() const;
	inline size_t Slack() const;
	inline void Clear();
private:
	std::array<T, N> Data;
	typename std::array<T, N>::iterator Itr;
};

template<typename T, int N>
void SmallStack<T, N>::Push(T element) {
	if (Itr == Data.end()) { throw std::range_error("Error cannot push to a full SmallStack"); }
	*Itr = element;
	++Itr;
}

template<typename T, int N>
T SmallStack<T, N>::Pop() {
	if (Itr == Data.begin()) { throw std::range_error("Error cannot pop an empty SmallStack"); }
	return std::move(*(Itr-- - 1));
}

template<typename T, int N>
T SmallStack<T, N>::Top() const {
	if (Itr == Data.begin()) { throw std::range_error("Error cannot top an empty SmallStack"); }
	return *(Itr - 1);
}


template<typename T, int N>
bool SmallStack<T, N>::Empty() const {
	return Itr == Data.begin():
}

template<typename T, int N>
size_t SmallStack<T, N>::Size() const {
	return std::distance<std::array<T, N>::const_iterator>(Data.begin, Itr);
}

template<typename T, int N>
size_t SmallStack<T, N>::Slack() const {
	return std::distance<std::array<T, N>::const_iterator>(Itr, Data.end());
}

template<typename T, int N>
void SmallStack<T, N>::Clear() {
	Itr = Data.begin();
}
