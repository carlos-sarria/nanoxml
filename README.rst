=============
Nano XML
=============

A simple and efficient XML parser written in pure C, with support for HTML-like constructs. It operates directly on the XML buffer without allocating additional memory, aside from pointers to relevant elements within the buffer. The parser processes the entire buffer by pushing and popping tag pointers onto a stack. This stack maintains a hierarchical list of all active tags at any given moment, which accompanies each text element as it is stored sequentially.

To use the resulting structure, simply read the elements in order and apply the associated tags to produce the final output.
This parser is designed to be part of a graphical window system that uses HTML-style formatting for text.

An example is included that reads an HTML file and outputs the complete list of tags and text content.


Building
--------
The CMake file is supplied. Tested with QT Creator. Just build it straight from the CMake file using MinGW 64-bit compiler.

