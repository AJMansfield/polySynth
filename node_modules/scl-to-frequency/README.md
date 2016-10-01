# Scala to MIDI Frequencies

This is for [Scala][1] scale files (.scl). Scala is a software program used for 
experimenting with musical tunings. This has nothing to do with the programming
language also called Scala.

This was heavily inspired by the Lua script that eventually became a Renoise
plugin:

<http://forum.renoise.com/index.php/topic/28495-snippet-load-scala-scl-tuning-file>

You point it to an .scl file, and it returns an array of frequencies, where the
index matches the MIDI note (0 -127).

Example:

```javascript
var scl = require('scl-to-frequencies');

scl('/path/to/scl/file');

// Defaults to Middle C at MIDI note 48 and 261.625565300598623 Hz.
scl('/path/to/scl/file', 48, 261.625565300598623);
```

[1]: http://www.huygens-fokker.org/scala/
