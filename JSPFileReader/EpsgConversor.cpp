#include "EpsgConversor.h"

EpsgConversor::EpsgConversor(QObject *parent)
	: QObject(parent)
{}

bool EpsgConversor::transformCoordinates(double x, double y, double &xOut, double &yOut)
{
	int epsgSrc = 4326;
	int epsgDst = 32630;
	//----------------------------------------------------------------------------------
	// Configure Spatial Reference Reprojection
	//----------------------------------------------------------------------------------
	OGRSpatialReference srcSpatialReference;
	OGRErr error = srcSpatialReference.importFromEPSG(epsgSrc);

	OGRSpatialReference dstSpatialReference;
	error = error | dstSpatialReference.importFromEPSG(epsgDst);

	if (error != 0)
		return false;

	OGRCoordinateTransformation* coordTrans = OGRCreateCoordinateTransformation(&srcSpatialReference, &dstSpatialReference);

	xOut = x;
	yOut = y;

	coordTrans->Transform(1, &xOut, &yOut);
	return true;
}


