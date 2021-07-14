# LoadBalancer

## Umsetzung
Der LoadBalancer öffnet eine TCP Port, bei dem eingehende Verbindungen akzeptiert werden.
Diese Verbindungen werden mit einem Hash-Verfahren analysiert und einer Ziel-IP-Adresse zugeordnet.
Dann wird zu dieser Adresse eine Verbindung aufgebaut.

Stehen beide Verbindungen werden die Routen der beiden Verbindungen gesetzt. 
Eingehende Daten werden auf ausgehnde Daten umgelenkt und anders herum.

Der LoadBalancer ist komplett auf MultiThreading ausgelegt und kann komplett nicht-blockierend betrieben werden.