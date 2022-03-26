# FateMachine
my take on Finite State-Machines

# Description
So the goal was to go one step further than just your regular switch-case thingy. And add a lot of puns. 

I still use enums to describe states and signals, create transition map (rules) and add function pointer for each transition. Nothing can stop you in using something more complicated than enums though. After setting rules you can traverse state graph using tempt function

# Example

Simple state graph, created in main.cpp:

~~~ mermaid
graph TD;
    S1 --> |T1| S2;
    S2 --> |T2| S3;
    S2 --> |T4| S4;
    S3 --> |T3| S4;
    S4 --> |T5*| S1;
~~~
