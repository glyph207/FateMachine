#include <QString>
#include <QDebug>

#include <memory>

#include "fatemachine.h"

enum class UState { // user defined states
    S1, S2, S3, S4
};

enum class USignal { // user defined signals
    T1, T2, T3, T4, T5
};

class Logic // user defined logic
{
public:
    void l1() { log.push_back("l1"); }
    void l2() { log.push_back("l2"); }
    void l3() { log.push_back("l3"); }
    void l4() { log.push_back("l4"); }
    void l5() { log.push_back("l5"); }
    void printLog() const {
        qDebug() << "log:";
        for (const auto& l: log) qDebug() << QString::fromStdString(l);
    }
private:
    std::vector<std::string> log;
};

int main()
{
    auto l = std::make_shared<Logic>();
    // describing transition graph
    // function bound to transition is expected to be void f(void)
    const FateMachine::Rules<UState, USignal> rules {
            {UState::S1, {USignal::T1, UState::S2, std::bind(&Logic::l1, l)}},
            {UState::S2, {USignal::T2, UState::S3, std::bind(&Logic::l2, l)}},
            {UState::S2, {USignal::T4, UState::S4, std::bind(&Logic::l4, l)}},
            {UState::S3, {USignal::T3, UState::S4, std::bind(&Logic::l3, l)}},
            {UState::S4, {USignal::T5, UState::S1, [l]() {
                    qDebug() << "something custom";
                    l->l5();
                    l->printLog(); } } }
    };
    FateMachine::Fate<UState, USignal> f(rules, UState::S1);

    // preparation is over, switching states now
    qDebug() << f.tempt(USignal::T1);
    qDebug() << f.tempt(USignal::T3);
    qDebug() << f.tempt(USignal::T4);
    qDebug() << f.tempt(USignal::T5);

    return 0;
}
