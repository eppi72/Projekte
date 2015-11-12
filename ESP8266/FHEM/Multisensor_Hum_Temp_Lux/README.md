# Multisensor (Temperatur, Luftfeuchtigkeit, Helligkeit): #

Bestehend aus:
- ESP8266-01 (auch andere möglich)
- DHT-22 (Temperatur und Luftfeuchtigkeit)
- BH1750 (Lux-Sensor)

Die Sensoren senden im Abstand von zwei Minuten Ihre Werte an FHEM

Folgende Anpassungen musst du machen:
- Im init File, die SSID und das PAsswort deines WLAN anpassen
- Im File Multisensor die Server IP und den Telnetport von FHEM anpassen

Der ESP wird mit NodeMCU 0.9x (integer Version) geflasht.

