**Erzeuger**

Dieses Programm wird von jedem Erzeuger verwendet.
  
- Ein Erzeuger wird dabei über eine abstrakte Klasse in den jeweiligen Erzeugertyp eingeteilt. Dabei wird zwischen
    Atom, Kohle, Solar und Winderzeugern unterschieden.
    - Jeder Typ wird durch einen string mit seinem `typ`, einem string mit dem `namen`, einem int mit der `id`,
      und den beiden booleschen Werten `turnOffPossible` und `status` beschrieben. Außerdem wird in dem Attribut 
      `completeGeneration` die jeweils komplett erzeugte Strommenge gespeichert.
    - Die abstrakte Klasse Erzeuger stellt die virtuelle Methode `getLastHourGeneration()` zur Verfügung. Diese Methode
    ist je nach Typ des Erzeugers implementiert. 
    -  Kohle und Atomkraftwerke können je nach Bedarf von einer Zentrale mit
    einem RPC Aufruf ausgeschaltet werden.
       
- Die Klasse `Simulator` startet einmal pro Stunde einen Thread, der die generierte Strommenge des Erzeugers der letzten
    Stunden ausließt und daraus mithilfe der Methode 
    `messageToJSON(string type, string name, int id, double value, unsigned long long t)` eine Nachricht im JSON Format
    baut. Die Nachricht ist wie folgt aufgebaut: 
    `{"type": "Unternehmen", "name": "FLEISCHER", "id": 123,"value": 2006.550000}`. 
  
- Die Erzeuger kommunizieren über das Interface `ZentralenKommunikation` mit der Zentrale. Beim Senden von Daten rufen
  die Erzeuger die Methode `sendData(string message)` des Interfaces auf.
    - Das Interface `ZentralenKommunikation` wird durch die Klassen `UDPKommunikation` und `MQTTKommunikation` 
    implementiert. 
        * Funktion von `UDPKommunikation`:
            - Die IPv4 Adresse und der Port der Zentrale wird bei der Initialisierung des UPDKommunikationsobjektes 
              übergeben (Aufruf des Konstruktors `UDPKommunikation(int port, std::string address)`).
            - Ein Socket wird mit der Funktion `initSocket()` initialisiert. Der Deskriptor des geöffneten Sockets 
                wird in dem Attribut `socketFD` gespeichert.
            - Die Methode `sendData(string message)` wurde so implementiert, dass der vorher geöffnete Socket verwendet
                wird, um die Daten zur Zentrale zu senden
              
        * Funktion von `MqttKommunikation`:
            - In der Klasse wird eine Verbindung zu dem MQTT-Server mit den übergebenen Parametern hergestellt (`MqttKommunikation(string brokerIP, string name)`).
              Danach wird die Methode `sendData(string message)`, welche die Methode aus ZentralenKommunikation überschreibt, benutzt, um Nachrichten an den Channel des MQTT-Servers zu schicken.
              
- Die Klasse `RpcController` ist bist auf die überschrieben Funktionen, die die Daten für die Remote-Calls liefern, gleich zu der Klasse aus der Zentrale aufgebaut. Bitte dort nachlesen.