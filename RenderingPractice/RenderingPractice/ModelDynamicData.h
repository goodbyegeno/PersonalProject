#pragma once
#include "CustomMatrix.h"
class ModelDynamicData
{
public:
	ModelDynamicData();
	virtual ~ModelDynamicData();

	ORBITMATRIX4x4 modelWorldPosition;

};