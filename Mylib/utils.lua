local function register(...)
    local args = {...}
    for i = 1, select('#', ...) do
        debug.setmetatable(args[i], {
            __call = function(condition, valueOnTrue, valueOnFalse)
                if condition then
                    return valueOnTrue
                else
                    return valueOnFalse
                end
            end
        })
    end
end

local function deregister(...)
    local args = {...}
    for i = 1, select('#', ...) do
        debug.setmetatable(args[i], nil)
    end
end

-- Register the required types (nil, boolean, number, string)
-- WARNING: Do not let this stay in the global scope
-- it can mess up the behaviour of the types and libraries
register(nil, true, 0, '')

print((true)  (false, true)) -- Prints 'false'
print((false) (false, true)) -- Prints 'true'
print((nil)   (true, false)) -- Prints 'false'
print((0)     (true, false)) -- Prints 'true'
print(('')    (true, false)) -- Prints 'true'

-- WARNING: Always deregister the types after using them
deregister(nil, true, 0, '')

-- print((true)  (false, true)) -- Error

-- Deferred execution
local Stream = {}

-- The low level stream constructor receives a generator function
-- similar to the one coroutine.wrap would return. You could change the API
-- to something returning multiple values, like ipairs does. 
function Stream:new(gen)
  local stream = { _next = gen}
  setmetatable(stream, self)
  self.__index = self
  return stream
end

-- Receives a predicate and returns a filtered Stream
function Stream:Where(pred)
  return Stream:new(coroutine.wrap(function()
    for x in self._next do
      if pred(x) then
        coroutine.yield(x)
      end
    end
  end))
end


function Stream:Length()
  local n = 0
  for _ in self._next do
     n = n + 1
  end
  return n
end

function Each(list)
  return Stream:new(coroutine.wrap(function()
    for _, x in ipairs(list) do
      coroutine.yield(x)
    end
  end))
end

local ys = {10, 20, 30, 40}
print( Each(ys):Where(function(x) return x <= 20 end):Length() )
