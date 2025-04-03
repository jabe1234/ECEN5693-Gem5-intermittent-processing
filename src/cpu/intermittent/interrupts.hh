#ifndef __CPU_INTERMITTENT_INTERRUPT_HH__
#define __CPU_INTERMITTENT_INTERRUPT_HH__

#include "arch/generic/interrupts.hh"
#include "base/logging.hh"
#include "cpu/thread_context.hh"
#include "debug/Interrupt.hh"
#include "params/IntermittentInterrupts.hh"

namespace gem5
{

namespace Intermittent
{

enum InterruptTypes
{
        INT_OUTAGESOON,
        INT_RESTORED,
        NumInterruptTypes
};

enum DistributionType
{
        DST_CONST, //power is off every constant ticks
        //DST_SINE, //power is off when sine is <0
        //DST_POISSON, //power outages happen on a poisson distribution
        NumDistributionTypes
};

class Interrrupts : public BaseInterrupts
{
        private:
                BaseInterrupts *wrapped = nullptr;
                bool interrupts[NumInterruptTypes];

                int outageSignature = (int)DST_CONST;
                float distribFactor = 1;
                int outageTicks = 1;

        public:
                using Params = IntermittentInterruptsParams;
                //NOTE: I think the param name is set by the python value

                Interrupts(const Params &p) :
                        BaseInterrupts(p),
                                                wrapped(p.wrapped),
                        outageSignature(p.outageSignature),
                        distribFactor(p.distribFactor),
                        outageTicks(p.outageTicks) {
                        clearAll();
                }

                void post(int int_num, int index) override {
                        wrapped->post(int_num, index);
                }

                void clear(int int_num, int index) override {
                        wrapped->clear(int_num, index);
                }

                void clearAll() override {
                        for (int i = 0; i < NumInterruptTypes; i++) {
                                interrupts[i] = false;
                        }
                }

                bool checkInterrupts() const override;

                Fault getInterrupt() override;

                void updateIntrInfo() override {
                        wrapped->updateIntrInfo();
                }

                void serialize(CheckpointOut &cp) const override {
                        inform("TODO: Intermittent Serialization?");
                        wrapped->serialize(cp);
                }

                void unserialize(CheckpointIn &cp) override {
                        inform("TODO: Intermittent Unserialization?");
                        wrapped->unserialize(cp);
                }

}; //class IntermittentInterrupts

} // namespace Intermittent
} //namespace gem5
#endif
