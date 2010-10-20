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
  lastvalue = config.BINPATH .. config.CMD .. 
              " -l " .. config.IP .. 
              " -s " .. config.SENSOR ..
              " -n " .. config.DATADIR .. "/current_value.xml" ..
              " -f chumby-current -o file "
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

function timeactor(tupstream, command, filename)
  return coroutine.create(function()
    local i=0;
    while true do
      coroutine.resume(tupstream)
      log("running " .. command)
      i = i + 1;
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

local cmd=command.lastvalue
log("Using command "..cmd);

local chain = controller(
                timeactor(
                    ticker(), 
                  cmd, "narf.dat"
                )
              )

coroutine.resume(chain);
