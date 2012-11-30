tools/compile $1 $2 $3
tools/readdeps $2 | xargs redo-ifchange
redo-ifchange "$2.c"
if [ -f "$2.h" ]; then
  redo-ifchange "$2.h"
fi
