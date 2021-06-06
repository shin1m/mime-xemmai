$do = @(encode, bytes)
	n = bytes.size(
	i = 0
	target = ""
	encode(
		@(buffer, offset, size)
			size > n && (size = n)
			for j = 0; j < size; j = j + 1
				buffer[offset] = bytes.code_at(i
				:i = i + 1
				offset = offset + 1
			:n = n - size
			size
		@(x) :target = target + x
	target
