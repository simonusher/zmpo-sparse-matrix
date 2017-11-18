#pragma once
#include <cstring>
#include <string>
namespace arrayUtils{
	template <class T>
	void copyArray(T *destination, T *source, int numberOfElements) {
		std::memcpy(destination, source, numberOfElements * sizeof(T));
	}

	template <class T>
	void allocateBigger(T *&src, int oldLength, int newLength) {
		T *newArray = new T[newLength];
		copyArray(newArray, src, oldLength);
		delete[] src;
		src = newArray;
	}

	template <class T>
	void allocateSmaller(T *&src, int newLength) {
		T *newArray = new T[newLength];
		copyArray(newArray, src, newLength);
		delete[] src;
		src = newArray;
	}

	template <class T>
	void ensureCapacity(int &arrayLength, T *&array, int numberOfArrayElements, float lowerBound,
		float upperBound, int minArrayCapacity) {
		float load = (float)numberOfArrayElements / arrayLength;
		if (load < lowerBound && arrayLength > minArrayCapacity) {
			allocateSmaller(array, (arrayLength / 2) + 1);
			arrayLength = (arrayLength / 2) + 1;
		}

		else if (load > upperBound) {
			allocateBigger(array, arrayLength, (arrayLength * 3) / 2 + 1);
			arrayLength = (arrayLength * 3) / 2 + 1;
		}
	}

	template <class T>
	void moveArray(T *startPointer, int numberOfElements, int offset) {
		memmove(startPointer + offset, startPointer, numberOfElements * sizeof(T));
	}

	template <class T>
	void moveArrayLeftByOne(T *startPointer, int numberOfElements) {
		memmove(startPointer - 1, startPointer, numberOfElements * sizeof(T)); //memmove is safe for overlapping areas
	}

	template <class T>
	void moveArrayRightByOne(T *startPointer, int numberOfElements) {
		memmove(startPointer + 1, startPointer, numberOfElements * sizeof(T)); //memmove is safe for overlapping areas
	}

	template <class T>
	std::string arrayToString(T *startPointer, int numberOfElements) {
		std::string arrayText;
		arrayText.append("[");
		for (int i = 0; i < numberOfElements; i++) {
			arrayText.append(std::to_string(startPointer[i]));
			if (i != numberOfElements - 1) {
				arrayText.append(", ");
			}
		}
		arrayText.append("]");
		return arrayText;
	}
}
