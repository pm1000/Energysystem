.PHONY: help install build clean pushContainer

help:
	@echo "Befehl: make [clean | install | build | pushContainer]";

install:
	docker login -u container -p yx_b-aEqL9MV4x3ydcf5 registry.code.fbi.h-da.de
	docker pull registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/zentrale:latest
	docker pull registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/erzeuger:latest
	docker pull registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/verbraucher:latest
	docker pull registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/energieversorger:latest


build:
	-make -j build_zentrale build_erzeuger build_verbraucher build_energieversorger

build_zentrale:
	-docker build -t registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/zentrale:latest Zentrale/
build_erzeuger:
	-docker build -t registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/erzeuger:latest Erzeuger/
build_verbraucher:
	-docker build -t registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/verbraucher:latest Verbraucher/
build_energieversorger:
	-docker build -t registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/energieversorger:latest Energieversorger/


clean:
	-docker image rm zentrale
	-docker image rm verbraucher
	-docker image rm erzeuger
	-docker image rm energieversorger


pushContainer:
	docker login -u container -p yx_b-aEqL9MV4x3ydcf5 registry.code.fbi.h-da.de
	docker push registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/zentrale:latest
	docker push registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/erzeuger:latest
	docker push registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/verbraucher:latest
	docker push registry.code.fbi.h-da.de/istyabril/verteiltesysteme-burchard-ss21-brilmayermeier/energieversorger:latest