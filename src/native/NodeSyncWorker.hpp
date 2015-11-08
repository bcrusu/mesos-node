#ifndef NODEASYNCWORKER_HPP_
#define NODEASYNCWORKER_HPP_

#include <functional>
#include <nan.h>

namespace mesosNode {

class NodeSyncWorker {
public:
	NodeSyncWorker(std::function<void()> work) :
			_work(work) {
		_handle.data = this;
	}

	void Run() {
		uv_async_init(uv_default_loop(), &_handle, AsyncExecute);
		uv_async_send(&_handle);
	}

private:
	void Execute() {
		_work();
	}

	static void CloseHandleCallback(uv_handle_t* handle){
		auto worker = static_cast<NodeSyncWorker*>(handle->data);
		delete worker;
	}

	static void AsyncExecute(uv_async_t* handle) {
		auto worker = static_cast<NodeSyncWorker*>(handle->data);
		worker->Execute();

		uv_close((uv_handle_t*)handle, CloseHandleCallback);
	}

	std::function<void()> _work;
	uv_async_t _handle;

	NAN_DISALLOW_ASSIGN_COPY_MOVE(NodeSyncWorker)
};

}

#endif /* NODEASYNCWORKER_HPP_ */
