system = Module("system"
print = system.out.write_line
mime = Module("mime"
decode = Module("decode"
assert = @(x) x || throw Throwable("Assertion failed."
assert_equals = @(actual, expected)
	print(actual
	assert(actual == expected

quoted_printable = @(text) decode(mime.quoted_printable_decode, text
assert_equals(quoted_printable(""), ""
assert_equals(quoted_printable("f=3Do"), "f=o"
assert_equals(quoted_printable("f=3Do=\r\no"), "f=oo"
assert_equals(quoted_printable("fo=3D=\r\no"), "fo=o"
assert_equals(quoted_printable("foo=\r\n=3D"), "foo="
