#include "arrayUtils.h"
class SparseCell{
	friend class SparseMatrix;
	SparseCell(int *coordinates, int value);
	SparseCell(SparseCell &other, int numberOfCoordinates);
	~SparseCell();
	int *coordinates;
	int value;
};