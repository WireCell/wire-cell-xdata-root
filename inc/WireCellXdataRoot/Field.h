#ifndef WIRECELLXDATAROOT_FIELD
#define WIRECELLXDATAROOT_FIELD

#include <vector>
#include <string>

#include "TObject.h"

namespace WireCellXdataRoot {

    /// An association of values to a point in space.
    struct FieldPoint {
	FieldPoint();
	FieldPoint(const Point& point);
	FieldPoint(const Point& point, const std::vector<float>& value);
	Point point;
	std::vector<float> values;
    };

    /** A field is a collection of field points with an associated name.
     */
    struct Field : public TObject {
	Field(const std::string& name = "");

	std::string name;
	std::vector<FieldPoint> points;

	ClassDef(Field,1);
    };
}

#endif
