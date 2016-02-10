#ifndef WIRECELLXDATAROOT_TYPES
#define WIRECELLXDATAROOT_TYPES

#include <cstdint>

namespace WireCellXdataRoot {

    /// Uniquely identify a geometry globally
    typedef uint64_t geomid_t;

    /// Uniquely identify a wire within the context of a
    /// geometry. Note this must be 16 bits to allow packing into a
    /// cellid_t.  65k wires is enough for anyone.
    typedef uint16_t wireid_t;

    /// Strictly sequentially count wires in a plane starting with
    /// zero for the wire with a midpoint at the smallest Z and
    /// increasing.
    typedef uint16_t wireoff_t;

    /// The planes within one APA face
    enum plane_types {kUplane=0, kVplane=1, kWplane=2, kNplanes=3, kUnknownPlane=-1};
    typedef int32_t planeid_t;

    /// The faces of an APA.
    enum face_types {kUnownFace=0, kFrontFace=1, kBackFace=2};
    typedef int32_t faceid_t;

    /// Wires are described uniquely to some context provided by the
    /// geometry.  In some cases the application may need to
    /// distinguish between groups of wires besides plane and face.
    /// For example, if non-identical APAs exist in the same geometry
    /// context.  The "volumeid" soaks up these differences.  For
    /// geometries where the APAs are considered identical
    /// (replicated) then leave this as 0.
    typedef uint32_t apaid_t;

    /// For wrapped conductors many wires attach to the same channel.
    /// The segment counts how many wires are between the wire in
    /// question and the channel input.
    typedef uint8_t segment_t;

    /// Uniquely identify a cell within the context of a geometry.
    typedef uint64_t cellid_t;

    /// Identify the algorithm used to form the cell.  
    typedef uint16_t tilingid_t;

    /// Uniquely identify a channel in the context of a geometry.
    typedef uint32_t chanid_t;

    /// Uniquely identify an instance of a trigger
    typedef uint64_t trigid_t;

    /// Identify reasons for a trigger
    typedef uint64_t trigger_t;

    /// Uniquely identify a run in the context of a geometry 
    typedef uint64_t runid_t;

    /// Uniquely identify a frame in time
    typedef uint64_t frameid_t;

    /// Identification of a slice in a frame.  This is used as an
    /// index in places and so is typically "close" to 0 and somewhat
    /// sequential.  Some slices may be unpolluted so its values can
    /// be sparse.
    typedef uint32_t slice_t;

    /// Uniquely identify a blob in the context of at least an Image.
    typedef uint32_t blobid_t;

    typedef uint32_t imageid_t;
 
    /// Uniquely identify a field up to the associated frame.
    typedef uint32_t fieldid_t;

    /// Type to hold time_t seconds from the start of the Unix epoch.
    /// Use 64 bits regardless of system time_t.
    typedef int64_t second_t;
    
    /// Type to hold number of nanoseconds within a second.
    typedef uint32_t nanosecond_t;


}


#endif

