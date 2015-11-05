#ifndef MESOSASYNCWORKER_HPP_
#define MESOSASYNCWORKER_HPP_

#include <functional>
#include <nan.h>

class MesosAsyncWorker: public Nan::AsyncWorker {
public:
	MesosAsyncWorker(std::function<int()> work);
	~MesosAsyncWorker();

	void Execute();

	void HandleOKCallback();
	void HandleErrorCallback();

	v8::Local<v8::Promise> GetPromise();

private:
	std::function<int()> _work;
	Nan::Persistent<v8::Promise::Resolver> _promiseResolver;

	int _resultStatus;
};

#endif /* MESOSASYNCWORKER_HPP_ */
