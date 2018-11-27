system = Module("system"
print = system.out.write_line
mime = Module("mime"
encode = Module("encode"
assert = @(x) x || throw Throwable("Assertion failed."
assert_equals = @(actual, expected)
	print(actual
	assert(actual == expected

quoted_printable = @(bytes) encode(
	@(source, target) mime.quoted_printable_encode(source, target, 5
	bytes
assert_equals(quoted_printable(""), ""
assert_equals(quoted_printable("f=o"), "f=3Do"
assert_equals(quoted_printable("f=oo"), "f=3Do=\r\no"
assert_equals(quoted_printable("fo=o"), "fo=3D=\r\no"
assert_equals(quoted_printable("foo="), "foo=\r\n=3D"

q = @(bytes) encode(mime.q_encode, bytes
assert_equals(q(""), ""
assert_equals(q("f=o"), "f=3Do"
