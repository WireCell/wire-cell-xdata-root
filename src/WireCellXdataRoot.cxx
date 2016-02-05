// This holds random implementation code and provides something for
// the build system to turn into a library.

#include "WireCellXdataRoot/Point.h"
#include "WireCellXdataRoot/Wire.h"
#include "WireCellXdataRoot/Cell.h"
#include "WireCellXdataRoot/Blob.h"
#include "WireCellXdataRoot/Blotch.h"
#include "WireCellXdataRoot/Field.h"
#include "WireCellXdataRoot/Locus.h"

using namespace WireCellXdataRoot;

Wire::Wire()
    : wireid(0)
    , chanid(0)
    , volid(0)
    , plane(0)
    , face(0)
    , offset(-1)
    , segment(0)
    ,  point1()
    , point2()
{
}

Point::Point()
    : x(0)
    , y(0)
    , z(0) 
{
}

Point::Point(float x, float y, float z) 
    : x(x)
    , y(y)
    , z(z) 
{
}

Cell::Cell() 
    : uind(0)
    ,vind(0)
    ,wind(0)
    ,area(-1)
    ,center()
{
}

Cell::Cell(uint32_t uind, uint32_t vind, uint32_t wind)
    : uind(uind)
    , vind(vind)
    , wind(wind)
    , area(-1)
    , center() 
{
}

Blob::Blob()
    : cellind()
{
}


Blotch::Blotch()
    : slice(-1)
    , cellind()
    , value()
{
}

Locus::Locus()
    : name("")
    , blotchind()
{
}

Locus::Locus(const std::string& name)
    : name(name)
    , blotchind()
{
}

FieldPoint::FieldPoint()
    : point()
    , value()
{
}
	
FieldPoint::FieldPoint(const Point& point)
    : point(point)
    , value()
{
}
	
FieldPoint::FieldPoint(const Point& point, const std::vector<float>& value)
    : point(point)
    , value(value)
{
}
