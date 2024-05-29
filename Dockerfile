FROM ubuntu:20.04

# timze zone
RUN ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime

RUN apt-get update && apt-get -y upgrade && \
    apt-get install -y sudo && \
    apt-get install -y build-essential

RUN apt-get -y install wget git cmake g++ gcc \
    apt-get install -y libgoogle-glog-dev libgflags-dev \
    apt-get install -y libatlas-base-dev \
    apt-get install -y libeigen3-dev \
    apt-get install -y libsuitesparse-dev


RUN apt-get -y install python3-dev python3-numpy