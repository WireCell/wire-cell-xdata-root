#ifndef WIRECELLXDATAROOT_GEOM
#define WIRECELLXDATAROOT_GEOM

#include "WireCellXdataRoot/Wire.h"

namespace WireCellXdataRoot {

    /// Collect all geometry info.
    struct Geom {
	Geom();
	~Geom();

	/// Define a rectangular bounds for the wire planes.  Wires
	/// terminate on the bounds.
	Ray wire_bounds;

	/// Define the wire planes.  Each plane is defined by a ray.
	/// The tail point is at the center of wire zero (smallest Z)
	/// and the vector to the head points along the pitch
	/// direction and with magnitude equal to the pitch.  For
	/// real, as-built measured wires which may not have uniform
	/// pitch, these pitches are assumed to be consistent with
	/// average.
	std::vector<Ray> pitches;


	/// The wires corresponding to the pitches and bounds.
	std::vector<Wire*> wires;
    };

}

#endif
