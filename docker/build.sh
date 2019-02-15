#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-seedcore/seed}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/seedd docker/bin/
cp $BUILD_DIR/src/seed-cli docker/bin/
cp $BUILD_DIR/src/seed-tx docker/bin/
strip docker/bin/seedd
strip docker/bin/seed-cli
strip docker/bin/seed-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
