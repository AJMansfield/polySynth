

tuning.cpp: makeTuning.js keymap.json $(wildcard tuning/*.scl)
	node makeTuning.js