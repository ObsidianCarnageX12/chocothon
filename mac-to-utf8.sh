#!/bin/bash

# Takes any number of input files with CR line endings in Macintosh Roman and
# converts them to Unix line endings and UTF-8. Used to convert the original
# Marathon Infinity source files to be compatible with modern editors.

while [ "${1}" != "" ]; do
	echo "Converting ${1}..."
	iconv -f mac -t utf-8 "${1}" | sed 's/\r/\n/g' > ${1}
	shift # move to the next argument
done

