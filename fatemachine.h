#ifndef FATEMACHINE_H
#define FATEMACHINE_H

#include <functional>
#include <unordered_map>

template <typename TFate, typename TReq>
class FateMachine
{
public:
    struct Quest {
        TReq request;
        TFate destiny;
        std::function<void()> feat;
    };
    using Rules = std::unordered_multimap<TFate, Quest>;

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
    const auto questsRange = rules.equal_range(fate);
    if (questsRange.first == questsRange.second) {
        return false;
    }
    const auto questPtr = std::find_if(questsRange.first,
                                 questsRange.second,
                                 [&ts](const std::pair<const TFate, Quest> &p)
    {
        return p.second.request == ts;
    });

    if (questPtr != questsRange.second) {
        const auto quest = questPtr->second;
        fate = quest.destiny;
        if (quest.feat){
            quest.feat();
        }
        return true;
    }

    return false;
}

template<typename TFate, typename TReq>
TFate FateMachine<TFate, TReq>::currentFate() const
{
    return fate;
}

#endif // FATEMACHINE_H
