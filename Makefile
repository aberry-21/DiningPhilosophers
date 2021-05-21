.PHONY:		all re clean fclean
all:
	@mkdir -p build && cd build && cmake .. && make && mv dining_philosophers ..
clean:
	@find . -name *.o -delete
fclean:
	@rm -rf build && rm -rf dining_philosophers && rm -rf dining_philosophers.dSYM
re:			fclean all