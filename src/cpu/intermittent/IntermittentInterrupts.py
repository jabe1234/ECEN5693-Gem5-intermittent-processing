from m5.objects.BaseInterrupts import BaseInterrupts


class IntermittentInterrupts(BaseInterrupts):
    type = "IntermittentInterrupts"
    cxx_class = "gem5::Intermittent::Interrupts"
    cxx_header = "cpu/intermittent/interrupts.hh"
