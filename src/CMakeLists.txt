add_library(mime MODULE base64.cc quoted_printable.cc mime.cc)
target_link_libraries(mime xemmai)
set_property(TARGET mime PROPERTY PREFIX "")
