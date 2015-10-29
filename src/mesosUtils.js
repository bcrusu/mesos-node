var EventEmitter = require("events");

exports.validateScheduler = function (scheduler){
    validateEventEmitter(scheduler);
}

exports.validateExecutor = function (executor){
    validateEventEmitter(executor);
}


function validateEventEmitter(ee){
    if (!(ee instanceof EventEmitter))
        throw "Invalid argument. Expected EventEmitter instance.";
}