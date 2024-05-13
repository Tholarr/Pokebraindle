##
## PERSONAL PROJECT, 2024
## Pokebraindle
## File description:
## Makefile
##
NAME = pokebraindle

SRC = 	src/Main.cpp

OBJ = $(SRC:.cpp=.o)

all: Ct.hpp $(NAME)

$(NAME): $(OBJ)
	mv -f Ct.hpp src/include/
	g++ -o $@ $^ -lX11
	rm -f $(OBJ)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.'
	@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

clean:
	rm -f $(OBJ)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.'

fclean: clean
	rm -f $(NAME)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'
	rm -f Ct.hpp
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" Ct.hpp | tr ' ' '.'

re: fclean all

Ct.hpp: db/ct.csv
	@echo "Generating $@ from [$^]"
	@touch $@
	@chmod +w $@
	@echo -e "/*\n** PERSONNAL PROJECT, 2024\n** Pokebraindle\n** File" \
	"description:\n** Auto-generated file that lists all available" \
	"assets\n** Do not modify by hand.\n*/" > $@
	@echo >> $@
	@echo '#include <array>' >> $@
	@echo '#include <string>' >> $@
	@echo '#include <limits>' >> $@
	@echo '#include <cstdint>' >> $@
	@echo >> $@
	@echo "#ifndef CT_HPP_" >> $@
	@echo "#define CT_HPP_" >> $@
	@echo >> $@
	@echo '    enum CtId {' >> $@
	@awk -F ',' '{print "        " $$1 " = " NR-1 ","}' $^ >> $@
	@echo >> $@
	@echo '        CT_COUNT,' >> $@
	@echo '    };' >> $@
	@echo >> $@
	@echo '    const std::array<std::string, CT_COUNT> CtNames = {' >> $@
	@awk -F ',' '{print "        " $$2 ","}' $^ >> $@
	@echo '    };' >> $@
	@echo >> $@
	@echo '    const std::array<std::string, CT_COUNT> CtTypes = {' >> $@
	@awk -F ',' '{print "        " $$3 ","}' $^ >> $@
	@echo '    };' >> $@
	@echo >> $@
	@echo '    const std::array<std::int32_t, CT_COUNT> CtPower = {' >> $@
	@awk -F ',' '{print "        " $$4 ","}' $^ >> $@
	@echo '    };' >> $@
	@echo >> $@
	@echo '    const std::array<std::int32_t, CT_COUNT> CtAccuracy = {' >> $@
	@awk -F ',' '{print "        " $$5 ","}' $^ >> $@
	@echo '    };' >> $@
	@echo >> $@

	@echo "#endif /* !CT_HPP_ */" >> $@
	@chmod -w $@
