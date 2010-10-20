#!/usr/bin/env lua -lluarocks.loader
-- This file is part of libflukso.
--
-- (c) Mathias Dalheimer <md@gonium.net>, 2010
--
-- libflukso is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
-- 
-- libflukso is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with libflukso. If not, see <http://www.gnu.org/licenses/>.

require 'posix'
ox=posix
ox.openlog('system')
function log(line)
  --ox.syslog(30, line)
  print(line)
end

log("starting flukso data provider daemon")
local config = {
  IP      = "192.168.1.102",
  SENSOR  = "a0e9cbec251ee1ef53310ccd64032d6a",
  DATADIR = "/Users/md/tmp/flukso",
  BINPATH = "/Users/md/Projects/mysmartgrid/libflukso.git",
  CMD     = "/build/src/flukso-getvalues"
}
log("Using " .. config.IP)

local command = {
  last_reading = config.BINPATH .. config.CMD .. 
              " -l " .. config.IP .. 
              " -s " .. config.SENSOR ..
              " -n " .. config.DATADIR .. "/last_reading" ..
              " -f chumby-current -o file",
  last_minute = config.BINPATH .. config.CMD .. 
              " -l " .. config.IP .. 
              " -s " .. config.SENSOR ..
              " -n " .. config.DATADIR .. "/last_minute" ..
              " -f chumby-lastminute -o file"
}
ox.mkdir(config.DATADIR);

function ticker()
  return coroutine.create (function ()
    while true do
      ox.sleep(1)
      coroutine.yield()
    end
  end
  )
end

function timeactor(tupstream, command, interval)
  return coroutine.create(function()
    local i=interval;
    while true do
      if (i > 0) then
        i = i - 1;
      else
        retval = os.execute(command)
        if not retval==0 then
          log("Error while running " .. command .. 
              " -> return code " .. retval)
        end
        i=interval;
      end
      coroutine.resume(tupstream)
      coroutine.yield()
    end
  end
  )
end

function controller(cupstream)
  return coroutine.create(function()
    while true do
      coroutine.resume(cupstream)
    end
  end
  )
end

local chain = 
controller(
  timeactor(
    timeactor(ticker(), command.last_reading, 2 )
  , command.last_minute, 2)
)

coroutine.resume(chain);
