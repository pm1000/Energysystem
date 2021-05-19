# Projekt Erzeuger

## Klassenstruktur

### Zentrale
In der Zentrale werden alle benötigten Komponenten initialisiert und gestartet.
Sowohl Webserver, als auch die Datenkommunikation werden hier organisiert.
Alle konfigurationen des Prozesses finden hier statt.


### UDPServer und UDPCallback
Die Klasse `UDPServer` hat folgende Funktionen:
* `init(int port)`: Initialisiert die Klasse und legt einen Socket auf dem Betriebssystem an.
Als Port wird der übergebene Parameter benutzt.
Der Socket wird als Datagramm-Socket auf allen IPv4-Adressen geöffnet und ein Timeout auf den Server von 1s wird eingestellt.
Der zurückgegebene File-Deskriptor wird in als Objektattribut gespeichert.
* `setCallback(UDPCallback*)`: Setzt das Callback, das aufgerufen werden soll, wenn eine Nachricht ankommt.
* `operator()()`: Die Funktion macht das Objekt zu einem Funktor, sodass man das Onjekt als Thread starten kann.
* `stop()`: Die Stop-Methode setzt ein Flag in dem Objekt in dem Objekt, das angibt, ob der Socket noch auf eingehende Daten warten soll. Das Flag ist die Stop-Bedingung in der run()-Methode
* `run()`: Hier findet die Main-Loop des Threads statt.
Solange nicht das Stop-Flag gesetzt ist wird von dem Socket gelesen.
Dabei wird ein 1500 langer Buffer zur Verfügung gestellt, in den von dem vorher erstelltem Socket eingelesen wird.
Wurden Bytes empfangen (kein Timout/Fehler erkannt) wird die Objekt-Callback Methode mit den empfangen Daten zum String konvertiert als Parameter aufgerufen.
Bei dem Verlassen der Schleife ist die Aufgabe des Threads fertig (Server kann geschlossen werden) und der Socket wird probiert zu schließen.

Die Klasse `UDPCallback` dient als Interface für andere Klassen eine Nachricht zu verarbeiten. Sie wird aufgerufen, wenn in der run()-Methode des UDPServer eine Nachricht empfangen wird.
* `processMessage (string)`: Zu überschreibende Funktion, die aufgerufen wird, wenn eine Nachricht empfangen wird.


### WebServer
##### WebServer Klasse
Die Klasse `WebServer` kümmert sich um alle eingehenden TCP-Verbindungen und darauffolgende HTTP-Anfragen. Funktionen:

* `init(int port)`: Initialisiert die Klasse und legt einen Socket auf dem Betriebssystem an.
  Als Port wird der übergebene Parameter benutzt.
  Der Socket wird als Stream-Socket auf allen IPv4-Adressen geöffnet und ein Timeout auf den Server von 1s wird eingestellt.
  Der zurückgegebene File-Deskriptor wird in als Objektattribut gespeichert.
* `setCallback(UDPCallback*)`: Setzt das Callback, das aufgerufen werden soll, wenn eine Nachricht ankommt.
* `operator()()`: Die Funktion macht das Objekt zu einem Funktor, sodass man das Onjekt als Thread starten kann.
* `stop()`: Die Stop-Methode setzt ein Flag in dem Objekt in dem Objekt, das angibt, ob der Socket noch auf eingehende Daten warten soll. Das Flag ist die Stop-Bedingung in der run()-Methode
* `run()`: Hier findet die Main-Loop des Threads statt.
  Solange nicht das Stop-Flag gesetzt ist, werden eingehende Verbindungen von dem Socket angenommen.
  Wenn kein Fehler erkannt wurde (Timeout, anderer Fehler), so wird der neu-erstellte Socket der Klasse HTTPIntepreter übergeben und als neuer Thread unabhängig gestartet.
  Danach wird auf die nächste Verbindung gewartet.
  Wenn das Stop-Flag gesetzt ist, wird die Schleife bei nächster Gelegenheit verlassen und der Socket zum Empfangen der Daten geschlossen.

##### HTTPContextHandlerController
Die Klasse `HttpContextHandlerController` ergänzt die Funktionalität der Klasse Webserver. Sie führt die ...