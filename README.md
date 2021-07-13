# Projekt zum Modul Verteilte Systeme

Anmerkungen für den Prof zu zusätzlichen erledigten Aufgaben befinden sich in [Anmerkungen für den Prof.txt](Anmerkung für Prof.txt)

## Projektaufbau
Das Projekt besteht aus folgenden Unterprojekten:

* `Zentrale`: Die Zentrale übbernimmt die Kommunikation zwischen den Komponenten. 
Sie verwaltet alle Komponenten, die sich bei ihr angemeldet haben und stellt einen WebServer zur Verfügung, um auf diese Daten zuzugreifen. 
[Link zum Projekt](Zentrale/)
* `Erzeuger`: Der Erzeuger sorgt dafür, dass koninuierlich Daten an die entsprechende Zentrale gesendet werden. Diese werden Dabei berechnet und sollen eine möglichst genaue Simulation darstellen. 
[Link zum Projekt](Erzeuger/)
* `Verbraucher`: Der Verbraucher sorgt dafür, dass koninuierlich Daten an die entsprechende Zentrale gesendet werden. Diese werden Dabei berechnet und sollen eine möglichst genaue Simulation darstellen. 
[Link zum Projekt](Verbraucher/)
* `Energieversorger`: Mit dem Energieversorger als externen Client kann man sich per RPC die Daten der Komponenten und die Werte aller Komponenten abfragen lassen.
  [Link zum Projekt](Energieversorger/)
* `LoadBalancer`: Der LoadBalancer teilt eingehenden Traffic auf die Zentralen auf. 
  [Link zum Projekt](LoadBalancer/)


## Projekt starten
Um das Projekt starten zu können wird Docker, Docker-Compose und Git auf dem Zielrechner benötigt.

1. Git-Repo clonen.
2. In das Hauptverzeichnis des Git-Repos navigieren.
3. Befehl `make install` ausführen
4. Docker-Container starten mit Compose
    * Im Vordergrund starten: `docker-compose up` ausführen
    * Im Hintergrund starten: `docker-compose up -d` ausführen
    * Um den Energieversorger zu starten: `docker-compose run energieversorger1` ausführen (am besten mit den anderen Sachen im Hintergrund)
    * Um einen Ausfall einer Zentrale zu simulieren: `docker-compose stop zentrale1`, dann `docker-compose start zentrale1` (gestartet im Hintergrund).
5. Zum Beenden der Services
    * Im Vordergrund: **Ctrl + C** auf der Tastatur drücken
    * Im Hintergrund: `docker-compose down` ausführen
   

## Zugriff auf das Projekt
Der Zugriff auf die WebPages kann über die einzelnen Zentralen geschehen:
* Zentrale1: http://172.16.1.1:9000
* Zentrale2: http://172.16.1.2:9000
* Zentrale3: http://172.16.1.3:9000

oder über den LoadBalancer:
* LoadBalancer: http://172.16.0.3:10000


## Sonstige Informationen
Fertig gebaute Container werden in der Container-Registry vom h-da Gitlab bereitgestellt.
Falls man die Projekte doch selber bauen möchte kann man auch den Befehl `make build` benutzen und sich die Images selber bauen.

Erstellt von Philipp Meier und Yannick Brilmayer.
