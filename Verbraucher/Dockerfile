###
### Build Stage
###
FROM ubuntu:latest AS buildStage

LABEL maintainer = philipp.meier@stud.h-da.de
LABEL maintainer = yannick.brilmayer@stud.h-da.de
LABEL stage = build

# Update all apps and install build deps
RUN apt-get update -y && apt-get install -y wget make gcc g++ git curl build-essential
RUN sh -c "mkdir -p /usr/opt \
    && cd /usr/opt \
    && curl -s -L https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.sh -o cmake.sh \
    && sh cmake.sh --skip-license --prefix=/usr/local"
RUN sh -c "git clone https://github.com/eclipse/paho.mqtt.c.git \
    && cd paho.mqtt.c \
    && git checkout v1.3.8 \
    && cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON -DPAHO_WITH_SSL=OFF -DPAHO_HIGH_PERFORMANCE=ON \
    && cmake --build build/ --target install \
    && ldconfig"
RUN sh -c "git clone https://github.com/eclipse/paho.mqtt.cpp \
    && cd paho.mqtt.cpp \
    && cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON -DPAHO_BUILD_DOCUMENTATION=FALSE -DPAHO_BUILD_SAMPLES=FALSE -DPAHO_WITH_SSL=OFF \
    && cmake --build build/ --target install \
    && ldconfig"


# Copy the app
COPY src/ /app/src
COPY CMakeLists.txt /app

# Start build process
WORKDIR /app
RUN cmake .
RUN make -f Makefile

# Start the app
ENTRYPOINT ["./Verbraucher"]
CMD ["ip=127.0.0.1", "port=5000"]
