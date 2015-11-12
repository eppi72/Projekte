-- ***************************************************************************
-- *****MY GPIO-TABLE******
-- ***************************************************************************
-- GPIO-0 = IO 3
-- GPIO-1 = IO 10
-- GPIO-2 = IO 4
-- GPIO-3 = IO 9
-- GPIO-4 = IO 2
-- GPIO-5 = IO 1
-- GPIO-9 = IO 11
-- GPIO-10 = IO 12
-- GPIO-12 = IO 6
-- GPIO-13 = IO 7
-- GPIO-14 = IO 5
-- GPIO-15 = IO 8
-- GPIO-16 = IO 0
-- ***************************************************************************
sensorType="dht22" -- set sensor type dht11 or dht22
	humi="XX"
	temp="XX"
	count=1
	DHT_PIN = 0 -- data pin, GPIO16
-- load DHT module and read sensor
function ReadDHT()
	dht=require("dht")
	dht.read(DHT_PIN)
	if sensorType=="dht11"then
	humi=dht.getHumidity()/256
	temp=dht.getTemperature()/256
	else
	humi=dht.getHumidity()/10
	temp=dht.getTemperature()/10
	end
	print("Humidity:    "..humi.." %")
	print("Temperature: "..temp.." deg C")
	-- release module
	dht=nil
	package.loaded["dht"]=nil
end

ReadDHT()
tmr.alarm(1,10000,1,function()ReadDHT()count=count+1 if count==5 then count=0 wifi.sta.connect()print("Reconnect")end

    SDA_PIN = 2 -- sda pin, GPIO-4
    SCL_PIN = 1 -- scl pin, GPIO-10

    bh1750 = require("bh1750")
    bh1750.init(SDA_PIN, SCL_PIN)
    bh1750.read(OSS)
    l = bh1750.getlux()
    print("lux: "..(l / 100).."."..(l % 100).." lx")
	luxi = l / 100
	if(l==nil) then
	l=0
	end
 conn=net.createConnection(net.TCP, 0)
 conn:on("receive", function(conn, payload) print(payload) end )
 -- nachfolgende Zeile die IP und den Port von FHEM eingeben
 conn:connect(7072,"192.168.2.160")
 -- die nachfolgende Zeile ist nur notwendig wenn FHEM Telnet durch ein Passwort geschuetzt ist
 conn:send("password\n")
 conn:send("setreading esp8266temp lux " ..luxi.. "\nexit\n")
 conn:send("setreading esp8266temp temperature " ..temp.. "\nexit\n")
 conn:send("setreading esp8266temp humidity " ..humi.. "\nexit\n")

end)