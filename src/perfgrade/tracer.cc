#include "perfgrade/tracer.hh"

#include "base/output.hh"
#include "config/the_isa.hh"
#include "cpu/base.hh"
#include "cpu/static_inst.hh"
#include "cpu/thread_context.hh"
#include "perfgrade/proto/trace.pb.h"

using namespace std;
using namespace TheISA;

namespace Perfgrade {

ProtoOutputStream *Tracer::traceStream;

void
TracerRecord::dump()
{
    StaticInstPtr inst = staticInst;

    PGProto::ExecTrace trace;
    trace.set_tick(curTick());
    trace.set_cycle(thread->getCpuPtr()->curCycle());
    trace.set_pc(pc.instAddr());

    if (staticInst->isMicroop()) {
        trace.set_upc(pc.upc());
    }

    trace.set_predicate(predicate);
    if (data_status != DataInvalid) {
        trace.set_data(data.as_int);
    }
    if (getMemValid()) {
        PGProto::MemAccess *mem = trace.mutable_mem();
        mem->set_addr(addr);
        mem->set_size(size);
    }

    Tracer::traceStream->write(trace);
}

Tracer::Tracer(const Params &params) : InstTracer(params)
{
    createTraceFile(params.file_name);
}

void
Tracer::createTraceFile(std::string filename)
{
    // Since there is only one output file for all tracers check if it exists
    if (traceStream)
        return;

    traceStream = new ProtoOutputStream(simout.resolve(filename));

    // Output the header
    PGProto::Header header;
    header.set_tick_freq(SimClock::Frequency);
    traceStream->write(header);

    // get a callback when we exit so we can close the file
    registerExitCallback([this]() { closeStream(); });
}

void
Tracer::closeStream()
{
    if (!traceStream)
        return;

    delete traceStream;
    traceStream = NULL;
}
Tracer::~Tracer()
{
    closeStream();
}

} // namespace Perfgrade
