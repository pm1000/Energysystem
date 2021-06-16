.PHONY: help install clean

help:
	@echo "Befehl: make [clean | install]";

install:
	-docker build -t zentrale:latest Zentrale/
	-docker build -t erzeuger:latest Erzeuger/
	-docker build -t verbraucher:latest Verbraucher/
	-docker build -t energieversorger:latest Energieversorger/

clean:
	-docker image rm zentrale
	-docker image rm verbraucher
	-docker image rm erzeuger
	-docker image rm energieversorger