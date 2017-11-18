#include "arrayUtils.h"
class SparseCell{
public:
	friend class SparseMatrix;
private:
	SparseCell(int *coordinates, int value);
	SparseCell(SparseCell &other, int numberOfCoordinates);
	~SparseCell();
	int *coordinates;
	int value;
};