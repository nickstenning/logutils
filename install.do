exec >&2

if [ -z "$PREFIX" ]; then
  echo 'Please set $PREFIX before running `redo install`'
  exit 1
fi

<BINS while read bin; do
  redo-ifchange "$bin"
  install -m 755 "$bin" "${PREFIX}/bin"
done
