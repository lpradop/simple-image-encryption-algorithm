function chaos(n)
	if n == 0
		return 0.5
	else
		return 3.9 * chaos(n - 1) * (1 - chaos(n - 1))
	end
end

for i in 0:10
	println(chaos(i))
end