# Multisensor (Temperatur, Luftfeuchtigkeit, Helligkeit): #

Bestehend aus:
- ESP8266-01 (auch andere möglich)
- DHT-22 (Temperatur und Luftfeuchtigkeit)
- BH1750 (Lux-Sensor)

Die Sensoren senden im Abstand von zwei Minuten Ihre Werte an FHEM

Folgende Anpassungen musst du machen:
- Im "init.lua" File, die SSID und das Passwort deines WLAN anpassen
- Im "fhem_multisensor.lua" File die Server IP und den Telnetport von deinem FHEM anpassen

Der ESP wird mit NodeMCU 0.9.5 (integer Version) geflasht.

