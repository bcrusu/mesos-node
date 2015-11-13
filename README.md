## mesos-node: Apache Mesos API for Node.js

### Status

Full API bindings consistent with the API provided by Mesos 0.26.0.

### Known issues

Mesos is built against an older version of [http-parser](https://github.com/nodejs/http-parser) than the one used by Node.js and because the implementations are not compatible, segmentation faults are generated at runtime. The quick [fix](https://github.com/bcrusu/mesos/commit/a63561f82ef1f62fc6f7b13157bf2a219db21864) was to use local binding for the http-parser functions.

### Items left to do:

- [ ] More testing
- [ ] npm package
- [ ] CI build system

