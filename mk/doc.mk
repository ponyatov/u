
.PHONY: doc
doc: $(DOC)
	unison $(APP)

.PHONY: doxy
doxy: .doxygen doc/DoxygenLayout.xml vscode/logo.png
	rm -rf doc/html ; doxygen $< 1>/dev/null
