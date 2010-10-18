#!/usr/bin/env lua
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


print("Chumby Data Provider Daemon")
local config = {
  IP      = "192.168.1.102",
  SENSOR  = "a0e9cbec251ee1ef53310ccd64032d6a"
}
print("Using " .. config.IP)

function sleep(n)
  os.execute("sleep " .. tonumber(n))
end

function ticker()
  return coroutine.create (function ()
    while true do
      sleep(1)
      coroutine.yield()
    end
  end
  )
end

function timeactor(tupstream)
  return coroutine.create(function()
    while true do
      coroutine.resume(tupstream)
      print("foo")
      coroutine.yield()
    end
  end
  )
end

function controller(cupstream)
  return coroutine.create(function()
    while true do
      coroutine.resume(cupstream)
      print("bar")
    end
  end
  )
end


local chain = controller(
                timeactor(
                  ticker()
                )
              )

coroutine.resume(chain);