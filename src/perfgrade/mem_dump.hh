#ifndef __PERFGRADE_MEM_DUMP_HH__
#define __PERFGRADE_MEM_DUMP_HH__

#include "base/addr_range.hh"
#include "base/types.hh"
#include "cpu/pc_event.hh"
#include "params/MemDump.hh"
#include "sim/sim_object.hh"
#include "sim/system.hh"

namespace Perfgrade {

class LoadEvent : public PCEvent
{
  private:
    const std::string filename;
    const Addr addr;

  public:
    LoadEvent(PCEventScope *s, Addr when, const std::string &filename,
      const Addr addr) : PCEvent(s, "Memory dump event", when),
        filename(filename), addr(addr)
    {}

    void process(ThreadContext *tc) override;
};

class MemDump : public SimObject
{
  public:
    typedef MemDumpParams Params;
    MemDump(const Params &params) : SimObject(params), system(params.system)
    {}

    void dump(const std::string &filename, const AddrRange range);
    void load(const std::string &filename, const Addr address);
    void loadWhen(const std::string &filename, const Addr address,
      const Addr when);

  protected:
    System *system;
};

} // namespace Perfgrade

#endif // __PERFGRADE_MEM_DUMP_HH__
