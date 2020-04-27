# Die HsKA unterstützt die Bewerbung der Stadt Karlsruhe, um den Status als UNESCO City of Media Arts. Für diesen Anlass werden sogenannte “Swimming-Pixel” entwickelt. Diese sollen später auf dem Schlossteich schwimmen und je nach Position verschiedene Farbsequenzen abspielen. Dadurch soll es möglich sein, Bilder oder Farbspiele zu erzeugen.

Dokumentation: http://hit-karlsruhe.de/hit-info/info-ss20/PixelAnst/

## Getting Started
Das Projekt ist in zwei Bereiche aufgeteilt:
1. Schwimmende_Pixel_ESP 32 dazu gehört:
Verbindung mit Wifi
Verbindung mit Mosquitto (Broker)
Erhalten der Farben mit Koordinaten vom Host
Neue Farbe nach aktueller Position filtern
Ansteuerung des RGB-Rings
Ansteuerung des Oled Displays
 
2. Host dazu gehört:
Verbindung mit Mosquitto (Broker)
Dasboard für die Eingabe
Eingabe von Bildern als Link
Eingabe und senden von Farben an alle Pixel
Eingabe und senden von festen Koordinaten an alle Pixel für Tests
Alle Pixel ausschalten
Senden von Beispielbildern

## Sonstiges
Der Swimming Pixel ESP 32 Code wurde mit VS Code und der Platform IO Erweiterung umgesetzt. Der Host wurde mit Node-RED umgesetzt. Als Schnittstelle zwischen Host und Pixel wurde Mosquitto als Broker verwendet. Der Code ist ausreichend kommentiert und wird zudem im YouTube Video erklärt.
 
Inbetriebnahme und Funktion: https://youtu.be/rOyfbNaR32Y
