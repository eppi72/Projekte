-- ***************************************************************************
-- BH1750 Example Program for ESP8266 with nodeMCU
-- BH1750 compatible tested 2015-1-30
--
-- Written by xiaohu
--
-- MIT license, http://opensource.org/licenses/MIT
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
-- ***************************************************************************
tmr.alarm(0, 120000, 1, function()

    SDA_PIN = 3 -- sda pin, GPIO-0
    SCL_PIN = 4 -- scl pin, GPIO-2

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
 conn:connect(7072,"192.168.125.5")
 conn:send("setreading Sensor_Licht lux " ..luxi.. "\nexit\n")
end)
