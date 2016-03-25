FROM gcc:latest

MAINTAINER iorch

RUN apt-get update && \
  apt-get install -y --no-install-recommends \
  python3-pip \
  python3-dev \
  swig

ADD . /AmiGo

RUN cd /AmiGo && \
  make && \
  cd python && \
  make
