FROM fedora:22

MAINTAINER Shaikat Majumdar <sm2774us@gmail.com>

RUN yum -y update && yum clean all

RUN yum -y install boost-devel gcc gcc-c++ libuv-devel git cmake make ncurses-devel
