var nativeApi = require('bindings')('mesosApi.node');
var exports = {};
module.exports = exports;

exports.protos = require('./generated/mesos.js');

exports.createSchedulerDriver = function(scheduler) {
	validateScheduler(scheduler);
	//TODO
}

exports.createExecutorDriver = function(executor) {
	validateExecutor(executor);
	//TODO
}

// --- private ---

function validateScheduler(scheduler){
}

function validateExecutor(executor){
}
