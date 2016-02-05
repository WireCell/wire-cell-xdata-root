#ifndef WIRECELLXDATAROOT_LOCUS
#define WIRECELLXDATAROOT_LOCUS

#include <vector>
#include <string>

namespace WireCellXdataRoot {

    /** Mathematically, a locus is a manifold in a space which is
     * defined according to some criteria.  It is may also be defined
     * as the "scene of an event".
     *
     * Here, a Locus is a region of 3D space defined as a collection
     * of cells and possibly some associated values.  As there may be
     * multiple ways to define a Locus on the same space, the
     * association is make with weak references (to Blotches).
     *
     * A Locus has a name to allow multiple Loci to exist in the same context.
     *
     * A Locus can be used to hold all blob-level charge (and
     * uncertainty) information in a readout window or multiple Loci
     * can be used to separately hold clusters.
    */
    struct Locus {
	Locus();
	Locus(const std::string& name);

	/// some human-oriented identifier
	std::string name;

	/// Index into blotches array of associated blotches
	std::vector<int> blotchind;
    };

}

#endif
