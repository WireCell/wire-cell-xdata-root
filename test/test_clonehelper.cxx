#include "WireCellXdataRoot/CloneHelper.h"
#include "WireCellXdataRoot/Field.h"

#include <cassert>

using namespace WireCellXdataRoot;

int main ()
{
    Field field;
    CloneHelper<FieldPoint> fpch(*field.points);

    auto fps = fpch.make();
    assert (fpch.size() == 1);

    fps->values.push_back(42);
    assert (fps->values.size() == 1);

    assert(fpch.get(0)->values.size() == 1);

    fpch.clear();
    assert (fpch.size() == 0);


    // At this point fps *should* be treated as invalid by real code.
    // However, TClonesArray keeps it around so we use this evil
    // knowledge to check that the value that was there is now
    // cleared.  DON'T EVER DO THIS IN REAL CODE!
    assert (fps->values.size() == 0); // clear should recurse


    // now make it again in same slot of previously cleared object
    fps = fpch.make();
    assert (fpch.size() == 1);
    assert (fps->values.size() == 0);

}
