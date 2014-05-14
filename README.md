hook-library
============

API Hook Library
(C) 2010 - Guilherme Maeda

This is a free library for hooking any exported function from a Windows
executable file.

It uses the JMP replacement method for detouring the function calls, and it
also uses a disassembler (ollyasm) to correctly handle functions in any calling
convention (cdecl, stdcall, fastcall, etc), as long as the entire function code
is at least 5 bytes long.

It was compiled and tested using Pelles C on Windows XP and Windows 7.

Please check the example and source files for instruction on how to use the
library.