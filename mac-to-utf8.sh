#!/bin/bash

# Takes any number of input files with CR line endings in Macintosh Roman and
# converts them to Unix line endings and UTF-8. Used to convert the original
# Marathon Infinity source files to be compatible with modern editors.

while [ "${1}" != "" ]; do
	# convert CR to LF
	mac2unix "${1}"
	# convert Mac OS Roman to UTF-8
	iconv -f mac -t utf-8 < "${1}" > "${1}.bak"
	sed -i 's#[[:space:]]*$##' "${1}.bak"
	sed -i '$a\' "${1}.bak"
	mv "${1}.bak" "${1}"
	shift # move to the next argument
done

