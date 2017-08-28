// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <array>

/**
 *  This is intended to be a small fast queue to hold FNames on the stack.
 */
template<typename T, int N>
class HEROROGUE_API SmallQueue
{
public:
	SmallQueue()
		: Itr{ Data.begin() }
	{
		Data.fill(T{});
	}
	~SmallQueue() {};
	inline void PushBack(T element);
	inline T PopFront();
	inline T Front() const;
	inline bool IsEmpty() const;
	inline size_t Size() const;
	inline size_t Slack() const;
	inline void Clear();
private:
	std::array<T, N> Data;
	typename std::array<T, N>::iterator Itr;
};

template<typename T, int N>
void SmallQueue<T, N>::PushBack(T element) {
	if (Itr == Data.end()) { throw std::range_error("Error cannot push to a full SmallQueue."); }
	*Itr = element;
	++Itr;
}

template<typename T, int N>
T SmallQueue<T, N>::PopFront() {
	if (Itr == Data.begin()) { throw std::range_error("Error cannot pop an empty SmallQueue"); }
	auto retVal = *Data.begin();
	for (typename std::array<T, N>::iterator swapItr = Data.begin(); swapItr != Itr; ++swapItr) {
		*swapItr = std::move(*(swapItr + 1));
	}
	--Itr;
	return retVal;
}

template<typename T, int N>
T SmallQueue<T, N>::Front() const {
	if (Itr == Data.begin()) { throw std::range_error("Error cannot view an empty SmallQueue"); }
	return *(Itr - 1);
}

template<typename T, int N>
bool SmallQueue<T, N>::IsEmpty() const {
	return Itr == Data.begin();
}

template<typename T, int N>
size_t SmallQueue<T, N>::Size() const {
	return std::distance<std::array<T, N>::const_iterator>(Data.begin(), Itr);
}

template<typename T, int N>
size_t SmallQueue<T, N>::Slack() const {
	return std::distance<std::array<T, N>::const_iterator>(Itr, Data.end());
}

template<typename T, int N>
void SmallQueue<T, N>::Clear() {
	Itr = Data.begin();
}