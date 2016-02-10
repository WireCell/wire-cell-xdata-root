#ifndef WIRECELLXDATAROOT_GEOM
#define WIRECELLXDATAROOT_GEOM

#include "WireCellXdataRoot/Types.h"
#include "WireCellXdataRoot/Point.h"
#include "WireCellXdataRoot/Wire.h"
#include "WireCellXdataRoot/Cell.h"

#include <string>
#include <vector>

class TClonesArray;

namespace WireCellXdataRoot {

    /// Information about the geometry of an associated set of wire
    /// planes, typically all wire planes in one APA.  If a complete
    /// detector is composed of identical APAs then a single Geom
    /// object is needed.  If APAs differ then one Geom per unique APA
    /// is needed.
    struct Geom {

	Geom(geomid_t ident=0, const std::string& description="",
	     const Ray& wire_bounds = std::make_pair(Point(),Point()));
	~Geom();

	/// An application specific identifier for this collection of
	/// geometry information.  For example, if each APA is
	/// described in a unique manner this might be the APA number.
	/// If some APAs are identical this might be an APA category
	/// number.
	geomid_t ident;

	/// A human-readable description of the identity of this
	/// geometry.
	std::string description;
	
	/// Define rectangular bounds for the wire planes.  Wires
	/// terminate on the bounds.
	Ray wire_bounds;

	/// Define the wire planes.  Each plane is defined by a ray.
	/// The tail point is at the center of wire zero (smallest Z)
	/// and the vector to the head points along the pitch
	/// direction and with magnitude equal to the pitch.  For
	/// real, as-built measured wires which may not have uniform
	/// pitch, these pitches are assumed to be consistent with
	/// average.  The length and ordering of this vector is
	/// application specific.
	std::vector<Ray> pitches;

	/// The Wire objects corresponding to the pitches and bounds.
	TClonesArray* wires;

	/// The Cell objects made from those wires
	TClonesArray* cells;

    };

}

#endif
