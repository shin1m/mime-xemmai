system = Module("system"
print = system.out.write_line
mime = Module("mime"
encode = Module("encode"
assert = @(x) x || throw Throwable("Assertion failed."
assert_equals = @(actual, expected)
	print(actual
	assert(actual == expected

base64 = @(bytes) encode(
	@(source, target) mime.base64_encode(source, target, 72
	bytes
assert_equals(base64(""), "\r\n"
assert_equals(base64("f"), "Zg==\r\n"
assert_equals(base64("fo"), "Zm8=\r\n"
assert_equals(base64("foo"), "Zm9v\r\n"
assert_equals(base64("foob"), "Zm9vYg==\r\n"
assert_equals(base64("fooba"), "Zm9vYmE=\r\n"
assert_equals(base64("foobar"), "Zm9vYmFy\r\n"

b = @(bytes) encode(mime.b_encode, bytes
assert_equals(b(""), ""
assert_equals(b("f"), "Zg=="
assert_equals(b("fo"), "Zm8="
assert_equals(b("foo"), "Zm9v"
assert_equals(b("foob"), "Zm9vYg=="
assert_equals(b("fooba"), "Zm9vYmE="
assert_equals(b("foobar"), "Zm9vYmFy"
