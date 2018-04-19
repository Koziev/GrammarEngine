#include <lem/oformatter.h>
#include <lem/solarix/BackTrace.h>

using namespace lem;
using namespace Solarix;


BackTrace::BackTrace(const BackTrace *_parent)
{
    if (_parent != nullptr && !_parent->Empty())
        parent = _parent;
    else
        parent = nullptr;
}


bool BackTrace::Empty() const
{
    if (!seq_number.empty())
        return false;

    if (parent != nullptr)
        return parent->Empty();
    else
        return true;
}


void BackTrace::RollbackTx(const BackTraceTx &tx)
{
    seq_number.resize(tx);
    name.resize(tx);
    trace.resize(tx);
    return;
}



void BackTrace::Clear()
{
    seq_number.clear();
    name.clear();
    trace.clear();
    return;
}

void BackTrace::CollectAll(BackTrace *result) const
{
    if (parent != nullptr)
        parent->CollectAll(result);

    for (lem::Container::size_type i = 0; i < name.size(); ++i)
    {
        result->name.push_back(name[i]);
        result->seq_number.push_back(new lem::MCollect<int>(*seq_number[i]));
        result->trace.push_back(new BackTraceItem(*trace[i]));
    }

    return;
}


BackTraceItem& BackTrace::Add(const lem::MCollect<int> &PatternSequenceNumber, const lem::UCString &wf_name, const Solarix::Word_Form *wf)
{
    seq_number.push_back(new lem::MCollect<int>(PatternSequenceNumber));
    name.push_back(wf_name);
    trace.push_back(new BackTraceItem(wf));
    return *trace.back();
}



BackTraceItem& BackTrace::Add(const lem::MCollect<int> &PatternSequenceNumber, const lem::UCString &wf_name, const CP_Array & exported)
{
    seq_number.push_back(new lem::MCollect<int>(PatternSequenceNumber));
    name.push_back(wf_name);
    trace.push_back(new BackTraceItem(exported));
    return *trace.back();
}


BackTraceItem& BackTrace::Add(const lem::MCollect<int> &PatternSequenceNumber, const lem::UCString &wf_name, const Solarix::Word_Form *wf, const CP_Array & exported)
{
    seq_number.push_back(new lem::MCollect<int>(PatternSequenceNumber));
    name.push_back(wf_name);
    trace.push_back(new BackTraceItem(wf, exported));
    return *trace.back();
}


void BackTrace::Add(const BackTrace &src)
{
    for (lem::Container::size_type i = 0; i < src.name.size(); ++i)
    {
        seq_number.push_back(new lem::MCollect<int>(*src.seq_number[i]));
        name.push_back(src.name[i]);
        trace.push_back(new BackTraceItem(*src.trace[i]));
    }

    return;
}

static bool x_contains_any_of_y(const lem::MCollect<int> &x, const lem::MCollect<int> &y)
{
    if (y.size() == 1)
        return x.find(y.front()) != UNKNOWN;
    else if (y.size() == 2)
        return x.find(y.front()) != UNKNOWN || x.find(y.back()) != UNKNOWN;
    else
    {
        for (lem::Container::size_type i = 0; i < y.size(); ++i)
        {
            if (x.find(y[i]) != UNKNOWN)
                return true;
        }

        return false;
    }
}


const BackTraceItem* BackTrace::Get(const lem::MCollect<int>& PatternSequenceNumber, const lem::UCString &required_name, bool thow_if_missing) const
{
    for (int i = CastSizeToInt(name.size()) - 1; i >= 0; --i)
    {
        if (name[i] == required_name && x_contains_any_of_y(*seq_number[i], PatternSequenceNumber))
            return trace[i];
    }

    if (parent != nullptr)
    {
        return parent->Get(PatternSequenceNumber, required_name, thow_if_missing);
    }

    if (thow_if_missing)
    {
        lem::MemFormatter mem;
        mem.printf("Can not find BackTrace variable %us", required_name.c_str());
        throw lem::E_BaseException(mem.string());
    }
    else
        return NULL;
}


bool BackTrace::Contains(const lem::MCollect<int> & PatternSequenceNumber, const lem::UCString &required_name) const
{
    for (int i = CastSizeToInt(name.size()) - 1; i >= 0; --i)
    {
        if (name[i] == required_name && x_contains_any_of_y(*seq_number[i], PatternSequenceNumber))
        {
            return true;
        }
    }

    if (parent != nullptr)
        return parent->Contains(PatternSequenceNumber, required_name);

    return false;
}




void BackTrace::Print(lem::OFormatter &to, SynGram &sg, bool detailed) const
{
    if (parent != nullptr)
        parent->Print(to, sg, detailed);

    for (lem::Container::size_type i = 0; i < name.size(); ++i)
    {
        if (seq_number[i]->size() == 1)
        {
            to.printf("%d", seq_number[i]->front());
        }
        else
        {
            to.printf("(");

            for (lem::Container::size_type j = 0; j < seq_number[i]->size(); ++j)
                to.printf(" %d", seq_number[i]->get(j));

            to.printf(" )");
        }


        to.printf(":%us = ", name[i].c_str());

        trace[i]->Print(to, sg, detailed);

        to.eol();
    }

    return;
}


void BackTrace::PrintExportedNodes(lem::OFormatter &to, SynGram &sg, bool detailed) const
{
    if (parent != nullptr)
    {
        parent->PrintExportedNodes(to, sg, detailed);
    }

    return;
}
