# BASIC for RISC OS

This is a fork of the RT Russell BASIC, to run on RISC OS for the RISC OS 64 project. It is not
the same as the RISC OS Classic BASIC command, but it is intended to work in a very similar
way to that it can be used in place of it.

## Changes for RISC OS

The RISC OS 64 port has changed the BASIC implementation in the following areas since
5202e65:

### RISC OS Runtime

* Added a RISC OS 64 console build of the interpreter, with RISC OS-specific startup,
  memory layout and ARM64 data support.
* Added character and line input and output through the RISC OS environment so that the
  immediate mode prompt and program output can run on RISC OS.
* Added RISC OS implementations of file, OSCLI, keyboard, timing and support routines
  needed by the console interpreter.
* Changed memory allocation to reduce the requested BASIC workspace until an allocation
  succeeds.
* Updated error handling and C library integration so that BASIC programs can run with
  the RISC OS 64 C library.
* Added cache synchronisation support for generated code areas.
* Fixed the RISC OS text cursor query path so that reading the cursor position no longer
  crashes.
* Fixed `-quit` so that normal program termination returns a zero process exit status.

### SWI And OS Access

* Added RISC OS `SYS` support, calling real SWIs and returning register results to BASIC.
* Added support for integer, floating point and string parameters in RISC OS `SYS` calls.
* Fixed the sense of the `_kernel_oscli` result handling used by command execution.
* Fixed `OS_BPut` file output so that BASIC file writes are passed to RISC OS correctly.

### Program Loading

* Added loading of BBC BASIC tokenised files, allowing Acorn-format BASIC programs to be
  loaded directly.
* Added detection of RISC OS filetypes when loading programs: BBC BASIC tokenised
  (`&FFB`), text (`&FD1`) and RTR BASIC (`&1C7`).
* Added fallback loading by filename suffix on RISC OS, trying `,ffb`, `,fd1`, `,1c7`
  and `.bbc` forms where appropriate.
* Added conversion from BBC BASIC tokenised files into the internal RTR BASIC format.
* Added command-line loading of text-format BASIC programs.
* Added auto-numbering for unnumbered text files loaded from the command line.

### Program Saving

* Changed `SAVE "file"` to save Acorn/BBC BASIC tokenised files by default.
* Added `SAVE "file","Acorn"` for explicit Acorn/BBC BASIC tokenised output.
* Added `SAVE "file","RTR"` for RTR BASIC internal-format output.
* Added conversion from RTR BASIC internal format back to BBC BASIC tokenised format.
* Set the RISC OS filetype on saved BASIC files to match the selected output format.
* Added bare `SAVE`, inferring the destination filename from an initial `REM > filename`
  line.

### Text Format Support

* Added `TEXTLOAD "file"` to load textual BASIC source files.
* Added `TEXTSAVE "file"` to save the current program as textual BASIC source.
* Added text listing through the file output path so that saved text uses the same
  formatting as `LIST`.
* Added line-number parsing which works without relying on library `sscanf` behaviour.

### Command Line Behaviour

* Added BBC BASIC-style invocation modes: `bbcbasic file`, `bbcbasic -chain file`,
  `bbcbasic -load file` and `bbcbasic -quit file`.
* Made `file` and `-chain file` load and run the program, then return to immediate mode.
* Made `-load file` load the program and enter immediate mode without running it.
* Made `-quit file` run the program and exit when execution completes.
* Fixed command-line option parsing so that only a leading option is treated as an
  interpreter option, matching classic BASIC behaviour.
* Fixed auto-run selection on RISC OS so that command-line `-load` and `-chain` use the
  named BASIC program rather than the interpreter binary name.

### Language And Graphics Behaviour

* Fixed excess blank lines from the immediate-mode REPL on RISC OS.
* Fixed `ELLIPSE` drawing so that ellipses are rendered with the correct shape.
* Fixed a multiply overflow test in expression evaluation.
* Added inline arithmetic operation updates from the upstream interpreter.
* Pulled in upstream Console Mode updates through v0.50 and BBCSDL updates through v1.43b,
  bringing the RISC OS port up to date with the shared interpreter changes.

# Original README
BBC BASIC for SDL 2.0 (BBCSDL) is a cross-platform implementation of the BBC BASIC programming language for
Windows, Linux (x86), MacOS, Raspbian (Raspberry Pi OS), Android, iOS and Emscripten / WebAssembly.
It is highly compatible with BBC BASIC for Windows and has the same language extensions, but uses
SDL 2.0 as an OS abstraction layer to achieve cross-platform compatibility.

The BBC BASIC Console Mode editions (BBCTTY) are lightweight implementations for Windows, Linux (x86),
MacOS and Raspbian (Raspberry Pi OS) which do not support graphics or sound but are otherwise 
compatible with the desktop, mobile and web editions.  They take their input from stdin and
send their output to stdout, so may be used for scripting, CGI and remote terminal applications.

![Architecture](https://www.bbcbasic.co.uk/bbcsdl/arch.png)

The files in green constitute the generic BBC BASIC interpreter which is shared by all the
editions.  The files in the red box are used to build the Console Mode editions.  The files in
the blue box are used to build the SDL 2.0 editions.  The files in brown run in the GUI (main)
thread, all the others run in the interpreter thread.

The files with the 1 and 2 superscripts are CPU-specific and the different variants are listed
beneath (not all exist!).  Note that bbasmb_wasm32.c isn't an assembler, but has been used as a
convenient place to put the function wrappers needed to support SYS in the in-browser edition.

Not indicated in the diagram is that the in-browser edition uses different versions of bbc.h
and bbcsdl.h from the rest.

Note that the name 'BBC BASIC' is used by permission of the British Broadcasting Corporation
and is not transferrable to a derived or forked work.
