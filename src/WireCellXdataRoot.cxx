// This holds random implementation code and provides something for
// the build system to turn into a library.

#include "WireCellXdataRoot/Point.h"
#include "WireCellXdataRoot/Wire.h"
#include "WireCellXdataRoot/Geom.h"
#include "WireCellXdataRoot/Cell.h"
#include "WireCellXdataRoot/Blob.h"
#include "WireCellXdataRoot/Blotch.h"
#include "WireCellXdataRoot/Field.h"
#include "WireCellXdataRoot/Locus.h"
#include "WireCellXdataRoot/Image.h"
#include "WireCellXdataRoot/RunInfo.h"
#include "WireCellXdataRoot/Image.h"

#include <iostream>
using namespace std;
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

Image::Image(uint64_t ident,
	     uint64_t second, uint32_t nanosecond,
	     double slicespan, double toffset)
    : ident(ident)
    , second(second)
    , nanosecond(nanosecond)
    , slicespan(slicespan)
    , toffset(toffset)
    , cells()
    , blobs()
    , blotches()
    , fields()
{
}
Image::~Image()
{
    for (auto c : cells) {
	delete c;
    }
    for (auto b : blobs) {
	delete b;
    }
    for (auto b : blotches) {
	delete b;
    }
    for (auto f : fields) {
	delete f;
    }
}

Geom::Geom()
    : wires()
{
}
Geom::~Geom()
{
    for (auto w : wires) {
	delete w;
    }
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
    : ident(0)
    , uind(0)
    , vind(0)
    , wind(0)
    , area(-1)
    , center()
{
}

Cell::Cell(uint64_t ident, uint32_t uind, uint32_t vind, uint32_t wind)
    : ident(ident)
    , uind(uind)
    , vind(vind)
    , wind(wind)
    , area(-1)
    , center() 
{
}

Blob::Blob()
    : iscells(true)
    , index()
{
}


Blotch::Blotch()
    : slice(-1)
    , blobind()
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

Field::Field(const std::string& name) : name(name), value() {}




RunInfo::RunInfo(uint64_t ident, const std::string& detector)
    : detector(detector), ident(ident)
{
}
