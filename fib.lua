local fib_mt = {
	__index = function(self, key)
		if key == 0 or key == 1 then
			self[key] = 1
			return 1
		else
			self[key] = self[key - 1] + self[key - 2]
			return self[key]
		end
	end
}

local fib = setmetatable({}, fib_mt)
print(fib[10])
for k, v in pairs(fib) do
	print(k, v)
end
