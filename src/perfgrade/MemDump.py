from m5.SimObject import *
from m5.params import *
from m5.proxy import *

class MemDump(SimObject):
    type = 'MemDump'
    cxx_class = 'Perfgrade::MemDump'
    cxx_header = 'perfgrade/mem_dump.hh'
    cxx_exports = [
        PyBindMethod('dump'),
        PyBindMethod('load'),
        PyBindMethod('loadWhen'),
    ]

    system = Param.System(Parent.any, "system")
