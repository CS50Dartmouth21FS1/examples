#!/bin/bash
#
# A quick demonstration of command-line arguments in bash.
#

# Note that $# is the number of arguments provided, other than the command,
# and that $0 is the command name itself (as written by the invoking user).
echo "There are $# arguments to $0."

# Individual arguments are available as variables numbered 1, 2, ...
# and arguments beyond $# have value of empty string.
echo "The first  argument is '$1'"
echo "The second argument is '$2'"
echo "The third  argument is '$3'"

# Loop through all the arguments, in four different ways;
# Note carefully the difference between these cases when some of the
# arguments have embedded spaces.

echo
echo 'for arg in $* (likely not what you expect)'
for arg in $*; do echo "$arg"; done

echo
echo 'for arg in "$*" (likely not what you expect)'
for arg in "$*"; do echo "$arg"; done

echo
echo 'for arg in $@ (likely not what you expect)'
for arg in $@; do echo "$arg"; done

echo
echo 'for arg in "$@" (likely best for all common scripts)'
for arg in "$@"; do echo "$arg"; done

exit 0
