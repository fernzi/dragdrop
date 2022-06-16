#!/bin/sh -efu
# Download each URL dropped into the target with CURL.

dragdrop -u | while read url; do
	printf 'Downloading URL `%s`...' "${url}"
	curl -JLO# "${url}"
end
