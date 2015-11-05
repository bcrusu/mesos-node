#include "MesosAsyncWorker.hpp"

MesosAsyncWorker::MesosAsyncWorker(std::function<int()> work) :
		Nan::AsyncWorker(NULL), _work(work), _resultStatus(0) {
	Nan::HandleScope scope;
	v8::MaybeLocal<v8::Promise::Resolver> maybe = v8::Promise::Resolver::New(v8::Isolate::GetCurrent());
	assert(!maybe.IsEmpty());
	_promiseResolver.Reset(maybe.ToLocalChecked());
}

MesosAsyncWorker::~MesosAsyncWorker() {
	_promiseResolver.Reset();
}

void MesosAsyncWorker::Execute() {
	try {
		_resultStatus = _work();
	} catch (const std::exception& ex) {
		auto what = ex.what();
		if (what) {
			SetErrorMessage(what);
		} else {
			SetErrorMessage("Unknown exception during Mesos driver call.");
		}
	} catch (...) {
		SetErrorMessage("Unknown error during Mesos driver call.");
	}
}

void MesosAsyncWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	auto promiseResolver = Nan::New(_promiseResolver);

	auto status = Nan::New(_resultStatus);
	promiseResolver->Resolve(status);
}

void MesosAsyncWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
	auto promiseResolver = Nan::New(_promiseResolver);

	auto errorMessage = Nan::New(ErrorMessage());
	assert(!errorMessage.IsEmpty());
	promiseResolver->Reject(errorMessage.ToLocalChecked());
}

v8::Local<v8::Promise> MesosAsyncWorker::GetPromise() {
	Nan::EscapableHandleScope scope;
	return scope.Escape(Nan::New(_promiseResolver)->GetPromise());
}
