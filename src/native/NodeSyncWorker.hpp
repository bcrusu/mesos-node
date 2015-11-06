#ifndef NODEASYNCWORKER_HPP_
#define NODEASYNCWORKER_HPP_

#include <functional>
#include <nan.h>

class NodeSyncWorker {
public:
	NodeSyncWorker(std::function<void()> work) :
			_work(work) {
		_request.data = this;
	}

	void Run() {
		uv_async_init(uv_default_loop(), &_request, AsyncExecute);
		uv_async_send(&_request);
	}

private:
	void Execute() {
		_work();
	}

	static void AsyncExecute(uv_async_t* request) {
		auto worker = static_cast<NodeSyncWorker*>(request->data);
		worker->Execute();
		delete worker;
	}

	std::function<void()> _work;
	uv_async_t _request;

	NAN_DISALLOW_ASSIGN_COPY_MOVE(NodeSyncWorker)
};

#endif /* NODEASYNCWORKER_HPP_ */
