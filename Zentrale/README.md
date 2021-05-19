# Projekt Zentrale

## Nutzung der Zentrale

Der Aufruf über den Browser findet über die Adresszeile _http://localhost:9000/_ statt. 
Hier findet sich eine Übersicht aller bisher erkannten Geräte wieder.
Eine detaillierte Auflistung aller Geräte findet sich, wenn man ein Gerät in der Tabelle anwählt oder über _http://localhost:9000/Detail?name=<name>&history=true_.
Der Port des Webservers kann man über einen Parameter beim Programmstart abändern.

Über den UDP Port 5000 können Geräte ihre Daten melden. Die Kommunikation wird per String im JSON-Format geparst übertragen.

## Klassenstruktur

### Zentrale
In der Zentrale werden alle benötigten Komponenten initialisiert und gestartet.
Sowohl Webserver, als auch die Datenkommunikation werden hier organisiert.
Alle konfigurationen des Prozesses finden hier statt.
Funktionen: 

* `Zentrale()`: Der Konstruktor der Klasse.
  Hier wird die Zentrale mit allen erforderlichen Informationen initialisiert (Ports für Web- und UDPServer).
  HTTPContexte für den WeServer werden hier hinzugefügt, sodass sie erreichbar sind, sobald der Webserver gestartet ist.
* `start()`: Startet die Zentrale und alle ihre Threads, in denen die Informationsverarbeitung und Verbindungsverwaltung stattfindet.
  Ein Webserver wird initialisiert und in einem Thread gestartet (siehe Webserver).
  Ein UDPServer wird initialisiert und in einem Thread gestartet (siehe UDPServer).
  Die start()-Methode wird erst zurückkehren, wenn das Programm beendet werden soll.
* `stop()`: Die stop()-Methode setzt in allen Komponenten der Zentrale das Stop-Flag auf true und sorgt somit damit, dass alle Threads beendet werden.
  Nachdem sie aufgerufen wurde beendet sich das Programm, nachdem WebServer und UDPServer gestoppt wurden.


### UDPServer und UDPCallback
Die Klasse `UDPServer` hat folgende Funktionen:
* `init(int port)`: Initialisiert die Klasse und legt einen Socket auf dem Betriebssystem an.
Als Port wird der übergebene Parameter benutzt.
Der Socket wird als Datagramm-Socket auf allen IPv4-Adressen geöffnet und ein Timeout auf den Server von 1s wird eingestellt.
Der zurückgegebene File-Deskriptor wird in als Objektattribut gespeichert.
* `setCallback(UDPCallback*)`: Setzt das Callback, das aufgerufen werden soll, wenn eine Nachricht ankommt.
* `operator()()`: Die Funktion macht das Objekt zu einem Funktor, sodass man das Onjekt als Thread starten kann.
  Sie ruft die Methode run() auf.
* `stop()`: Die Stop-Methode setzt ein Flag in dem Objekt in dem Objekt, das angibt, ob der Socket noch auf eingehende Daten warten soll. Das Flag ist die Stop-Bedingung in der run()-Methode
* `run()`: Hier findet die Main-Loop des Threads statt.
Solange nicht das Stop-Flag gesetzt ist wird von dem Socket gelesen.
Dabei wird ein 1500 langer Buffer zur Verfügung gestellt, in den von dem vorher erstelltem Socket eingelesen wird.
Wurden Bytes empfangen (kein Timout/Fehler erkannt) wird die Objekt-Callback Methode mit den empfangen Daten zum String konvertiert als Parameter aufgerufen.
Bei dem Verlassen der Schleife ist die Aufgabe des Threads fertig (Server kann geschlossen werden) und der Socket wird probiert zu schließen.

Die Klasse `UDPCallback` dient als Interface für andere Klassen eine Nachricht zu verarbeiten. Sie wird aufgerufen, wenn in der run()-Methode des UDPServer eine Nachricht empfangen wird.
* `processMessage (string)`: Zu überschreibende Funktion, die aufgerufen wird, wenn eine Nachricht empfangen wird.


### WebServer

Der Aufruf des Webservers erfolt unter folgender Adresse: _http://localhost:9000/_.
Der Port wird dem WebServer übergeben und kann sich ändern.

##### WebServer Klasse
Die Klasse `WebServer` kümmert sich um alle eingehenden TCP-Verbindungen und darauffolgende HTTP-Anfragen. Funktionen:

* `init(int)`: Initialisiert die Klasse und legt einen Socket auf dem Betriebssystem an.
  Als Port wird der übergebene Parameter benutzt.
  Der Socket wird als Stream-Socket auf allen IPv4-Adressen geöffnet und ein Timeout auf den Server von 1s wird eingestellt.
  Der zurückgegebene File-Deskriptor wird in als Objektattribut gespeichert.
