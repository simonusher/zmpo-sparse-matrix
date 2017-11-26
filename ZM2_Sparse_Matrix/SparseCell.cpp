#include "SparseCell.h"

SparseCell::SparseCell(int *coordinates, int value) {
	this->coordinates = coordinates;
	this->value = value;
}

SparseCell::SparseCell(SparseCell &other, int numberOfCoordinates) {
	this->coordinates = new int[numberOfCoordinates];
	arrayUtils::copyArray(this->coordinates, other.coordinates, numberOfCoordinates);
	this->value = other.value;
}

SparseCell::~SparseCell() {
	delete[] this->coordinates;
}
