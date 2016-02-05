#ifndef WIRECELLXDATAROOT_LOCUS
#define WIRECELLXDATAROOT_LOCUS

#include <vector>
#include <string>

namespace WireCellXdataRoot {

    /// A collection of blotches.
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
