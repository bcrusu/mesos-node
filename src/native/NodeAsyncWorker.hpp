#ifndef NODEASYNCWORKER_HPP_
#define NODEASYNCWORKER_HPP_

#include <functional>
#include <nan.h>

template<typename TResult>
class NodeAsyncWorker {
public:
	NodeAsyncWorker(std::function<TResult()> work, std::function<v8::Local<v8::Value>(TResult)> resultConverter) :
			_work(work), _resultConverter(resultConverter), _errorMessage(NULL) {
		_request.data = this;

		Nan::HandleScope scope;
		v8::MaybeLocal<v8::Promise::Resolver> maybe = v8::Promise::Resolver::New(v8::Isolate::GetCurrent());
		assert(!maybe.IsEmpty());
		_promiseResolver.Reset(maybe.ToLocalChecked());
	}

	virtual ~NodeAsyncWorker() {
		_promiseResolver.Reset();

		if (_errorMessage)
			delete[] _errorMessage;
	}

	v8::Local<v8::Promise> GetPromise() {
		Nan::EscapableHandleScope scope;
		auto promise = Nan::New(_promiseResolver)->GetPromise();
		return scope.Escape(promise);
	}

	void Run() {
		uv_queue_work(uv_default_loop(), &_request, AsyncExecute, (uv_after_work_cb) AsyncExecuteComplete);
	}

private:
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
		v8::Maybe<bool> result = promiseResolver->Resolve(v8::Isolate::GetCurrent()->GetCurrentContext(), jsResult);
		assert(!result.IsNothing());
	}

	void HandleErrorCallback() {
		Nan::HandleScope scope;
		auto promiseResolver = Nan::New(_promiseResolver);

		auto errorMessage = Nan::New(_errorMessage);
		assert(!errorMessage.IsEmpty());

		v8::Maybe<bool> result = promiseResolver->Reject(v8::Isolate::GetCurrent()->GetCurrentContext(), errorMessage.ToLocalChecked());
		assert(!result.IsNothing());
	}

	virtual void WorkComplete() {
		if (_errorMessage == NULL)
			HandleOKCallback();
		else
			HandleErrorCallback();
	}

	void SetErrorMessage(const char *msg) {
		if (_errorMessage) {
			delete[] _errorMessage;
		}

		size_t size = strlen(msg) + 1;
		_errorMessage = new char[size];
		memcpy(_errorMessage, msg, size);
	}

	static void AsyncExecute(uv_work_t* request) {
		auto worker = static_cast<NodeAsyncWorker*>(request->data);
		worker->Execute();
	}

	static void AsyncExecuteComplete(uv_work_t* request) {
		auto worker = static_cast<NodeAsyncWorker*>(request->data);
		worker->WorkComplete();
		delete worker;
	}

	std::function<TResult()> _work;
	std::function<v8::Local<v8::Value>(TResult)> _resultConverter;
	Nan::Persistent<v8::Promise::Resolver> _promiseResolver;

	uv_work_t _request;
	TResult _result;
	char* _errorMessage;

	NAN_DISALLOW_ASSIGN_COPY_MOVE(NodeAsyncWorker)
};

#endif /* NODEASYNCWORKER_HPP_ */
