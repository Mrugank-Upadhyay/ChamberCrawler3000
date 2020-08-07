#ifndef _OBSERVER_
#define _OBSERVER_

#include <memory>

class Subject;

class Observer {
  public:
    virtual void notify(std::shared_ptr<Subject> whoNotified) = 0;
    virtual ~Observer();
};

#endif
