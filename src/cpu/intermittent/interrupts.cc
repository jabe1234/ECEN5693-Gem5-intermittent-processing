//TODO: Insert Copyright Here

#include "cpu/intermittent/interrupts.hh"
#include <iostream>

using namespace std;

namespace gem5
{

void
Intermittent::OutageSoon::invoke(
                        ThreadContext *tc,
                        const StaticInstPtr &inst) {
        inform("Intermittent Power Outage Soon!");
}

void
Intermittent::Restored::invoke(
                        ThreadContext *tc,
                        const StaticInstPtr &inst) {
        inform("Intermittent Power Restored!");
}

bool Intermittent::Interrupts::checkInterrupts() const {
        cout <<
                        "Intermittent Wrapper is checking for interrupts"
                        << endl;
        for (int i = 0; i < Intermittent::NumInterruptTypes; i++) {
                if (interrupts[i]) return true;
        }

        return wrapped->checkInterrupts();
}

Fault Intermittent::Interrupts::getInterrupt() {
        if (interrupts[Intermittent::INT_OUTAGESOON])
                        return std::make_shared<Intermittent::OutageSoon>();

        if (interrupts[Intermittent::INT_RESTORED])
                        return std::make_shared<Intermittent::Restored>();

        return wrapped->getInterrupt();
}

} //namespace gem5
