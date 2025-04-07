from m5.objects.BaseInterrupts import BaseInterrupts
from m5.params import *


class IntermittentOutageSignature(Enum):
    map = {"Constant": 0, "Sine": 1, "Poisson": 2}


class IntermittentInterrupts(BaseInterrupts):
    type = "IntermittentInterrupts"
    cxx_class = "gem5::Intermittent::Interrupts"
    cxx_header = "cpu/intermittent/interrupts.hh"

    wrapped = Param.BaseInterrupts(
        NULL, "Interrupt Controller for the Architecture"
    )

    outageSignature = Param.IntermittentOutageSignature(
        "Constant", "The Type of Outage the Intermittence is Modelling"
    )

    distribFactor = Param.Float(
        1, "Distribution Factor used to determine Outages"
    )

    outageTicks = Param.Int(1, "Duration of Ticks the Outage takes")
