#pragma once
#include <vector>
#include "Observer.h"


class Subject
{
private:
	std::vector<Observer*> subscribers;

public:
    void subscribe(Observer* observer);
    void unsubscribe(Observer* observer);
    void notify();
};
