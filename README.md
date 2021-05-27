# Projekt zum Modul Verteilte Systeme

## Projektaufbau
Das Projekt besteht aus folgenden Unterprojekten:

* `Zentrale`: Die Zentrale übbernimmt die Kommunikation zwischen den Komponenten. 
Sie verwaltet alle Komponenten, die sich bei ihr angemeldet haben und stellt einen WebServer zur Verfügung, um auf diese Daten zuzugreifen. 
[Link zum Projekt](Zentrale/)
* `Erzeuger`: Der Erzeuger sorgt dafür, dass koninuierlich Daten an die entsprechende Zentrale gesendet werden. Diese werden Dabei berechnet und sollen eine möglichst genaue Simulation darstellen. 
[Link zum Projekt](Erzeuger/)
* `Verbraucher`: Der Verbraucher sorgt dafür, dass koninuierlich Daten an die entsprechende Zentrale gesendet werden. Diese werden Dabei berechnet und sollen eine möglichst genaue Simulation darstellen. 
[Link zum Projekt](Verbraucher/)


## Projekt starten
Um das Projekt starten zu können wird Docker, Docker-Compose und Git auf dem Zielrechner benötigt. Alle Befehle müssen mit einem User ausgeführt werden, der Docker verwenden darf.

1. Git-Repo clonen.
2. In das Hauptverzeichnis des Git-Repos navigieren.
3. Befehl `make install` ausführen
4. Docker-Container starten mit Compose
    * Im Vordergrund starten: `docker-compose up` ausführen
    * Im Hintergrund starten: `docker-compose up -d` ausführen
5. Zum Beenden der Services
    * Im Vordergrund: **Ctrl + C ** auf der Tastatur drücken
    * Im Hintergrund: `docker-compose down` ausführen
   

Zugriff auf die Webseite auf das Projekt, wenn per docker-compose.yml File gestartet: http://172.16.1.1:9000/


## Sonstige Informationen

Erstellt von Philipp Meier und Yannick Brilmayer.
