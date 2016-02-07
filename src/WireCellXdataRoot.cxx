// This holds random implementation code and provides something for
// the build system to turn into a library.

#include "WireCellXdataRoot/Point.h"
#include "WireCellXdataRoot/Wire.h"
#include "WireCellXdataRoot/Deco.h"
#include "WireCellXdataRoot/Geom.h"
#include "WireCellXdataRoot/Cell.h"
#include "WireCellXdataRoot/Blob.h"
#include "WireCellXdataRoot/Field.h"
#include "WireCellXdataRoot/Locus.h"
#include "WireCellXdataRoot/RunInfo.h"

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

Deco::Deco()
    : wireind(0)
    , slice(0)
    , values()
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

Cell::Cell(uint32_t ident, uint32_t uind, uint32_t vind, uint32_t wind)
    : ident(ident)
    , uind(uind)
    , vind(vind)
    , wind(wind)
    , area(-1)
    , center() 
{
}

Blob::Blob()
    : slice(0)
    , cellind()
    , values()
{
}



Locus::Locus()
    : name("")
    , blobind()
{
}

Locus::Locus(const std::string& name)
    : name(name)
    , blobind()
{
}

FieldPoint::FieldPoint()
    : point()
    , values()
{
}
	
FieldPoint::FieldPoint(const Point& point)
    : point(point)
    , values()
{
}
	
FieldPoint::FieldPoint(const Point& point, const std::vector<float>& value)
    : point(point)
    , values(value)
{
}

Field::Field(const std::string& name)
    : name(name),
      points()
{
}




RunInfo::RunInfo(uint64_t ident, const std::string& detector)
    : detector(detector), ident(ident)
{
}
