#include "mime.h"

namespace xemmaix::mime
{

t_extension::t_extension(t_object* a_module) : xemmai::t_extension(a_module)
{
	f_define<void(*)(const t_pvalue&, const t_pvalue&), f_b_encode>(this, L"b_encode"sv);
	f_define<void(*)(const t_pvalue&, const t_pvalue&, size_t), f_base64_encode>(this, L"base64_encode"sv);
	f_define<void(*)(const t_pvalue&, const t_pvalue&), f_base64_decode>(this, L"base64_decode"sv);
	f_define<void(*)(const t_pvalue&, const t_pvalue&), f_q_encode>(this, L"q_encode"sv);
	f_define<void(*)(const t_pvalue&, const t_pvalue&, size_t), f_quoted_printable_encode>(this, L"quoted_printable_encode"sv);
	f_define<void(*)(const t_pvalue&, const t_pvalue&), f_quoted_printable_decode>(this, L"quoted_printable_decode"sv);
}

void t_extension::f_scan(t_scan a_scan)
{
}

void t_string_source::f_read()
{
	v_value = v_read();
	if (v_value) {
		f_check<t_string>(v_value, L"result of read.");
		auto& p = f_as<const t_string&>(v_value);
		v_i = p;
		v_j = v_i + p.f_size();
	} else {
		v_i = v_j = nullptr;
	}
}

void t_string_target::f_flush()
{
	if (v_buffer.empty()) return;
	v_write(t_string::f_instantiate(v_buffer.data(), v_buffer.size()));
	v_buffer.clear();
}

void t_bytes_source::f_read()
{
	auto& bytes = f_as<t_bytes&>(v_buffer);
	auto n = v_read(v_buffer, f_global()->f_as(0), f_global()->f_as(bytes.f_size()));
	f_check<size_t>(n, L"result of read.");
	v_n = f_as<size_t>(n);
	v_i = 0;
}

void t_bytes_target::f_flush()
{
	if (v_n <= 0) return;
	v_write(v_buffer, f_global()->f_as(0), f_global()->f_as(v_n));
	v_n = 0;
}

}

XEMMAI__MODULE__FACTORY(xemmai::t_object* a_module)
{
	return new xemmaix::mime::t_extension(a_module);
}
