#ifndef MESOSASYNCWORKER_HPP_
#define MESOSASYNCWORKER_HPP_

#include <functional>
#include <nan.h>

template<typename TResult>
class MesosAsyncWorker: public Nan::AsyncWorker {
public:
	MesosAsyncWorker(std::function<TResult()> work, std::function<v8::Local<v8::Value>(TResult)> resultConverter) :
			Nan::AsyncWorker(NULL), _work(work), _resultConverter(resultConverter) {
		Nan::HandleScope scope;
		v8::MaybeLocal<v8::Promise::Resolver> maybe = v8::Promise::Resolver::New(v8::Isolate::GetCurrent());
		assert(!maybe.IsEmpty());
		_promiseResolver.Reset(maybe.ToLocalChecked());
	}

	~MesosAsyncWorker() {
		_promiseResolver.Reset();
	}

	void Execute() {
		try {
			_result = _work();
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

	void HandleOKCallback() {
		Nan::HandleScope scope;
		auto promiseResolver = Nan::New(_promiseResolver);

		auto jsResult = _resultConverter(_result);
		promiseResolver->Resolve(jsResult);
	}

	void HandleErrorCallback() {
		Nan::HandleScope scope;
		auto promiseResolver = Nan::New(_promiseResolver);

		auto errorMessage = Nan::New(ErrorMessage());
		assert(!errorMessage.IsEmpty());
		promiseResolver->Reject(errorMessage.ToLocalChecked());
	}

	v8::Local<v8::Promise> GetPromise() {
		Nan::EscapableHandleScope scope;
		return scope.Escape(Nan::New(_promiseResolver)->GetPromise());
	}

private:
	std::function<TResult()> _work;
	std::function<v8::Local<v8::Value>(TResult)> _resultConverter;
	TResult _result;
	Nan::Persistent<v8::Promise::Resolver> _promiseResolver;
};

#endif /* MESOSASYNCWORKER_HPP_ */
