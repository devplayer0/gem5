from m5.params import *
from m5.objects.Workload import Workload

class ARMROMWorkload(Workload):
    type = 'ARMROMWorkload'
    cxx_class = 'Perfgrade::ARMROMWorkload'
    cxx_header = 'perfgrade/workload.hh'

    rom_file = Param.String('', 'File that contains the ROM')
