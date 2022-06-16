#!/bin/sh -efu
# Bulk-rename files dropped into the target using a text editor

readonly FILES_OLD="$(mktemp -t rename.old.XXXX)"
readonly FILES_NEW="$(mktemp -t rename.new.XXXX)"
readonly FILES_EXE="$(mktemp -t rename.exe.XXXX.sh)"

renamer_clean() {
	rm "${FILES_OLD}" "${FILES_NEW}" "${FILES_EXE}"
}

trap renamer_clean HUP INT QUIT TERM PWR EXIT

dragdrop | tee "${FILES_OLD}" > "${FILES_NEW}"

command "${EDITOR:-nano}" "${FILES_NEW}"

echo '# The following commands will be executed:' > "${FILES_EXE}"
paste -d '\n' "${FILES_OLD}" "${FILES_NEW}" |
	xargs -d '\n' printf 'mv -- %q %q\n' >> "${FILES_EXE}"

command "${EDITOR:-nano}" "${FILES_EXE}"

. "${FILES_EXE}"
