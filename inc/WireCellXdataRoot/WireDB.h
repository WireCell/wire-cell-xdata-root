#ifndef WIRECELLXDATAROOT_WIREDB
#define WIRECELLXDATAROOT_WIREDB

#include "WireCellXdataRoot/Wire.h"

#include <unordered_map>


namespace WireCellXdataRoot {

    /// A simple lookup of wires.  Load them up like:
    /// WireDB wdb;
    ///
    /// for (auto wire : collection_of_wires) {
    ///   wdb(wire);
    /// }
    ///
    /// Then do lookups like:
    ///
    /// const Wire* wire_on_ch42 = wdb.by_chan(42);
    struct WireDB {
	std::unordered_map<chanid_t,const Wire*> chan2wire;
	std::unordered_map<wireid_t,const Wire*> id2wire;
    public:
	WireDB() {}
	~WireDB() {}

	void operator()(const Wire* wire) {
	    id2wire[wire->ident] = wire;
	    chan2wire[wire->chanid] = wire;
	}

	const Wire* by_chan(chanid_t cid) {
	    return chan2wire[cid];
	}
	const Wire* by_id(wireid_t wid) {
	    return id2wire[wid];
	}

    };

}

#endif
