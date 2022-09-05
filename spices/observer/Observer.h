#ifndef ___OBESERVER_H___
#define ___OBESERVER_H___

class Subject;

class Observer
{

public:
	Observer(){;}
	virtual ~Observer() {;}
	virtual void update(Subject * sub) = 0;
};

#endif
