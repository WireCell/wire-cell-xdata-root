#ifndef WIRECELLXDATAROOT_FIELD
#define WIRECELLXDATAROOT_FIELD

#include "WireCellXdataRoot/Types.h"
#include "WireCellXdataRoot/Point.h"

#include <vector>
#include <string>

#include "TObject.h"
class TClonesArray;

namespace WireCellXdataRoot {

    /// An association of values to a point in space.
    struct FieldPoint : public TObject {
	FieldPoint();
	FieldPoint(const Point& point);
	FieldPoint(const Point& point, const std::vector<float>& value);
	Point point;
	std::vector<float> values;

	ClassDef(FieldPoint,1);
    };

    /** A field is a collection of field points with an associated name.
     */
    struct Field {
	Field(fieldid_t ident=0,
	      trigid_t trigid=0,
	      geomid_t geomid=0,
	      const std::string& name = "");
	~Field();

	/// A unique identifier for this field.
	fieldid_t ident;

	/// The associated trigger.
	trigid_t trigid;

	/// The associated geometry.
	geomid_t geomid;

	/// A human-readable description of the field 
	std::string name;

	TClonesArray* points;
    };
}

#endif
