from m5.objects import (
    BaseCPU,
    IntermittentInterrupts,
)


class IntermittentCPU(BaseCPU):
    def createInterruptController(self):
        super().createInterruptController()

        for i in range(len(self.interrupts)):
            itr = self.interrupts[i]
            self.interrupts[i] = IntermittentInterrupts(itr)
