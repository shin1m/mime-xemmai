#include "mime.h"

namespace mime
{

namespace xemmai
{

using ::xemmai::f_define;

t_extension::t_extension(t_object* a_module) : ::xemmai::t_extension(a_module)
{
	f_define<void (*)(const t_value&, const t_value&), f_b_encode>(this, L"b_encode");
	f_define<void (*)(const t_value&, const t_value&, size_t), f_base64_encode>(this, L"base64_encode");
	f_define<void (*)(const t_value&, const t_value&), f_base64_decode>(this, L"base64_decode");
	f_define<void (*)(const t_value&, const t_value&), f_q_encode>(this, L"q_encode");
	f_define<void (*)(const t_value&, const t_value&, size_t), f_quoted_printable_encode>(this, L"quoted_printable_encode");
	f_define<void (*)(const t_value&, const t_value&), f_quoted_printable_decode>(this, L"quoted_printable_decode");
}

void t_extension::f_scan(t_scan a_scan)
{
}

void t_string_source::f_read()
{
	t_transfer p = v_read->f_call();
	if (p) {
		f_check<const std::wstring*>(p, L"result of read.");
		v_value = f_as<const std::wstring&>(p);
	} else {
		v_value = std::wstring();
	}
	v_i = v_value.begin();
}

void t_string_target::f_flush()
{
	if (v_buffer.empty()) return;
	v_write->f_call(f_global()->f_as(std::wstring(v_buffer.begin(), v_buffer.end())));
	v_buffer.clear();
}

void t_bytes_source::f_read()
{
	t_bytes& bytes = f_as<t_bytes&>(v_buffer);
	t_transfer n = v_read->f_call(v_buffer, f_global()->f_as(0), f_global()->f_as(bytes.f_size()));
	f_check<size_t>(n, L"result of read.");
	v_n = f_as<size_t>(n);
	v_i = 0;
}

void t_bytes_target::f_flush()
{
	if (v_n <= 0) return;
	v_write->f_call(v_buffer, f_global()->f_as(0), f_global()->f_as(v_n));
	v_n = 0;
}

}

}

XEMMAI__MODULE__FACTORY(xemmai::t_object* a_module)
{
	return new mime::xemmai::t_extension(a_module);
}
