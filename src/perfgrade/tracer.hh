#ifndef __CPU_PERFGRADE_TRACE_HH__
#define __CPU_PERFGRADE_TRACE_HH__

#include "base/addr_range.hh"
#include "base/trace.hh"
#include "base/types.hh"
#include "cpu/static_inst.hh"
#include "cpu/thread_context.hh"
#include "params/PerfgradeTracer.hh"
#include "proto/protoio.hh"
#include "sim/insttracer.hh"

class ThreadContext;

namespace Perfgrade {

class TracerRecord : public Trace::InstRecord
{
  public:
    TracerRecord(Tick _when, ThreadContext *_thread,
               const StaticInstPtr _staticInst, TheISA::PCState _pc,
               const StaticInstPtr _macroStaticInst = NULL)
        : Trace::InstRecord(_when, _thread, _staticInst, _pc, _macroStaticInst)
    {}

    void traceInst(const StaticInstPtr &inst, bool ran);

    void dump();
};

class Tracer : public Trace::InstTracer
{
  public:
    typedef PerfgradeTracerParams Params;
    Tracer(const Params &params);
    virtual ~Tracer();

    Trace::InstRecord *
    getInstRecord(Tick when, ThreadContext *tc,
            const StaticInstPtr staticInst, TheISA::PCState pc,
            const StaticInstPtr macroStaticInst = NULL)
    {
        return new TracerRecord(when, tc,
                staticInst, pc, macroStaticInst);
    }

  protected:
    static ProtoOutputStream *traceStream;

    void createTraceFile(std::string filename);
    void closeStream();
    void dumpMem();

    friend class TracerRecord;
};

} // namespace Perfgrade

#endif // __CPU_PERFGRADE_TRACE_HH__
