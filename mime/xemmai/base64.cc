#include "mime.h"

namespace mime
{

namespace xemmai
{

namespace
{

const wchar_t v_encoding_b2a[64] = {
	L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H',
	L'I', L'J', L'K', L'L', L'M', L'N', L'O', L'P',
	L'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X',
	L'Y', L'Z', L'a', L'b', L'c', L'd', L'e', L'f',
	L'g', L'h', L'i', L'j', L'k', L'l', L'm', L'n',
	L'o', L'p', L'q', L'r', L's', L't', L'u', L'v',
	L'w', L'x', L'y', L'z', L'0', L'1', L'2', L'3',
	L'4', L'5', L'6', L'7', L'8', L'9', L'+', L'/'
};

void f_b_encode(t_bytes_source& a_source, t_string_target& a_target)
{
	while (true) {
		int c = a_source.f_get();
		if (c == -1) break;
		a_target.f_put(v_encoding_b2a[(c >> 2) & 0x3f]);
		size_t d = c << 4;
		c = a_source.f_get();
		if (c == -1) {
			a_target.f_put(v_encoding_b2a[d & 0x3f]);
			a_target.f_put(L'=');
			a_target.f_put(L'=');
			break;
		}
		a_target.f_put(v_encoding_b2a[(d | (c >> 4)) & 0x3f]);
		d = c << 2;
		c = a_source.f_get();
		if (c == -1) {
			a_target.f_put(v_encoding_b2a[d & 0x3f]);
			a_target.f_put(L'=');
			break;
		}
		a_target.f_put(v_encoding_b2a[(d | (c >> 6)) & 0x3f]);
		a_target.f_put(v_encoding_b2a[c & 0x3f]);
	}
}

inline void f_put(t_string_target& a_target, size_t a_n, size_t& a_i, wchar_t a_c)
{
	if (a_i >= a_n) {
		a_target.f_put(L'\r');
		a_target.f_put(L'\n');
		a_i = 0;
	}
	a_target.f_put(a_c);
	++a_i;
}

void f_base64_encode(t_bytes_source& a_source, t_string_target& a_target, size_t a_n = 72)
{
	size_t i = 0;
	while (true) {
		int c = a_source.f_get();
		if (c == -1) break;
		f_put(a_target, a_n, i, v_encoding_b2a[(c >> 2) & 0x3f]);
		size_t d = c << 4;
		c = a_source.f_get();
		if (c == -1) {
			f_put(a_target, a_n, i, v_encoding_b2a[d & 0x3f]);
			f_put(a_target, a_n, i, L'=');
			f_put(a_target, a_n, i, L'=');
			break;
		}
		f_put(a_target, a_n, i, v_encoding_b2a[(d | (c >> 4)) & 0x3f]);
		d = c << 2;
		c = a_source.f_get();
		if (c == -1) {
			f_put(a_target, a_n, i, v_encoding_b2a[d & 0x3f]);
			f_put(a_target, a_n, i, L'=');
			break;
		}
		f_put(a_target, a_n, i, v_encoding_b2a[(d | (c >> 6)) & 0x3f]);
		f_put(a_target, a_n, i, v_encoding_b2a[c & 0x3f]);
	}
	a_target.f_put(L'\r');
	a_target.f_put(L'\n');
}

const int v_encoding_a2b[128] = {
	-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,
	-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,
	-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 62, -3, -3, -3, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -3, -3, -3, -2, -3, -3,
	-3, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -3, -3, -3, -3, -3,
	-3, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -3, -3, -3, -3, -3
};

inline int f_a2b(int a_c)
{
	return a_c == -1 ? -1 : a_c > 127 ? -3 : v_encoding_a2b[a_c];
}

void f_base64_decode(t_string_source& a_source, t_bytes_target& a_target)
{
	while (true) {
		int c = f_a2b(a_source.f_get());
		while (c < 0) {
			if (c == -1) return;
			if (c == -2) {
				do c = a_source.f_get(); while (c != -1);
				return;
			}
			c = f_a2b(a_source.f_get());
		}
		unsigned char d = c << 2;
		c = f_a2b(a_source.f_get());
		while (c < 0) {
			if (c == -1) return;
			if (c == -2) {
				do c = a_source.f_get(); while (c != -1);
				return;
			}
			c = f_a2b(a_source.f_get());
		}
		a_target.f_put(d | (c >> 4));
		d = c << 4;
		c = f_a2b(a_source.f_get());
		while (c < 0) {
			if (c == -1) return;
			if (c == -2) {
				do c = a_source.f_get(); while (c != -1);
				return;
			}
			c = f_a2b(a_source.f_get());
		}
		a_target.f_put(d | (c >> 2));
		d = c << 6;
		c = f_a2b(a_source.f_get());
		while (c < 0) {
			if (c == -1) return;
			if (c == -2) {
				do c = a_source.f_get(); while (c != -1);
				return;
			}
			c = f_a2b(a_source.f_get());
		}
		a_target.f_put(d | c);
	}
}

}

void f_b_encode(const t_value& a_source, const t_value& a_target)
{
	t_bytes_source source(a_source);
	t_string_target target(a_target);
	f_b_encode(source, target);
}

void f_base64_encode(const t_value& a_source, const t_value& a_target)
{
	t_bytes_source source(a_source);
	t_string_target target(a_target);
	f_base64_encode(source, target);
}

void f_base64_encode(const t_value& a_source, const t_value& a_target, size_t a_n)
{
	t_bytes_source source(a_source);
	t_string_target target(a_target);
	f_base64_encode(source, target, a_n);
}

void f_base64_decode(const t_value& a_source, const t_value& a_target)
{
	t_string_source source(a_source);
	t_bytes_target target(a_target);
	f_base64_decode(source, target);
}

}

}
