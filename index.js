function getApi(version) {
    if (version === undefined)
        version = 1;

    switch (version) {
        case 0:
            return require('./src/mesosApiV0.js');
        case 1:
            return require('./src/mesosApiV1.js');
        default:
            throw "Invalid API version provided.";
    }
}

module.exports = getApi;
