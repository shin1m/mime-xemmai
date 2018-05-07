#ifndef XEMMAIX__MIME__MIME_H
#define XEMMAIX__MIME__MIME_H

#include <xemmai/convert.h>
#include <xemmai/bytes.h>

namespace xemmaix::mime
{

using namespace xemmai;

class t_extension : public xemmai::t_extension
{
public:
	t_extension(t_object* a_module);
	virtual void f_scan(t_scan a_scan);
	template<typename T>
	t_object* f_type() const
	{
		return f_global()->f_type<T>();
	}
	template<typename T>
	t_scoped f_as(T&& a_value) const
	{
		return f_global()->f_as(std::forward<T>(a_value));
	}
};

class t_string_source
{
	const t_value& v_read;
	std::wstring v_value;
	std::wstring::const_iterator v_i;

	void f_read();

public:
	t_string_source(const t_value& a_read) : v_read(a_read), v_i(v_value.begin())
	{
	}
	int f_get()
	{
		if (v_i == v_value.end()) {
			f_read();
			if (v_i == v_value.end()) return -1;
		}
		return *v_i++;
	}
};

class t_string_target
{
	const t_value& v_write;
	std::vector<wchar_t> v_buffer;

public:
	t_string_target(const t_value& a_write) : v_write(a_write)
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
	const t_value& v_read;
	t_scoped v_buffer;
	size_t v_n = 0;
	size_t v_i = 0;

	void f_read();

public:
	t_bytes_source(const t_value& a_read) : v_read(a_read), v_buffer(t_bytes::f_instantiate(1024))
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
	const t_value& v_write;
	t_scoped v_buffer;
	size_t v_n = 0;

public:
	t_bytes_target(const t_value& a_write) : v_write(a_write), v_buffer(t_bytes::f_instantiate(1024))
	{
	}
	~t_bytes_target()
	{
		f_flush();
	}
	void f_put(unsigned char a_c)
	{
		t_bytes& bytes = f_as<t_bytes&>(v_buffer);
		if (v_n >= bytes.f_size()) f_flush();
		bytes[v_n++] = a_c;
	}
	void f_flush();
};

void f_b_encode(const t_value& a_source, const t_value& a_target);
void f_base64_encode(const t_value& a_source, const t_value& a_target);
void f_base64_encode(const t_value& a_source, const t_value& a_target, size_t a_n);
void f_base64_decode(const t_value& a_source, const t_value& a_target);
void f_q_encode(const t_value& a_source, const t_value& a_target);
void f_quoted_printable_encode(const t_value& a_source, const t_value& a_target);
void f_quoted_printable_encode(const t_value& a_source, const t_value& a_target, size_t a_n);
void f_quoted_printable_decode(const t_value& a_source, const t_value& a_target);

}

#endif
