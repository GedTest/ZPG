#include "Subject.h"


void Subject::subscribe(Observer* observer) {
    this->subscribers.push_back(observer);
    return;
}

void Subject::unsubscribe(Observer* observer) {
    this->subscribers.erase(std::remove(this->subscribers.begin(), this->subscribers.end(), observer), this->subscribers.end());
    return;
}

void Subject::notify() {
    for (auto observer : this->subscribers) {
        observer->update();
    }
    return;
}
