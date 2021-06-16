###
### Build Stage
###
FROM ubuntu:latest AS buildStage

LABEL maintainer = philipp.meier@stud.h-da.de
LABEL maintainer = yannick.brilmayer@stud.h-da.de
LABEL stage = build

# Update all apps and install build deps
FROM gcc:8.2
RUN apt update -y && apt-get install -y wget
RUN sh -c "mkdir -p /usr/opt && cd /usr/opt \
  && curl -s -L https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.sh -o cmake.sh \
  && sh cmake.sh --skip-license --prefix=/usr/local"

Run mkdir /app
RUN mkdir /app/generated

# Copy the app
COPY src/ /app/src
COPY CMakeLists.txt /app

# Start build process
WORKDIR /app
RUN cmake -j .
RUN make -j -f Makefile


###
### Run Stage
###
FROM ubuntu:latest

LABEL maintainer = philipp.meier@stud.h-da.de
LABEL maintainer = yannick.brilmayer@stud.h-da.de

# Copy the exec
COPY --from=buildStage /app/Erzeuger /app/

# Start the app
WORKDIR /app
ENTRYPOINT ["./Energieversorger"]
CMD ["ip=127.0.0.1", "port=5000"]
