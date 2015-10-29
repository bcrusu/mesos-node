var mesosUtils = require('./mesosUtils.js');

var nativeApi = require('bindings')('mesosApi.node');
var MesosSchedulerDriver = nativeApi.MesosSchedulerDriver;
var MesosExecutorDriver = nativeApi.MesosExecutorDriver;

exports.protos = require('./generated/mesos.js');

// TODO: add all other Scheduler Driver ctor parameters
exports.createSchedulerDriver = function(scheduler) {
    mesosUtils.validateScheduler(scheduler);
    return new MesosSchedulerDriver(scheduler);
}

exports.createExecutorDriver = function(executor) {
    mesosUtils.validateExecutor(executor);
    return new MesosExecutorDriver(executor);
}