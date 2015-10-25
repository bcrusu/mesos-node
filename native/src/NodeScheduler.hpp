#ifndef NODESCHEDULER_HPP_
#define NODESCHEDULER_HPP_

#include <mesos/scheduler.hpp>
#include <nan.h>

using namespace mesos;
using std::string;
using std::vector;

class NodeScheduler: public Scheduler {
public:
	explicit NodeScheduler(v8::Local<v8::Object> jsScheduler);
	~NodeScheduler();

	virtual void registered(SchedulerDriver* driver, const FrameworkID& frameworkId, const MasterInfo& masterInfo);
	virtual void reregistered(SchedulerDriver*, const MasterInfo& masterInfo);
	virtual void disconnected(SchedulerDriver* driver);
	virtual void resourceOffers(SchedulerDriver* driver, const vector<Offer>& offers);
	virtual void offerRescinded(SchedulerDriver* driver, const OfferID& offerId);
	virtual void statusUpdate(SchedulerDriver* driver, const TaskStatus& status);
	virtual void frameworkMessage(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, const string& data);
	virtual void slaveLost(SchedulerDriver* driver, const SlaveID& slaveId);
	virtual void executorLost(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, int status);
	virtual void error(SchedulerDriver* driver, const string& message);

private:
	Nan::Persistent<v8::Object> _jsScheduler;
};

#endif /* NODESCHEDULER_HPP_ */
