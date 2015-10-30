#ifndef NODESCHEDULERDRIVER_HPP_
#define NODESCHEDULERDRIVER_HPP_

#include <nan.h>
#include <mesos/scheduler.hpp>
#include "NodeScheduler.hpp"

using namespace mesos;

class NodeSchedulerDriver: public Nan::ObjectWrap {
public:
	static void Init(v8::Local<v8::Object> exports);

private:
	explicit NodeSchedulerDriver(NodeScheduler* scheduler, const FrameworkInfo& framework, const std::string& master, bool implicitAcknowlegements,
			const Credential& credential);
	explicit NodeSchedulerDriver(NodeScheduler* scheduler, const FrameworkInfo& framework, const std::string& master, bool implicitAcknowlegements);
	~NodeSchedulerDriver();

	static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Start(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Stop(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Abort(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Join(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Run(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void RequestResources(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void LaunchTasks(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void KillTask(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void AcceptOffers(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void DeclineOffer(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void ReviveOffers(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void SuppressOffers(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void AcknowledgeStatusUpdate(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void ReconcileTasks(const Nan::FunctionCallbackInfo<v8::Value>& info);

	static Nan::Persistent<v8::Function> _constructor;
	NodeScheduler* _scheduler;
	MesosSchedulerDriver* _schedulerDriver;
};

#endif /* NODESCHEDULERDRIVER_HPP_ */
