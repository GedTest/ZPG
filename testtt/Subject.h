#pragma once
#include <vector>
#include "Observer.h"


class Subject
{
protected:
	std::vector<Observer*> subscribers;

public:
    void subscribe(Observer* observer);
    void unsubscribe(Observer* observer);
    virtual void notify();
};
