#ifndef ICOREEVENTS_H_
#define ICOREEVENTS_H_

class ICoreEvents
{

public:
	virtual void OnFrame();
	virtual void OnActivate();
	virtual void OnDeactivate();
	virtual void OnStart();
	virtual void OnStop();

	void SetActive(bool arg_active);

protected:
	bool mIsActive;

};


#endif