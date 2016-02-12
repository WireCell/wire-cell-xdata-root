#ifndef WIRECELLXDATAROOT_CLONEHELPER
#define WIRECELLXDATAROOT_CLONEHELPER

#include "TClonesArray.h"

namespace WireCellXdataRoot {

    /// Some syntax sugar on TClonesArray.
    template<class Type>
    class CloneHelper {
	TClonesArray& m_ca;
    public:
	CloneHelper(TClonesArray& ca) : m_ca(ca) {}


	/// Return current size of TClonesArray
	int size() {
	    return m_ca.GetEntriesFast(); 
	}

	/// Make a new-in-place object at the end of the TClonesArray,
	/// returning its pointer.
	Type* make() {
	    int index = size();
	    Type* ret = (Type*)m_ca.ConstructedAt(index);
	    ret->Clear();
	    return ret;
	}

	/// Return object at index in TClonesArray.
	Type* get(int index) {
	    return (Type*)m_ca.At(index);
	}	

	/// Pass on clear message to CA.
	void clear() {
	    m_ca.Clear("C");
	}
    };
}

#endif
