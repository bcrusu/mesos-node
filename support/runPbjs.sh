#!/bin/bash

SCRIPTDIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)
MESOS_INCLUDE_DIR=~/work/github/mesos/include
OUTPUT_DIR=$SCRIPTDIR/../generated

if [ -d $OUTPUT_DIR ]; then
  rm -r $OUTPUT_DIR
  mkdir $OUTPUT_DIR
  mkdir $OUTPUT_DIR/v1
fi

pbjs $MESOS_INCLUDE_DIR/mesos/mesos.proto $MESOS_INCLUDE_DIR/mesos/executor/executor.proto $MESOS_INCLUDE_DIR/mesos/scheduler/scheduler.proto -t commonjs -p $MESOS_INCLUDE_DIR > $OUTPUT_DIR/mesos.js

pbjs $MESOS_INCLUDE_DIR/mesos/v1/mesos.proto $MESOS_INCLUDE_DIR/mesos/v1/executor/executor.proto $MESOS_INCLUDE_DIR/mesos/v1/scheduler/scheduler.proto -t commonjs -p $MESOS_INCLUDE_DIR > $OUTPUT_DIR/v1/mesos.js

