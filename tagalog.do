export LDFLAGS="$(pkg-config --libs yajl)"
redo-ifchange tagalog.o
tools/link tagalog tagalog "$3"
