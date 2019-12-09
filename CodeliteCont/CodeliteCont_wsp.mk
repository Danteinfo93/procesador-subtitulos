.PHONY: clean All

All:
	@echo ----------Building project:[ TpFinal - Debug ]----------
	@cd "TpFinal" && "$(MAKE)" -f "TpFinal.mk"
clean:
	@echo ----------Cleaning project:[ TpFinal - Debug ]----------
	@cd "TpFinal" && "$(MAKE)" -f "TpFinal.mk" clean
