# Projekt Zentrale

## Nutzung der Zentrale

Der Aufruf über den Browser findet über die Adresszeile _http://localhost:9000/_ statt. 
Hier findet sich eine Übersicht aller bisher erkannten Geräte wieder.
Eine detaillierte Auflistung aller Geräte findet sich, wenn man ein Gerät in der Tabelle anwählt oder über _http://localhost:9000/Detail?name=<name>&history=true_.
Der Port des Webservers kann man über einen Parameter beim Programmstart abändern.

Über den UDP Port 5000 können Geräte ihre Daten melden. Die Kommunikation wird per String im JSON-Format geparst übertragen.

## Synchronisierung und Verteilen der Daten
Bei einem Start einer Zentralen werden die Daten von anderen Zentralen (per Programmparameter übergeben) über einen RPC-Call angefordert.
Ist die Zentrale hochgefahren bereit und hat Daten, so werden diese an die anfragende Zentrale per MQTT gesendet.

Während der gesamten Dauer empfängt eine Zentrale auch nur Daten von ihren Komponenten. 
Diese werden dann per MQTT auch an die anderen bekannten Zentralen gesendet.
Fällt eine Zentrale aus, so stehen die Daten der Komponenten, die nur an diese Zentrale senden nicht mehr zur Verfügung über den zeitraum hinweg.


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
* `processMessageUdp (string)`: Zu überschreibende Funktion, die aufgerufen wird, wenn eine Nachricht empfangen wird.



### RPCServer

#### Proto File
Die Proto files finden sich in dem `src/proto` Ordner wieder und beschreiben die RPC-Aufrufe.
- `erzeuger.proto` beschreibt die Kommunikation zwischen Erzeuger und Zentrale.
  Hier kann man mit `SetStatus()` den jeweiligen Erzeuger ein- und ausschalten
- `rpcServer.proto` beschreibt die Kommunikation zwischen Energieversorger und Zentrale.
  Hier können aktuelle Daten der Erzeuger/Verbaucher angefragt werden.
  `GetKomponentenIDs` liefert eine Liste nur mit den Ids aller Komponenten zurück.
  `GetKomponente` liefert die genauen Daten der Komponenten zurück.
  `GetKomponentenWerte` liefert die Werte/Daten der jeweiligen Komponente zurück.
  
Die Proto-Files werden automatisch beim Build-Vorgang in den generated Ordner abgelegt und eingebunden.

#### RpcServer
Die Klasse RpcServer kümmert sich um die Verbindung/Bereitstellung des RPC-Dienstes für den Energieversorger.
Sie wird in der Klasse Zentrale gestartet und verwaltet.
Sie erbt von der Klasse `Komponente::Service`, die aus dem Service aus der Proto-File entsteht.
Die beinhaltet folgende Methoden:

- `init()`: Initialisiert die Klasse.
  Übergibt einen Port, wo der RPC-Server gestartet werden soll und den Komponentencontroller, der für Datenzugriffe benutzt werden soll.
- `run()`: Startet den eigentlichen Prozess, der in einem Thread gestartet werden kann.
- `stop()`: Stoppt den RPC-Server und beendet den Dienst.
- Die Methoden `GetKomponentenIDs()`, `GetKomponente()` und `GetKomponentenWerte()` sind überschriebene Methoden aus der Service Klasse unseres Packages aus der Proto File.
  Sie werden bei einem Remote-Call aufgerufen.
  Hier finden die eigentlichen Datenaufrufe statt.

#### ErzeugerRpcClient
Die Klasse ErzeugerRpcClient ist für die Remote Calls auf die Erzeuger zuständig. 
Sie wird aus einem Zugriff über HTTP aufgerufen.
Die Verbindung des HTTP-Aufrufes und des RPC-Calls finden in der Zentrale statt, wo Pfad des Webservers ein besonderes Verhalten zugeordnet wird (ähnlich einem REST-Call, interne SetStatus-Klasse).
Hier wird die Verbindung zu den Erzeugern per RPC verwaltet.
Sie hat folgende Methoden:

- `initRpc()`: Hier wird die Verbindung zu dem RPC-Server im Erzeuger deklariert und ein Channel (Stub) erzeugt.
- `changeStatus()`: Über die eindeutige Komponenten-ID wird hier die SetStatus()-Methode aus der Proto-File aufgerufen und ein Remote-Call abgesetzt.
  Der Status der jeweiligen Komponente wird dabei geändert.


### MQTT

#### Einbinden
Die MQTT-Funktion bedarf beim Bauen einer Installation auf dem Host-Rechner. 
Bei einem Bauen in den Dockerfiles wird es automatisch installiert.

