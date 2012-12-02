exec >&2
if ! pkg-config --atleast-version=2.0.0 yajl; then
  echo "tagalog tool depends on libyajl (>=2.0.0)"
  exit 1
fi
export CFLAGS="$(pkg-config --cflags yajl)"
tools/compile tagalog.o tagalog "$3"
tools/readdeps tagalog | xargs redo-ifchange
redo-ifchange tagalog.c