* `setCallback(UDPCallback*)`: Setzt das Callback, das aufgerufen werden soll, wenn eine Nachricht ankommt.
* `operator()()`: Die Funktion macht das Objekt zu einem Funktor, sodass man das Onjekt als Thread starten kann.
  Sie ruft die Methode run() auf.
* `stop()`: Die Stop-Methode setzt ein Flag in dem Objekt in dem Objekt, das angibt, ob der Socket noch auf eingehende Daten warten soll. Das Flag ist die Stop-Bedingung in der run()-Methode
* `run()`: Hier findet die Main-Loop des Threads statt.
  Solange nicht das Stop-Flag gesetzt ist, werden eingehende Verbindungen von dem Socket angenommen.
  Wenn kein Fehler erkannt wurde (Timeout, anderer Fehler), so wird der neu-erstellte Socket der Klasse HTTPIntepreter übergeben und als neuer Thread unabhängig gestartet.
  Danach wird auf die nächste Verbindung gewartet.
  Wenn das Stop-Flag gesetzt ist, wird die Schleife bei nächster Gelegenheit verlassen und der Socket zum Empfangen der Daten geschlossen.

##### HTTPIntepreter
Die Klasse `HttpIntepreter` bekommt eine Verbindung übergeben und kümmert sich dann um diese. 
Die Verbindung ist eine TCP-Verbindung, die von der Klasse `WebServer` kommt.
Sie bearbeitet diese Abfragen und leitet dann korrekte Anfragen an den HttpContextHandlerController weiter, wo die Inhalte ermittelt werden.
Funktionen:

* `operator()()`: Macht das Objekt zu einem Funktor, sodass sie einfach per Thread gestartet werden kann.
Nur das Objekt muss dem Thread übergeben werden. Sie ruft die Methode run() auf.
* `run()`: Die run()-Methode akzeptiert genau eine eingehende Nachricht von dem Socket.
  Dabei wird solange von dem Thread gelesen, bis das Endzeichen von einer HTTP-Anfrage erkannt wird (\r\n\r\n).
  Die eingelesenen Zeichen werden in einem String gespeichert.
  Nach vollständigem einlesen der Nachricht wird die Nachricht verarbeitet.
  Solange die Zeile nicht leer ist (Ende der Header) wird diese Zeile als Header erkannt und in einer Map gespeichert.
  Nachdem alle Header eingelesen sind, wird auf GET geprüft.
  Sofern eine Unterstützte HTTP Anfrage bearbeitet wurde, werden die Antwort-Header vorbereitet und die Antwort an sich mit der Methode processHTTP() ermittelt.
  Die Antwort wird an den Client geschickt und der Socket anschließend geschlossen (keep-alive oder anderer Header werden ignoriert).
* `processHTTP(unordered_map<string, string> &headers)`: Die HTTP Anfrage wird mit den angegebenen Parametern bearbeitet.
  Der angefragte Pfad wird extrahiert und dann der rückzugebende Inhalt von dem ContextController ermittelt.
  Die Antwort wird per string zurückgegeben.
  


##### HTTPContextHandlerController und HTTPContextHandler
Die Klasse `HttpContextHandlerController` ergänzt die Funktionalität der Klasse Webserver. 
Sie führt die Funktionen verschiedene Seiten passend zum angefragten Pfad zurückzugeben.
Funktionen:

* `addContext(string path, HTTPContextHandler* handler)`: Fügt einen neuen HTTPContextHandler hinzu, der unter dem übergebenen Path erreichbar ist.
* `getContext(string& path, string &args)`: Gibt einen String mit der Antwort zurück des HTTPContextHandler zurück.
  Der HTTPContextHandler wird dabei anhand des path ausgewählt.
  Außerdem werden die Argumente, die am Path mit anhängen übergeben, um diese zu verarbeiten.
* `setContextNotFoundErrorPage(HttpContextHandler* handler)`: Setzt einen Standard HTTPContextHandler, der ausgeführt werden soll, wenn kein anderer unter dem path erreichbar ist.

Die Klasse `HttpContextHandler` dient als Interface für den HttpContextHandlerController. 
Dieses Interface kann benutzt werden, um den Inhalt eines Http-Aufrufes zu bestimmen.
Das Interface muss einem HttpContextHandlerController übergeben werden (per addContext() mit einem Pfad, unter dem es erreichbar ist oder als Fallback-Errorpage).
Funktionen:

* `getContent(string &args)`: Die Methode muss überschrieben werden. 
  Sie gibt den benutzerdefinierten Inhalt für die erstellte Seite zurück. 
  Argumente des HTTP-Aufrufes werden als Parameter übergeben.
  

#### HTMLGenerator
TODO: PM bitte ausformulieren.


### KomponentenController und Komponenten
#### KomponentenCtonroller
TODO: PM bitte ausformulieren

#### Komponenten
TODO: PM bitte ausformulieren