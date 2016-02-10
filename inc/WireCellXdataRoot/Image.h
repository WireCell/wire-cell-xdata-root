#ifndef WIRECELLXDATAROOT_IMAGE
#define WIRECELLXDATAROOT_IMAGE

#include "WireCellXdataRoot/Types.h"
#include "WireCellXdataRoot/Blob.h"

class TClonesArray;

namespace WireCellXdataRoot {

    /** A Wire Cell image is a reduced region of space and time in a
     * frame where activity has been localized.  Localization is in
     * the form Blob objects.
     */
    struct Image {
	Image(imageid_t ident=0,
	      frameid_t frameid=0);

	~Image();

	/// A identifying number for this image within the frame.
	imageid_t ident;

	/// The identity of the frame to which this image is associated.
	frameid_t frameid;

	/// The blobs that make up this image.
	TClonesArray* blobs;
    };

}


#endif
