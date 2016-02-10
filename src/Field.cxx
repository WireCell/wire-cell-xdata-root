#include "WireCellXdataRoot/Field.h"
#include "TClonesArray.h"

using namespace WireCellXdataRoot;

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

Field::Field(fieldid_t ident, trigid_t trigid, geomid_t geomid, const std::string& name)
    : ident(ident)
    , trigid(trigid)
    , geomid(geomid)
    , name(name)
    , points(new TClonesArray("WireCellXdataRoot::FieldPoint"))
{
}

Field::~Field()
{
    delete points;
}
