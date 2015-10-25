#include "NodeScheduler.hpp"
#include "Common.hpp"

NodeScheduler::NodeScheduler(v8::Object jsScheduler) :
		_jsScheduler(jsScheduler) {
	//TODO: validate JS scheduler instance
}

void NodeScheduler::registered(SchedulerDriver* driver, const FrameworkID& frameworkId, const MasterInfo& masterInfo) {
	ScopedByteArray frameworkIdBytes = protobuf::Serialize(frameworkId);
	ScopedByteArray masterInfoBytes = protobuf::Serialize(masterInfo);
	//TODO: call _scheduler
}

void NodeScheduler::reregistered(SchedulerDriver*, const MasterInfo& masterInfo) {
	ScopedByteArray masterInfoBytes = protobuf::Serialize(masterInfo);
	//TODO: call _scheduler
}

void NodeScheduler::disconnected(SchedulerDriver* driver) {
	//TODO: call _scheduler
}

void NodeScheduler::resourceOffers(SchedulerDriver* driver, const vector<Offer>& offers) {
	ScopedByteArrayCollection offersCollection = protobuf::SerializeVector(offers);
	//TODO: call _scheduler
}

void NodeScheduler::offerRescinded(SchedulerDriver* driver, const OfferID& offerId) {
	ScopedByteArray offerIdBytes = protobuf::Serialize(offerId);
	//TODO: call _scheduler
}

void NodeScheduler::statusUpdate(SchedulerDriver* driver, const TaskStatus& status) {
	ScopedByteArray statusBytes = protobuf::Serialize(status);
	//TODO: call _scheduler
}

void NodeScheduler::frameworkMessage(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, const string& data) {
	ScopedByteArray executorIdBytes = protobuf::Serialize(executorId);
	ScopedByteArray slaveIdBytes = protobuf::Serialize(slaveId);
	ByteArray dataBytes = StringToByteArray(data);
	//TODO: call _scheduler
}

void NodeScheduler::slaveLost(SchedulerDriver* driver, const SlaveID& slaveId) {
	ScopedByteArray slaveIdBytes = protobuf::Serialize(slaveId);
	//TODO: call _scheduler
}

void NodeScheduler::executorLost(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, int status) {
	ScopedByteArray executorIdBytes = protobuf::Serialize(executorId);
	ScopedByteArray slaveIdBytes = protobuf::Serialize(slaveId);
	//TODO: call _scheduler
}

void NodeScheduler::error(SchedulerDriver* driver, const string& message) {
	//TODO: call _scheduler
}
