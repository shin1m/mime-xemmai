$do = @(decode, text)
	source = [text]
	target = ""
	decode(
		@ source.size() > 0 ? source.shift() : null
		@(buffer, offset, size)
			while size > 0
				:target = target + String.from_code(buffer[offset])
				offset = offset + 1
				size = size - 1
	target
