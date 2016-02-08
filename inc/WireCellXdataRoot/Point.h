#ifndef WIRECELLXDATAROOT_POINT
#define WIRECELLXDATAROOT_POINT

#include <cstdint>
#include <map>

namespace WireCellXdataRoot {

    struct Point {
        Point();
        Point(float x, float y, float z);

        /// A location in Cartesian 3-space.
        float x, y, z;
    };

    typedef std::pair<Point,Point> Ray;
}

#endif
