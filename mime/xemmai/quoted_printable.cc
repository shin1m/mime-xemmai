#include "mime.h"

#include <cctype>
#include <cwctype>

namespace mime
{

namespace xemmai
{

namespace
{

inline wchar_t f_c2h(unsigned char a_c)
{
	return a_c < 10 ? a_c + L'0' : a_c - 10 + L'A';
}

inline bool f_is_qspecial(int c)
{
	switch (c) {
	case '(': case ')': case '<': case '>':	case '@':
	case ',': case ';': case ':': case '\\': case '"':
	case '/': case '[': case ']': case '?': case '=':
		return true;
	default:
		return !std::isprint(c);
	}
}

void f_q_encode(t_bytes_source& a_source, t_string_target& a_target)
{
	int c = a_source.f_get();
	while (c != -1) {
		if (f_is_qspecial(c)) {
			a_target.f_put(L'=');
			a_target.f_put(f_c2h(c >> 4));
			a_target.f_put(f_c2h(c & 0x0f));
		} else {
			a_target.f_put(c);
		}
		c = a_source.f_get();
	}
}

inline bool f_is_qpspecial(int c)
{
	switch (c) {
	case '(': case ')': case '<': case '>':	case '@':
	case ',': case ';': case ':': case '\\': case '"':
	case '/': case '[': case ']': case '?': case '=':
		return true;
	default:
		return !std::isprint(c);
	}
}

void f_quoted_printable_encode(t_bytes_source& a_source, t_string_target& a_target, size_t a_n = 72)
{
	size_t i = 0;
	int c = a_source.f_get();
	while (c != -1) {
		if (f_is_qpspecial(c)) {
			if (i + 2 >= a_n) {
				a_target.f_put(L'=');
				a_target.f_put(L'\r');
				a_target.f_put(L'\n');
				i = 0;
			}
			a_target.f_put(L'=');
			a_target.f_put(f_c2h(c >> 4));
			a_target.f_put(f_c2h(c & 0x0f));
			i += 3;
		} else {
			if (i >= a_n) {
				a_target.f_put(L'=');
				a_target.f_put(L'\r');
				a_target.f_put(L'\n');
				i = 0;
			}
			a_target.f_put(c);
			++i;
		}
		c = a_source.f_get();
	}
}

inline unsigned char f_h2c(int c)
{
	return std::iswdigit(c) ? c - L'0' : c - (std::iswupper(c) ? L'A' : L'a') + 10;
}

void f_quoted_printable_decode(t_string_source& a_source, t_bytes_target& a_target)
{
	int c = a_source.f_get();
	while (c != -1) {
		if (c == L'=') {
			c = a_source.f_get();
			if (c == L'\r') {
				c = a_source.f_get();
				if (c == L'\n') {
					c = a_source.f_get();
				} else {
					a_target.f_put('=');
					a_target.f_put('\r');
				}
			} else if (std::iswxdigit(c)) {
				int d = c;
				c = a_source.f_get();
				if (std::iswxdigit(c)) {
					a_target.f_put(f_h2c(d) << 4 | f_h2c(c));
					c = a_source.f_get();
				} else {
					a_target.f_put(d);
				}
			} else {
				a_target.f_put('=');
			}
		} else {
			a_target.f_put(c);
			c = a_source.f_get();
		}
	}
}

}

void f_q_encode(const t_value& a_source, const t_value& a_target)
{
	t_bytes_source source(a_source);
	t_string_target target(a_target);
	f_q_encode(source, target);
}

void f_quoted_printable_encode(const t_value& a_source, const t_value& a_target)
{
	t_bytes_source source(a_source);
	t_string_target target(a_target);
	f_quoted_printable_encode(source, target);
}

void f_quoted_printable_encode(const t_value& a_source, const t_value& a_target, size_t a_n)
{
	t_bytes_source source(a_source);
	t_string_target target(a_target);
	f_quoted_printable_encode(source, target, a_n);
}

void f_quoted_printable_decode(const t_value& a_source, const t_value& a_target)
{
	t_string_source source(a_source);
	t_bytes_target target(a_target);
	f_quoted_printable_decode(source, target);
}

}

}
