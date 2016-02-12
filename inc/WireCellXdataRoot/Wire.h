#ifndef WIRECELLXDATAROOT_WIRE
#define WIRECELLXDATAROOT_WIRE

#include "WireCellXdataRoot/Types.h"
#include "WireCellXdataRoot/Point.h"

#include "TObject.h"

#include <vector>


namespace WireCellXdataRoot {

    /// The geometrical and organizational description of one wire
    /// segment in an APA.  A wire is a straight run of conductor.
    /// The entire conductor is logically made up of some number of
    /// connected wires (eg, in the case the conductor wraps around
    /// both sides of the APA).
    struct Wire : public TObject {
	Wire(wireid_t ident=0,
	     chanid_t chanid=0,
	     wireoff_t offset=0,
	     planeid_t plane=0,
	     faceid_t face=0,
	     segment_t segment=0,
	     const Point& point1 = Point(),
	     const Point& point2 = Point(),
	     apaid_t apaid=0
	    );

	/// Identifier for this wire.  
	wireid_t ident;

	/// Identifier to which channel this wire is connected.
	chanid_t chanid;

	/// A monotonically increasing offset from the "zero wire"
	/// which is chosen such that the wires midpoint has the
	/// smallest "Z" in the plane, as expressed in the coordinate
	/// system associated with the APA.
	wireoff_t offset;

	/// The plane in the APA in which the wire resides. 
	planeid_t plane;

	/// The face (eg, "front" vs. "back") in which the wire resides.
	faceid_t face;

	/// The segment number (number of conductor segments between
	/// this wire and the input to digitizing electronics).
	segment_t segment;

	/// The starting point of the wire expressed in the coordinate
	/// system associated with the APA.
	Point point1;

	/// The ending point of the wire expressed in the coordinate
	/// system associated with the APA.
	Point point2;

	/// Wires are described uniquely to some context provided by the
	/// geometry.  In some cases the application may need to
	/// distinguish between groups of wires besides plane and face.
	/// For example, if non-identical APAs exist in the same geometry
	/// context.  The "volumeid" soaks up these differences.  For
	/// geometries where the APAs are considered identical
	/// (replicated) then leave this as 0.
	apaid_t apaid;

	// Override TObject
	virtual void Clear(Option_t* opt = "");

	ClassDef(Wire, 1);
    };

}

#endif
