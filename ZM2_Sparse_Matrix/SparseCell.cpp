#include "SparseCell.h"
#include <iostream>

SparseCell::SparseCell(int *coordinates, int value) {
	this->coordinates = coordinates;
	this->value = value;
	std::cout << "create sparse cell" << std::endl; //TODO: REMOVE THIS
}

SparseCell::SparseCell(SparseCell &other, int numberOfCoordinates) {
	this->coordinates = new int[numberOfCoordinates];
	arrayUtils::copyArray(this->coordinates, other.coordinates, numberOfCoordinates);
	this->value = other.value;
	std::cout << "create sparse cell copy" << std::endl; //TODO: REMOVE THIS
}

SparseCell::~SparseCell() {
	delete[] this->coordinates;
	std::cout << "destroy sparse cell" << std::endl; //TODO: REMOVE THIS
}
