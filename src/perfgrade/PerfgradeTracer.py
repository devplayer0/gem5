from m5.params import *
from m5.objects.InstTracer import InstTracer

class PerfgradeTracer(InstTracer):
    type = 'PerfgradeTracer'
    cxx_class = 'Perfgrade::Tracer'
    cxx_header = 'perfgrade/tracer.hh'

    file_name = Param.String('trace.bin', 'Instruction trace output file')
