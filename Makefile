doc: prime-handler.hh
	@echo '/** \mainpage' > mainpage.dox
	@cat README.md >> mainpage.dox
	@echo '*/' >> mainpage.dox
	@sed 's/```C++/@code/g' mainpage.dox > tmp.dox
	@sed 's/```/@endcode/g' tmp.dox > mainpage.dox
	@$(RM) tmp.dox
	doxygen >/dev/null 2>/dev/null

clean:
	$(RM) -r doc/ mainpage.dox
