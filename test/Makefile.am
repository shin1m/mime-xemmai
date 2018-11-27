TEST_EXTENSIONS = .xm
AM_TESTS_ENVIRONMENT = export XEMMAI_MODULE_PATH=$(top_builddir)/src/.libs:$(XEMMAI_MODULE_PATH);
XM_LOG_COMPILER = $(XEMMAI_BIN_PATH)
AM_XM_LOG_FLAGS = --verbose
scripts = \
	base64_encode.xm \
	base64_decode.xm \
	quoted_printable_encode.xm \
	quoted_printable_decode.xm
EXTRA_DIST = encode.xm decode.xm $(scripts)

TESTS = $(scripts)
