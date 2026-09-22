project('notes', 'c', default_options: ['c_std=c11', 'warning_level=2'])

notes_executable = executable(
  'notes',
  'main.c',
  'notes.c',
  'utils.c',
  'dirutils.c',
)

test(
  'cli behavior',
  find_program('sh'),
  args: [files('tests/test_cli.sh'), notes_executable],
)
