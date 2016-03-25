FROM gcc:latest

MAINTAINER iorch

RUN apt-get update && \
  apt-get install -y --no-install-recommends \
  python-pip \
  python-dev \
  swig

ADD . /AmiGo

RUN cd /AmiGo && \
  make && \
  cd python && \
  make
