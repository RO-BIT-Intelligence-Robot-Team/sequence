#ifndef SEQUENCE_BASE_BLOCKS_H
#define SEQUENCE_BASE_BLOCKS_H

#include "sequence.h"
#include "util.h"

using namespace std;

namespace seq
{
namespace block
{
class Print : public Block
{
private:
    std::string text;
public:
    Print(const std::string &text);

    virtual bool spinOnce(SpinInfo spinInfo);

    virtual void reset();
};

class Delay : public Block
{
private:
    Timeout timeout;
public:
    Delay(double timeSeconds);

    virtual bool spinOnce(SpinInfo spinInfo);

    virtual void reset();

    virtual string generateDebugName();
};

class Function : public Block
{
private:
    function<void(void)> func;
public:
    Function(function<void(void)> func);

    virtual bool spinOnce(SpinInfo spinInfo);

    virtual void reset();
};

class WaitFor : public Block
{
private:
    function<bool(void)> breakCondition;
    Timeout timeout;
public:
    WaitFor(function<bool(void)> breakCondition, double timeout, function<void(void)> timeoutHandler);

    WaitFor(function<bool(void)> breakCondition, double timeout);

    WaitFor(function<bool(void)> breakCondition);

    virtual bool spinOnce(SpinInfo spinInfo);

    virtual void reset();
};

class SequenceBlock : public Block
{
private:
protected:
    Sequence *sequence;
public:
    SequenceBlock(Sequence *sequence);

    ~SequenceBlock();

    virtual bool spinOnce(SpinInfo spinInfo);

    virtual void reset();

    virtual string generateDebugName();

    virtual void compile(bool debug) final;
};

class LoopSequence : public SequenceBlock
{
private:
    Timeout timeout;
    function<bool(void)> breakCondition;
public:
    LoopSequence(Sequence *sequence, function<bool(void)> breakCondition, double timeout,function<void(void)> timeoutHandler);

    LoopSequence(Sequence *sequence, function<bool(void)> breakCondition, double timeout);

    LoopSequence(Sequence *sequence, function<bool(void)> breakCondition);

    virtual bool spinOnce(SpinInfo spinInfo);
};

}
}

#endif //SEQUENCE_BASE_BLOCKS_H
