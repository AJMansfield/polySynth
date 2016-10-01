#!/usr/bin/node

var scl = require('scl-to-frequency')

var freq = scl('ptolmy.scl')

for (f of freq) {
	console.log( 1e6 / f)
}
