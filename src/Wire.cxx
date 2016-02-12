#include "WireCellXdataRoot/Wire.h"
using namespace WireCellXdataRoot;

Wire::Wire(wireid_t ident,
	   chanid_t chanid,
	   wireoff_t offset,
	   planeid_t plane,
	   faceid_t face,
	   segment_t segment,
	   const Point& point1,
	   const Point& point2,
    	   apaid_t apaid)
    : ident(ident)
    , chanid(chanid)
    , offset(offset)
    , plane(plane)
    , face(face)
    , segment(segment)
    , point1(point1)
    , point2(point2)
    , apaid(apaid)
{
}

void Wire::Clear(Option_t* opt)
{
    ident=0;
    chanid=0;
    offset=0;
    plane=0;
    face=0;
    segment=0;
    point1 = Point();
    point2 = Point();
    apaid=0;
}
