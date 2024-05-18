FROM ubuntu:20.04

# timze zone
RUN ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime

RUN apt-get update && apt-get -y upgrade && \
    apt-get install -y sudo && \
    apt-get install -y build-essential

RUN apt-get -y install wget git cmake g++ gcc

RUN apt-get -y install python3-dev python3-numpy