from gem5.components.boards.x86_board import X86Board
from gem5.components.cachehierarchies.ruby.mesi_two_level_cache_hierarchy import (
    MESITwoLevelCacheHierarchy,
)
from gem5.components.memory.single_channel import SingleChannelDDR4_2400
from gem5.components.processors.cpu_types import CPUTypes
from gem5.components.processors.simple_processor import SimpleProcessor
from gem5.isas import ISA
from gem5.resources.workload import obtain_resource
from gem5.simulate.simulator import Simulator

cpu = SimpleProcessor(CPUTypes("timing"), 1, ISA("x86"))

cachehierarchy = MESITwoLevelCacheHierarchy(
    "64KiB", "16", "64KiB", "16", "1MiB", "32", 1
)

dram = SingleChannelDDR4_2400(size="2GiB")

board = X86Board(
    "3GHz",
    cpu,
    dram,
    cachehierarchy,
)

command = "m5 exit;" + "echo 'random comment';" + "sleep 1;" + "m5 exit;"
board.set_kernel_disk_workload(
    kernel=obtain_resource("x86-linux-kernel-5.4.49"),
    disk_image=obtain_resource("x86-ubuntu-24.04-img"),
    readfile_contents=command,
)

sim = Simulator(board)
sim.run()
