#!/bin/bash
#
# image page: build an index page for a set of images.
# Creates index.md to refer to *.{jpg,jpeg,png,gif,tif,tiff,pdf}
#
# David Kotz, March 2021

cat > index.md <<EOF
# Images

EOF

# see https://www.gnu.org/software/bash/manual/html_node/The-Shopt-Builtin.html
shopt -s nullglob

for img in *.{jpg,jpeg,png,gif,tif,tiff,pdf}
do
    echo "![]($img)" >> index.md
    echo >> index.md
done

exit 0
