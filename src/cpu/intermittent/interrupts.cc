//TODO: Insert Copyright Here

#include "cpu/intermittent/interrupts.hh"

namespace gem5
{

bool Intermittent::Interrupts::checkInterrupts() const override {
        for (int i = 0; i < Intermittent::NumInterruptTypes; i++) {
                if (interrupts[i]) return true;
        }

        return wrapped->checkInterrupts();
}

Fault Intermittent::Interrupts::getInterrupt() override {
        if (interrupts[Intermittent::INT_OUTAGESOON]) return NoFault; //TODO
        if (interrupts[Intermittent::INT_RESTORED]) return NoFault; //TODO

        return wrapped->getInterrupt();
}

} //namespace gem5
