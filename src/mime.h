#ifndef XEMMAIX__MIME__MIME_H
#define XEMMAIX__MIME__MIME_H

#include <xemmai/convert.h>

namespace xemmaix::mime
{

using namespace xemmai;

struct t_library : xemmai::t_library
{
	using xemmai::t_library::t_library;
	XEMMAI__LIBRARY__MEMBERS
};

XEMMAI__LIBRARY__BASE(t_library, t_global, f_global())

class t_string_source
{
	t_pvalue v_read;
	t_pvalue v_value;
	const wchar_t* v_i = nullptr;
	const wchar_t* v_j = nullptr;

	void f_read();

public:
	t_string_source(const t_pvalue& a_read) : v_read(a_read)
	{
	}
	int f_get()
	{
		if (v_i == v_j) {
			f_read();
			if (v_i == v_j) return -1;
		}
		return *v_i++;
	}
};

class t_string_target
{
	t_pvalue v_write;
	std::vector<wchar_t> v_buffer;

public:
	t_string_target(const t_pvalue& a_write) : v_write(a_write)
	{
	}
	~t_string_target()
	{
		f_flush();
	}
	void f_put(wchar_t a_c)
	{
		v_buffer.push_back(a_c);
	}
	void f_flush();
};

class t_bytes_source
{
	t_pvalue v_read;
	t_object* v_buffer;
	size_t v_n = 0;
	size_t v_i = 0;

	void f_read();

public:
	t_bytes_source(const t_pvalue& a_read) : v_read(a_read), v_buffer(t_bytes::f_instantiate(1024))
	{
	}
	int f_get()
	{
		if (v_i >= v_n) {
			f_read();
			if (v_i >= v_n) return -1;
		}
		return f_as<const t_bytes&>(v_buffer)[v_i++];
	}
};

class t_bytes_target
{
	t_pvalue v_write;
	t_object* v_buffer;
	size_t v_n = 0;

public:
	t_bytes_target(const t_pvalue& a_write) : v_write(a_write), v_buffer(t_bytes::f_instantiate(1024))
	{
	}
	~t_bytes_target()
	{
		f_flush();
	}
	void f_put(unsigned char a_c)
	{
		auto& bytes = f_as<t_bytes&>(v_buffer);
		if (v_n >= bytes.f_size()) f_flush();
		bytes[v_n++] = a_c;
	}
	void f_flush();
};

void f_b_encode(t_bytes_source& a_source, t_string_target& a_target);
void f_base64_encode(t_bytes_source& a_source, t_string_target& a_target, size_t a_n = 72);
void f_base64_decode(t_string_source& a_source, t_bytes_target& a_target);
void f_q_encode(t_bytes_source& a_source, t_string_target& a_target);
void f_quoted_printable_encode(t_bytes_source& a_source, t_string_target& a_target, size_t a_n = 72);
void f_quoted_printable_decode(t_string_source& a_source, t_bytes_target& a_target);

}

#endif
