system = Module("system"
print = system.out.write_line
mime = Module("mime"
decode = Module("decode"
assert = @(x) x || throw Throwable("Assertion failed."
assert_equals = @(actual, expected)
	print(actual
	assert(actual == expected

base64 = @(text) decode(mime.base64_decode, text
assert_equals(base64(""), ""
assert_equals(base64("Zg=="), "f"
assert_equals(base64("Zm8="), "fo"
assert_equals(base64("Zm9v"), "foo"
assert_equals(base64("Zm9vYg=="), "foob"
assert_equals(base64("Zm9vYmE="), "fooba"
assert_equals(base64("Zm9vYmFy"), "foobar"
