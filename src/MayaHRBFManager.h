#ifndef MAYAHRBFMAN_H
#define MAYAHRBFMAN_H

#include "MayaHRBF.h"
#include <vector>
#include "FloatGrid3D.hpp"

#include <maya/MMatrixArray.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MDataHandle.h>
#include <maya/MItGeometry.h>
#include <algorithm>

#define HRBF_COMPRES 128
#define NEWTON_STEPS 10
#define NEWTON_SIGMA 0.35f
#define COS_GRAD_ANGLE 0.57357643635 // cosine of 55 degrees

/******************************************************************************
Implements a skeleton of HRBF nodes.
This is effectively a fake scenegraph of sorts.
******************************************************************************/

class MayaHRBFManager {
public:
	MayaHRBFManager();
	~MayaHRBFManager();
	void buildHRBFs(std::vector<int> jointHierarchy, std::vector<std::string> names,
		MMatrixArray &binds, MMatrixArray &transforms,
		MArrayDataHandle& weightListHandle, MItGeometry& iter, MObject &weights);
	// we need weights to access things in the weightListHandle

	void compose(MMatrixArray &transforms); // compose the HRBFs
	void correct(MItGeometry& iter);

	void debugSamplesToConsole(std::string nodeName);
	void debugValuesToConsole(std::string nodeName);
	void debugCompositionToConsole(MMatrixArray &transforms, int numTransforms);

	// members
	std::vector<MayaHRBF*> m_HRBFs; // parallel to MMatrixArrays transforms and binds
	std::vector<float> m_isoVals; // parallel to MItGeometry iter
	int m_numJoints;
	int m_numISOs; // isovalues, one per vertex

	FloatGrid3D *mf_vals;
	FloatGrid3D *mf_gradX;
	FloatGrid3D *mf_gradY;
	FloatGrid3D *mf_gradZ;
	FloatGrid3D *mf_gradMag;
};

#endif