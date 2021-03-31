#include "perfgrade/mem_dump.hh"

#include <fstream>

#include "base/output.hh"

using namespace std;

static void loadData(PortProxy &proxy, const std::string &filename,
    const Addr addr)
{
    std::ifstream ifs(filename, ios::binary|ios::ate);
    std::ifstream::pos_type size = ifs.tellg();
    ifs.seekg(0, ios::beg);

    std::vector<uint8_t> buffer(size);
    ifs.read((char *)buffer.data(), size);
    proxy.writeBlob(addr, buffer.data(), size);
}

namespace Perfgrade {

void
LoadEvent::process(ThreadContext *tc)
{
    loadData(tc->getPhysProxy(), filename, addr);
}

void
MemDump::dump(const std::string &filename, const AddrRange range)
{
    std::vector<uint8_t> buffer(range.size());
    system->physProxy.readBlob(range.start(), buffer.data(), buffer.size());

    OutputStream *out = simout.create(filename, true);
    out->stream()->write((const char *)buffer.data(), buffer.size());
}

void
MemDump::load(const std::string &filename, const Addr addr)
{
    loadData(system->physProxy, filename, addr);
}

void
MemDump::loadWhen(const std::string &filename, const Addr addr,
    const Addr when)
{
    new LoadEvent(system, when, filename, addr);
}

} // namespace Perfgrade
