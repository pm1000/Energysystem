###
### Build Stage
###
FROM ubuntu:latest AS buildStage

LABEL maintainer = philipp.meier@stud.h-da.de
LABEL maintainer = yannick.brilmayer@stud.h-da.de
LABEL stage = build

# Update all apps and install build deps
RUN apt-get update
RUN apt-get install -y cmake make gcc g++

# Copy the app
COPY src/ /app/src
COPY CMakeLists.txt /app

# Start build process
WORKDIR /app
RUN cmake .
RUN make -f Makefile


###
### Run Stage
###
FROM ubuntu:latest

LABEL maintainer = philipp.meier@stud.h-da.de
LABEL maintainer = yannick.brilmayer@stud.h-da.de

# Copy the exec
COPY --from=buildStage /app/Zentrale /app/

# Mark ports to be exposed
EXPOSE 5000
EXPOSE 9000

# Start the app
WORKDIR /app
ENTRYPOINT ["./Zentrale"]
CMD [""]