#### Server
Die MQTT Funktionalität bedarf keiner eigenen Klasse.
Der MQTT-Client wird in der Zentrale gestartet und verwaltet.
Die `start()`-Methode der Zentrale startet den MQTT-Client, der sich auf den MQTT-Server verbindet, der als Attribut in der Zentrale gespeichert wird.
Die Serveradresse und Client-Id werden als Parameter in der Methode `setMqttProperties()` gesetzt.
Als Callback für Connection-Events und eingehende Nachrichten wird die Klasse `KomponentenController` verwendet.
Sie verwaltet die Events und verarbeitet die Nachrichten.
Die `stop()`-Methode stoppt den Server.



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

* `addContext(string path, HTTPContextHandler* handler)`: Fügt einen neuen HTTPContextHandler hinzu, der unter dem 
  übergebenen Path erreichbar ist.
* `getContext(string& path, string &args)`: Gibt einen String mit der Antwort zurück des HTTPContextHandler zurück.
  Der HTTPContextHandler wird dabei anhand des path ausgewählt.
  Außerdem werden die Argumente, die am Path mit anhängen übergeben, um diese zu verarbeiten.
* `setContextNotFoundErrorPage(HttpContextHandler* handler)`: Setzt einen Standard HTTPContextHandler, der ausgeführt 
  werden soll, wenn kein anderer unter dem path erreichbar ist.

Die Klasse `HttpContextHandler` dient als Interface für den HttpContextHandlerController. 
Dieses Interface kann benutzt werden, um den Inhalt eines Http-Aufrufes zu bestimmen.
Das Interface muss einem HttpContextHandlerController übergeben werden (per addContext() mit einem Pfad,
unter dem es erreichbar ist oder als Fallback-Errorpage).
Funktionen:

* `getContent(string &args)`: Die Methode muss überschrieben werden. 
  Sie gibt den benutzerdefinierten Inhalt für die erstellte Seite zurück. 
  Argumente des HTTP-Aufrufes werden als Parameter übergeben.
  

#### HTMLGenerator
Die Klasse `HTMLGenerator` liefert beim Aufruf der Methode `generateMainPage()` die Startseite der Website aus. Diese
HTML Seite enthält alle derzeit verbunden Erzeuger und Verbraucher. Die Methode 
`string generateSubPage(string& name, bool history)` gibt je nach übergebenen Namen eine Übersichtsseite der jeweiligen
Komponente zurück. Auf dieser Übersichtsseite sind alle gemeldeten Daten der jeweiligen Komponenten sichtbar.


### KomponentenController und Komponenten
#### KomponentenController
Der `KomponentenController` dient zur Verwaltung von allen Komponenten. Die Komponenten sind in einer Map gespeichert.
Die ID jeder Komponente dient dazu als Key. Außerdem findet ein Mapping zwischen dem Namen der Komponente und der ID 
statt. Außerdem implementiert die Klasse `KomponentenController` die Methode
`void processMessageUdp(std::string ip, std::string message)` vom Interface `UDPCallback`. Diese Methode wird bei jeder
neu eingegangen Nachricht aufgerufen. Innerhalb der Methode findet ein Parsing der Nachricht statt und die übermittelten
Werte werden der jeweiligen Komponente zugeordnet. Falls die Komponente noch unbekannt ist, so wird diese angelegt und
in der Map gespeichert. Außerdem wird nach dem Einfügen von neuen Daten bei jeder Komponente geprüft, ob die Nachrichtenids
in der richtigen Reihenfolge sind, oder ob Nachrichten verloren gegangen sind. Falls dies passiert ist, wird ein neuer
Thread gestartet, der die fehlenden Nachrichten bei den Komponenten nochmals anfordert. 
Die Methode `message_arrived()`, die von der Vererbung von `mqtt::callback` kommt ist eine Callback-Funktion für den MQTT-Service und kümmert sich um eingehende Nachrichten.
Sie verarbeitet eingehende Nachrichten.

#### Komponenten
In dieser Klasse werden alle grundlegenden Informationen zu einer Komponente gespeichert (`string name`, `int id`, 
`string type`, `string ip`). Außerdem werden in der Map `std::map<unsigned long long,double> values;` die gemeldeten 
Werte mit ihren Timestamp als Schlüssel gespeichert. Der Vector `std::vector<int> maxHeap` dient zum detektieren von 
fehlenden Nachrichten. Die Methode `virtual void addNewValue(unsigned long long timestamp, double value)` wird vom 
`KomponentenController` bei jeder neu eingetroffenen Nachricht aufgerufen und fügt das neue Wertepaar ein. Auch die 
Methode `std::vector<int> checkMissingMsg(int msgID)` wird nach jeder eingegangen Nachricht aufgerufen und prüft, dass 
alle Nachrichten vorhanden sind.