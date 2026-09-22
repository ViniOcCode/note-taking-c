#!/bin/sh
set -eu

notes_binary="$1"
test_home="$(mktemp -d)"
trap 'rm -rf "$test_home"' EXIT

export HOME="$test_home"
export EDITOR=true

"$notes_binary" --help | grep -q "Usage: Notes"

if "$notes_binary" new >"$test_home/missing-args.txt" 2>&1; then
  echo "new without a category should fail"
  exit 1
fi
grep -q "notes new <category>" "$test_home/missing-args.txt"

"$notes_binary" new work first
test -f "$test_home/notes/work/first.md"

"$notes_binary" new work
test -f "$test_home/notes/work/new_note.md"

"$notes_binary" ls --oneline | grep -q "first.md"

if "$notes_binary" unknown >"$test_home/unknown-command.txt" 2>&1; then
  echo "an unknown command should fail"
  exit 1
fi
grep -q "Unknown command" "$test_home/unknown-command.txt"
