# Lichtsensor (Helligkeit) #

Bestehend aus:
- ESP8266-01 (auch andere möglich)
- BH1750 (Lux-Sensor)

Der Sensor sendet im Abstand von zwei Minuten (einstellbar) seine Werte an FHEM

Folgende Anpassungen musst du machen:
- In "init.lua" die SSID und das Passwort deines WLAN anpassen
- In "fhem_bh1750.lua" die Server IP und den Telnetport von deinem FHEM anpassen, sowie das den Namen deines FHEM-Device  anpassen (bei mir Sensor_Licht).

Der ESP wird mit NodeMCU 0.9.5 (integer Version) geflasht, siehe https://github.com/eppi72/Projekte/tree/master/ESP8266/NodeMCU

