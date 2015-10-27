function getApiV0() {
    var result = {};

    result.protos = require('./generated/mesos.js');
    //TODO: native

    return result;
}

function getApiV1() {
    var result = {};

    result.protos = require('./generated/v1/mesos.js');
    //TODO: native

    return result;
}

function getApi(version) {
    if (version.isUndefined())
        version = 0;

    switch (version) {
        case 0:
            return getApiV0();
        case 1:
            return getApiV1();
        default:
            throw "Invalid API version provided.";
    }
}

module.exports = getApi;