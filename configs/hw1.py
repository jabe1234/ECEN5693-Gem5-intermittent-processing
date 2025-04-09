from gem5.components.boards.simple_board import SimpleBoard
from gem5.components.cachehierarchies.ruby.mesi_two_level_cache_hierarchy import (
    MESITwoLevelCacheHierarchy,
)
from gem5.components.memory.single_channel import SingleChannelDDR4_2400
from gem5.components.processors.cpu_types import CPUTypes
from gem5.components.processors.simple_processor import SimpleProcessor
from gem5.isas import ISA
from gem5.resources.workload import obtain_resource
from gem5.simulate.simulator import Simulator

cpu = SimpleProcessor(CPUTypes("timing"), 1, ISA("arm"))

cachehierarchy = MESITwoLevelCacheHierarchy(
    "64KiB", "16", "64KiB", "16", "1MiB", "32", 1
)

dram = SingleChannelDDR4_2400()

board = SimpleBoard(
    "3GHz",
    cpu,
    dram,
    cachehierarchy,
)

rsrc = "arm-gapbs-tc-run"
board.set_workload(obtain_resource(rsrc))

sim = Simulator(board)
sim.run()
