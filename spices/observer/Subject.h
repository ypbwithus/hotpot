#ifndef ___SUBJECT_H___
#define ___SUBJECT_H___

#include "Observer.h"
#include <vector>

using namespace std;

class Subject
{

public:
	Subject();
	virtual ~Subject();
	Observer *m_Observer;

	void attach(Observer *pObserver);
	void detach(Observer *pObserver);
	void notify();

	virtual int getState() = 0;
	virtual void setState(int _SubjectState) = 0;

private:
	vector<Observer *> m_vtObj;
};

#endif
