#include <iostream>
#include <cassert>
#include <vector>

uint64_t cell_ident_pack(int uind, int vind, int wind, int context)
{
    uint64_t u = uind;
    uint64_t v = vind;
    uint64_t w = wind;
    uint64_t c = context;
    
    uint64_t pc = (0xffff&c)<<48;
    uint64_t pu = (0xffff&u)<<32;
    uint64_t pv = (0xffff&v)<<16;
    uint64_t pw = (0xffff&w);

    return pc | pu | pv | pw;
}

std::vector<int> cell_ident_unpack(uint64_t ident)
{
    int c = (ident>>48)&0xffff;
    int u = (ident>>32)&0xffff;
    int v = (ident>>16)&0xffff;
    int w = ident&0xffff;

    return std::vector<int>{u,v,w,c};
}

using namespace std;

int main() {
    const vector<int> uvwc{12345,23456,34567,45678};
    auto packed = cell_ident_pack(uvwc[0], uvwc[1], uvwc[2], uvwc[3]);
    auto unpacked = cell_ident_unpack(packed);

    cerr << packed << endl;
    for (int i=0; i<4; ++i) {
	cerr << i << ": " << uvwc[i] << " " << unpacked[i] << endl;
	assert(uvwc[i] == unpacked[i]);
    }
    return 0;
}
