#ifndef NODESCHEDULER_HPP_
#define NODESCHEDULER_HPP_

#include <mesos/scheduler.hpp>
#include <nan.h>

using namespace mesos;

namespace mesosNode {

class NodeScheduler: public mesos::Scheduler {
public:
	explicit NodeScheduler(const v8::Local<v8::Object>& jsSchedulerDriver, const v8::Local<v8::Object>& jsScheduler,
			const v8::Local<v8::Object>& protosBuilder);
	~NodeScheduler();

	virtual void registered(SchedulerDriver* driver, const FrameworkID& frameworkId, const MasterInfo& masterInfo);
	virtual void reregistered(SchedulerDriver*, const MasterInfo& masterInfo);
	virtual void disconnected(SchedulerDriver* driver);
	virtual void resourceOffers(SchedulerDriver* driver, const std::vector<Offer>& offers);
	virtual void offerRescinded(SchedulerDriver* driver, const OfferID& offerId);
	virtual void statusUpdate(SchedulerDriver* driver, const TaskStatus& status);
	virtual void frameworkMessage(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, const std::string& data);
	virtual void slaveLost(SchedulerDriver* driver, const SlaveID& slaveId);
	virtual void executorLost(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, int status);
	virtual void error(SchedulerDriver* driver, const std::string& message);

private:
	Nan::Persistent<v8::Object> _jsSchedulerDriver;
	Nan::Persistent<v8::Object> _jsScheduler;
	Nan::Persistent<v8::Object> _protosBuilder;
};

}

#endif /* NODESCHEDULER_HPP_ */
