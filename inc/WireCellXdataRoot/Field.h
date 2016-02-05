#ifndef WIRECELLXDATAROOT_FIELD
#define WIRECELLXDATAROOT_FIELD

#include <vector>


namespace WireCellXdataRoot {

    /// An association of values to a point in space.
    struct FieldPoint {
	FieldPoint();
	FieldPoint(const Point& point);
	FieldPoint(const Point& point, const std::vector<float>& value);
	Point point;
	std::vector<float> value;
    };

    typedef std::vector<FieldPoint> Field;
}

#endif
