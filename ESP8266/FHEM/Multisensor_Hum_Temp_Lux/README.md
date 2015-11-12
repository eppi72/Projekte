# Multisensor (Temperatur, Luftfeuchtigkeit, Helligkeit) #

Bestehend aus:
- ESP8266-01 (auch andere möglich)
- DHT-22 (Temperatur und Luftfeuchtigkeit)
- BH1750 (Lux-Sensor)

Die Sensoren senden im Abstand von zwei Minuten (einstellbar) Ihre Werte an FHEM

Folgende Anpassungen musst du machen:
- In "init.lua" die SSID und das Passwort deines WLAN anpassen
- In "fhem_multisensor.lua" die Server IP und den Telnetport von deinem FHEM anpassen

Der ESP wird mit NodeMCU 0.9.5 (integer Version) geflasht, siehe https://github.com/eppi72/Projekte/tree/master/ESP8266/NodeMCU

