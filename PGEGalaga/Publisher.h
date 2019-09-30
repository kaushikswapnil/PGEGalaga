#pragma once
#include"Subscriber.h"
#include<algorithm>

class Publisher
{
public:
	Publisher() {};
	virtual ~Publisher() { m_subscriber.clear(); };

	virtual void PublishEvent(Event* _event) = 0;
	virtual void AddSubscriber(Subscriber* _subscriber) = 0;
	virtual void RemoveSubscriber(Subscriber* _subscriber) = 0;

protected:
	std::vector<Subscriber*> m_subscriber{};
};
