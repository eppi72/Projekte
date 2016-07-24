/*******************************************************************************
 * Controller Plugin for "ESP Easy": FHEM TELNET
 * Modified version of "Nodo Telnet CPLUGIN"
 * Copyright 2016 eppi (https://forum.fhem.de/index.php?action=profile;u=9)
 *******************************************************************************
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You received a copy of the GNU General Public License along with this program in file 'License.txt'..
******************************************************************************/

#define CPLUGIN_010
#define CPLUGIN_ID_010         10
#define CPLUGIN_NAME_010       "FHEM TELNET"

boolean CPlugin_010(byte function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {
    case CPLUGIN_PROTOCOL_ADD:
      {
        Protocol[++protocolCount].Number = CPLUGIN_ID_010;
        Protocol[protocolCount].usesMQTT = false;
        Protocol[protocolCount].usesAccount = false;
        Protocol[protocolCount].usesPassword = true;
        Protocol[protocolCount].defaultPort = 7072;
        break;
      }

    case CPLUGIN_GET_DEVICENAME:
      {
        string = F(CPLUGIN_NAME_010);
        break;
      }
      
    case CPLUGIN_PROTOCOL_SEND:
      {
        char log[80];
        boolean success = false;
        char host[20];
        sprintf_P(host, PSTR("%u.%u.%u.%u"), Settings.Controller_IP[0], Settings.Controller_IP[1], Settings.Controller_IP[2], Settings.Controller_IP[3]);

        sprintf_P(log, PSTR("%s%s using port %u"), "TELNT: connecting to ", host,Settings.ControllerPort);
        addLog(LOG_LEVEL_DEBUG, log);

        // Use WiFiClient class to create TCP connections
        WiFiClient client;
        if (!client.connect(host, Settings.ControllerPort))
        {
          connectionFailures++;
          strcpy_P(log, PSTR("TELNT: connection failed"));
          addLog(LOG_LEVEL_ERROR, log);
          return false;
        }
        statusLED(true);
        if (connectionFailures)
          connectionFailures--;

        // We now create a URI for the request
        String url = F("");
		
		switch (event->sensorType)
		{
			case SENSOR_TYPE_SINGLE:                      // single value sensor, used for Dallas, BH1750, etc
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[0];
				url += F(" ");
				url += toString(UserVar[event->BaseVarIndex],ExtraTaskSettings.TaskDeviceValueDecimals[0]);
				url += "\n";
				break;
			case SENSOR_TYPE_LONG:							// single LONG value, stored in two floats (rfid tags)
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[0];
				url += F(" ");
				url += (unsigned long)UserVar[event->BaseVarIndex] + ((unsigned long)UserVar[event->BaseVarIndex + 1] << 16);
				url += "\n";
				break;
				case SENSOR_TYPE_TEMP_HUM:                      // temp + hum + hum_stat, used for DHT11
				//Erstes Reading
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[0];
				url += F(" ");
				url += toString(UserVar[event->BaseVarIndex],ExtraTaskSettings.TaskDeviceValueDecimals[0]);
				//Zweites Reading
				url += F(";");
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[1];
				url += F(" ");
				url += toString(UserVar[event->BaseVarIndex + 1],ExtraTaskSettings.TaskDeviceValueDecimals[1]);
				url += "\n";
				break;
			case SENSOR_TYPE_TEMP_BARO:                      // temp + hum + hum_stat + bar + bar_fore, used for BMP085
				//Erstes Reading
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[0];
				url += F(" ");
				url += toString(UserVar[event->BaseVarIndex],ExtraTaskSettings.TaskDeviceValueDecimals[0]);
				//Zweites Reading
				url += F(";");
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[1];
				url += F(" ");
				url += toString(UserVar[event->BaseVarIndex + 1],ExtraTaskSettings.TaskDeviceValueDecimals[1]);
				url += "\n";
				break;
			case SENSOR_TYPE_TEMP_HUM_BARO:                      // temp + hum + hum_stat + bar + bar_fore, used for BME280
				//Erstes Reading
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[0];
				url += F(" ");
				url += toString(UserVar[event->BaseVarIndex],ExtraTaskSettings.TaskDeviceValueDecimals[0]);
				//Zweites Reading
				url += F(";");
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[1];
				url += F(" ");
				url += toString(UserVar[event->BaseVarIndex + 1],ExtraTaskSettings.TaskDeviceValueDecimals[1]);
				//Drittes Reading
				url += F(";");
				url += F("setreading ");
				url += Settings.Name;
				url += F(" ");
				url += ExtraTaskSettings.TaskDeviceValueNames[2];
				url += F(" ");
				url += toString(UserVar[event->BaseVarIndex + 2],ExtraTaskSettings.TaskDeviceValueDecimals[2]);
				url += "\n";
				break;
			case SENSOR_TYPE_SWITCH:
				url += F("set ");
				url += Settings.Name;
				url += F(" ");
				if (UserVar[event->BaseVarIndex] == 0)
				{
					url += "off";
					url += "\n";
				}
				else
				{
					url += "on";
					url += "\n";
				}
				break;
			case SENSOR_TYPE_DIMMER:
				url += F("set ");
				url += Settings.Name;
				url += F(" ");
				if (UserVar[event->BaseVarIndex] == 0)
				{	
					url += "off";
					url += "\n";
				}
				else
				{
					url += F("pct ");
					url += UserVar[event->BaseVarIndex];
					url += "\n";
				}
				break;
		}
			
        strcpy_P(log, PSTR("TELNT: Sending enter"));
        addLog(LOG_LEVEL_ERROR, log);
        client.print(" \n");

        unsigned long timer = millis() + 200;
        while (!client.available() && millis() < timer)
          delay(1);

        timer = millis() + 1000;
        while (client.available() && millis() < timer && !success)
        {
          String line = client.readStringUntil('\n');
          if (line.substring(0, 20) == "Enter your password:")
          {
            success = true;
            strcpy_P(log, PSTR("TELNT: Password request ok"));
            addLog(LOG_LEVEL_ERROR, log);
          }
          delay(1);
        }

        strcpy_P(log, PSTR("TELNT: Sending pw"));
        addLog(LOG_LEVEL_ERROR, log);
        client.println(SecuritySettings.ControllerPassword);
        delay(100);
        while (client.available())
          client.read();

        strcpy_P(log, PSTR("TELNT: Sending cmd"));
        addLog(LOG_LEVEL_ERROR, log);
        client.print(url);
        delay(10);
        while (client.available())
          client.read();

        strcpy_P(log, PSTR("TELNT: closing connection"));
        addLog(LOG_LEVEL_DEBUG, log);

        client.stop();

        break;
      }

  }
  return success;
}

