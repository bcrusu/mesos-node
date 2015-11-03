var mesosUtils = require('./mesosUtils.js');
var nativeApi = require('bindings')('mesosApi.node');
var protosBuilder = require('./generated/mesos.js');

var MesosSchedulerDriver = nativeApi.MesosSchedulerDriver;
var MesosExecutorDriver = nativeApi.MesosExecutorDriver;

exports.protos = protosBuilder;

exports.createSchedulerDriver = function (scheduler, frameworkInfo, masterAddress, implicitAcknowlegements, credential) {
    mesosUtils.validateScheduler(scheduler);

    if (implicitAcknowlegements === undefined)
        implicitAcknowlegements = true;

    if (credential === undefined)
        return new MesosSchedulerDriver(protosBuilder, scheduler, frameworkInfo, masterAddress, implicitAcknowlegements);
    else
        return new MesosSchedulerDriver(protosBuilder, scheduler, frameworkInfo, masterAddress, implicitAcknowlegements, credential);
}

exports.createExecutorDriver = function (executor) {
    mesosUtils.validateExecutor(executor);
    return new MesosExecutorDriver(protosBuilder, executor);
}