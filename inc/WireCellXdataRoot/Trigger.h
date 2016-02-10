#ifndef WIRECELLXDATAROOT_TRIGGER
#define WIRECELLXDATAROOT_TRIGGER

#include "WireCellXdataRoot/Types.h"

#include <cstdint>

namespace WireCellXdataRoot {

    /** A trigger is an instance in time of something happening in the
     * context of a geometry.  It is largely referenced by other objects.
     */
    struct Trigger {

	Trigger(trigid_t ident=0,
		trigger_t type=0,
		runid_t runid=0,
		second_t second=0,
		nanosecond_t nanosecond=0
	    );
	~Trigger();

	/// An identifying number for this trigger in the context of
	/// the run. (eg, "event" number).
	trigid_t ident;
	
	/// The reason for raising this trigger
	trigger_t type;

	/// The associated run
	runid_t runid;	      

	/// The second in the Unix epoch in which the frame starts.
	second_t second;	// force 64 bit time_t

	/// The nanosecond in the second in which the frame starts.
	nanosecond_t nanosecond;

    };

}


#endif
