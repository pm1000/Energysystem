**Verbraucher**

Dieses Programm wird von jedem Verbraucher verwendet.

- Ein Verbraucher wird dabei über eine abstrakte Klasse in den jeweiligen Verbrauchertyp eingeteilt. Dabei wird zwischen
  Haushalten und Unternehmen unterschieden.
    - Jeder Typ wird durch einen string mit seinem `type`, einem string mit dem `namen` und einem int mit der `id`
      beschrieben. Das `enum Weekday{}` speichert den jeweiligen Wochentag. Dieser wird zusammen mit `time` verwendet, 
      um den Verbrauch zu verschiedenen Zeitpunkten zu simulieren. Außerdem wird in dem Attribut `completeConsumption` 
      die jeweils komplett verbrauchte Strommenge gespeichert.
    - Die abstrakte Klasse Verbraucher stellt die virtuelle Methode `getLastHourConsumption()` zur Verfügung. 
      Diese Methode ist je nach Typ des Verbrauchers implementiert und gibt den Stromverbrauch der letzten Stunde 
      zurück.

- Die Klasse `Simulator` startet einmal pro Stunde einen Thread, der die verbrauchte Strommenge des Verbrauchers der
  letzten Stunden ausließt und daraus mithilfe der Methode
  `messageToJSON(string type, string name, int id, double value, unsigned long long t)` eine Nachricht im JSON Format
  baut. Die Nachricht ist wie folgt aufgebaut:
  `{"type": "Unternehmen", "name": "FLEISCHER", "id": 123,"value": 2006.550000}`.

- Die Verbraucher kommunizieren über das Interface `ZentralenKommunikation` mit der Zentrale. Beim Senden von Daten 
  rufen die Verbraucher die Methode `sendData(string message)` des Interfaces auf.
    - Das Interface `ZentralenKommunikation` wird durch die Klassen `UDPKommunikation` und `MQTTKommunikation`
      implementiert.
        - Funktion von `UDPKommunikation`:
            - Die IPv4 Adresse und der Port der Zentrale wird bei der Initialisierung des UPDKommunikationsobjektes
              übergeben (Aufruf des Konstruktors `UDPKommunikation(int port, std::string address)`).
            - Ein Socket wird mit der Funktion `initSocket()` initialisiert. Der Deskriptor des geöffneten Sockets
              wird in dem Attribut `socketFD` gespeichert.
            - Die Methode `sendData(string message)` wurde so implementiert, dass der vorher geöffnete Socket verwendet
              wird, um die Daten zur Zentrale zu senden.