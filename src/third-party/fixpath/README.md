# fixpath
See [https://github.com/xaljox/fixpath](https://github.com/xaljox/fixpath)

Fixpath processes the output of a make process. When nested projects are used
the resolving of the file names in some IDE's fails. The reported error/warning
location is relative to the build directory which varies. This is resolved by
processing the Entering and Leaving directory statements (use make -w). With
this information the paths are made absolute. Normally fixpath is used in the
following manner: `make -j4 -w 2>&1 | fixpath` It processes the stdin and puts
the altered output to stdout. There are options to perform some filtering at the
same time, these options are described below. Lines starting with: 'clang',
'gcc', 'clang++', 'g++', 'c++', 'CC' and 'GCC' are classified as compiler lines.

### Usage: 
fixpath --longoptions -hvxocdamr
```
    long option          arg           Description
  --help            (-h)               Print this help.
  --version         (-v)               Shows the current version of fixpath.
  --remove_options  (-x)               Removes the options from recognized
                                       compiler lines.
  --remove_same_opt (-s)               Removes the options from recognized
                                       compiler line if they are the same as on
                                       the previous compiler line.
  --skip_other      (-o)               Skip lines that are not recognized as
                                       compiler or Entering/Leaving directory
                                       lines.
  --skip_compiler   (-c)               Skip lines that are recognized as
                                       compiler lines.
  --skip_directory  (-d)               Skip lines that are recognized as
                                       Entering/Leaving directory lines.
  --skip_all        (-a)               Skip all lines from output.
  --skip_most       (-m)               Skip all lines from output except those
                                       recognized as compiler lines.
  --append_ready    (-r)               Append a line at end, so its clear we are
                                       ready.
```

