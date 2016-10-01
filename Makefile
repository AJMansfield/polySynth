

tuning.cpp: makeTuning.js keymap.json $(wildcard scl/*.scl)
	node makeTuning.js