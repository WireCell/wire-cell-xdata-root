#ifndef WIRECELLXDATAROOT_WIRE
#define WIRECELLXDATAROOT_WIRE

#include "WireCellXdataRoot/Point.h"

#include <cstdint>
#include <vector>


namespace WireCellXdataRoot {

    /// The geometrical and organizational description of one wire
    /// segment in an APA.  A wire is a straight run of conductor.
    /// The entire conductor is logically made up of some number of
    /// connected wires (eg, in the case the conductor wraps around
    /// both sides of the APA).
    struct Wire {
	Wire();

	/// Identifier for this wire.  
	uint32_t wireid;

	/// Identifier to which channel this wire is connected.
	uint32_t chanid;

	/// Identifier for the volume in which the wire resides.  The
	/// coordinate system of any 3D points related to wire
	/// locations is defined w.r.t. to the volume.
	uint16_t volid;

	/// The plane in the APA in which the wire resides. 
	int8_t plane;

	/// The face (eg, "front" vs. "back") in which the wire resides.
	int8_t face;

	/// A monotonically increasing offset from the "zero wire"
	/// which is chosen such that the wires midpoint has the
	/// smallest "Z" in the plane, as expressed in the coordinate
	/// system associated with the APA.
	int16_t offset;

	/// The segment number (number of conductor segments between
	/// this wire and the input to digitizing electronics).
	uint8_t segment;

	/// The starting point of the wire expressed in the coordinate
	/// system associated with the APA.
	Point point1;

	/// The ending point of the wire expressed in the coordinate
	/// system associated with the APA.
	Point point2;

    };

    struct WireSet {
	std::vector<Wire> wire;

	WireSet& operator=(const WireSet& other);
    };

}

#endif
