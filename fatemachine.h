#ifndef FATEMACHINE_H
#define FATEMACHINE_H

#include <functional>
#include <map>

template <typename TFate, typename TReq>
class FateMachine
{
public:
    struct Quest {
        TReq request;
        TFate destiny;
        std::function<void()> feat;
    };
    using Rules = std::multimap<TFate, Quest>;

    explicit FateMachine(const TFate initialFate);
    FateMachine(const Rules &rules, const TFate initialFate);
    FateMachine(Rules &&rules, const TFate initialFate);

    void setRules(const Rules &rules);
    bool tempt(TReq ts);
    TFate currentFate() const;

private:
    Rules rules;
    TFate fate;
};

template<typename TFate, typename TReq>
FateMachine<TFate, TReq>::FateMachine(const TFate initialFate) : fate(initialFate)
{ }

template<typename TFate, typename TReq>
FateMachine<TFate, TReq>::FateMachine(const Rules &rules, const TFate initialFate)
    : rules(rules)
    , fate(initialFate)
{ }

template<typename TFate, typename TReq>
FateMachine<TFate, TReq>::FateMachine(Rules &&rules, const TFate initialFate)
    : rules(std::move(rules))
    , fate(initialFate)
{ }

template<typename TFate, typename TReq>
void FateMachine<TFate, TReq>::setRules(const Rules &rules)
{
    this->rules = rules;
}

template<typename TFate, typename TReq>
bool FateMachine<TFate, TReq>::tempt(TReq ts)
{
    const auto range = rules.equal_range(fate);
    for (auto i = range.first; i != range.second; ++i)
    {
        auto t = i->second;
        if (t.request == ts) {
            fate = t.destiny;
            if (t.feat) {
                t.feat();
            }
            return true;
        }
    }
    return false;
}

template<typename TFate, typename TReq>
TFate FateMachine<TFate, TReq>::currentFate() const
{
    return fate;
}

#endif // FATEMACHINE_H
