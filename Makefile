all: lang/cpp/src
	pip install .
	./ubx/generateCPP.py

test: all
	make -C lang/cpp/ test
	python tests/tests.py
	python tests/test_relposned.py

lang/cpp/src:
	mkdir -p $<

push:
	git push; \
	git subtree push --prefix lang/cpp https://github.com/mayeranalytics/pyUBX-Cpp.git master

.PHONY: test push
