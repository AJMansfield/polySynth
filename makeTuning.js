#!/usr/bin/node

var fs = require('fs')
var scl = require('scl-to-frequency')

var keymap = require('./keymap.json')

var keytab = new Array(128)

for (km of keymap.segments) {
	freq = scl(km.tuning)

	for (i = 0; i < km.length; i++) {
		keytab[km.key + i] = (1e6 / freq[km.tone + i]) & -1
	}
}

var file = fs.createWriteStream('tuning.cpp');
file.on('error', function(err) { /* error handling */ });

file.write('const unsigned int tuning[] = {\n\t')
file.write(keytab.join(',\n\t'))
file.write('};\nconst unsigned int tuning_len = 128;')
file.end();
