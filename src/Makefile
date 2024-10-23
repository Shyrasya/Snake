CC = gcc
GPP = g++
CFLAGS = -Wall -Werror -Wextra -std=c11
CPPFLAGS = -Wall -Werror -Wextra -std=c++17
NCURSES = -lncurses
CLIBRG = cli_brick_games
DESKBRG = desktop_brick_games
TFLAG = -lgtest -coverage -lgtest_main

SNAKE_DIR = brick_game/snake
TETRIS_DIR = brick_game/tetris
SNAKE_OBJS = $(SNAKE_DIR)/snake_controller.o $(SNAKE_DIR)/snake_model.o
TETRIS_OBJS = $(TETRIS_DIR)/tetris_main_cycle.o $(TETRIS_DIR)/tetris_fsm.o $(TETRIS_DIR)/tetris_logic.o 
SNAKE_LIB = libsnake.a
TETRIS_LIB = libtetris.a
CLI_DIR = gui/cli
CLI_OBJ = $(CLI_DIR)/console_view.o
CLI_OBJ_TETR = $(CLI_DIR)/console_view_tetr.o
CLI_MAINOBJ = $(CLI_DIR)/cli_main.o
DESK_DIR = gui/desktop
BUILD = build
BUILD_DESKTOP_DIR = gui/desktop/build
DIST = dist
TEST_DIR = tests
TEST = $(TEST_DIR)/tests.cpp
DOC = documentation
REP = report
SG = -style=Google
CLANG = clang-format
CPPCHECK = cppcheck
DESKTOP_DIR := brick_game/gui/desktop
PROJECT = desktop_brick_games

UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	det_OS = -lm -lrt -lpthread
	for_lcov =
	CPPCHECK_FLAGS = --enable=all --suppress=missingInclude --language=c++ --suppress=unusedStructMember --suppress=unusedFunction
else
	det_OS = -lpthread
	for_lcov = --ignore-errors inconsistent
	CPPCHECK_FLAGS = --suppress=noExplicitConstructor --enable=all --suppress=missingInclude --language=c++ --suppress=unusedStructMember --suppress=unusedFunction
endif

all: clean_all gcov_report dist

# Компиляция C++ файлов для логики змейки
$(SNAKE_DIR)/snake_controller.o: $(SNAKE_DIR)/snake_controller.cpp
	$(GPP) $(GPPFLAGS) -c $^ -o $@ $(det_OS)

$(SNAKE_DIR)/snake_model.o: $(SNAKE_DIR)/snake_model.cpp
	$(GPP) $(GPPFLAGS) -c $^ -o $@ $(det_OS)

# Создание библиотеки для змейки
$(SNAKE_LIB): $(SNAKE_OBJS)
	ar rcs $@ $^

# Компиляция C файлов для мэйн тетриса
$(TETRIS_DIR)/tetris_main_cycle.o: $(TETRIS_DIR)/tetris_main_cycle.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(det_OS)

# Компиляция C файлов для fsm тетриса
$(TETRIS_DIR)/tetris_fsm.o: $(TETRIS_DIR)/tetris_fsm.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(det_OS)

# Компиляция C файлов для логики тетриса
$(TETRIS_DIR)/tetris_logic.o: $(TETRIS_DIR)/tetris_logic.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(det_OS)

# Создание библиотеки для тетриса
$(TETRIS_LIB): $(TETRIS_OBJS)
	ar rcs $@ $^

# Интерфейс змейки
$(CLI_OBJ): $(CLI_DIR)/console_view.c
	$(GPP) $(CPPFLAGS) -c $^ -o $@ $(det_OS)

# Интерфейс тетриса
$(CLI_OBJ_TETR): $(CLI_DIR)/console_view.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(det_OS)

# Главное меню
$(CLI_MAINOBJ): $(CLI_DIR)/cli_main.cpp
	$(GPP) $(CPPFLAGS) -c $^ -o $@ $(det_OS)

# Линковка исполняемого файла
$(CLIBRG): $(CLI_MAINOBJ) $(CLI_OBJ) $(CLI_OBJ_TETR) $(SNAKE_LIB) $(TETRIS_LIB)
	$(GPP) $(CPPFLAGS) $^ $(NCURSES) -o $@

# Создание папки build
$(BUILD):
	@mkdir -p $(BUILD)

# Установка игр
install: install_cli install_desktop clean

# Установка консольной brickgames в папку build
install_cli: $(CLIBRG)
	@make build
	@mv ./$(CLIBRG) $(BUILD)

# Установка десктопной brickgames в папку build
install_desktop:
	@mkdir -p $(BUILD_DESKTOP_DIR)
	@cd $(BUILD_DESKTOP_DIR) && cmake .. && $(MAKE)
	@mkdir -p $(BUILD)
	@mv $(BUILD_DESKTOP_DIR)/$(DESKBRG) $(BUILD)
	@rm -rf $(BUILD_DESKTOP_DIR)
	@chmod 0700 /run/user/1000/

# Запуск консольной brickgames
play_cli:
	./$(BUILD)/$(CLIBRG)

# Запуск десктопной brickgames
play_desktop:
	./$(BUILD)/$(DESKBRG)

uninstall:
	rm -rf ./$(BUILD)

# Компиляция тестов
tests: clean
	$(GPP) $(CPPFLAGS) $(SNAKE_DIR)/snake_model.cpp $(TEST) -o ./$(TEST_DIR)/$@ $(TFLAG) $(det_OS)

# Запуск тестов
start_tests: tests
	./$(TEST_DIR)/tests
	@make clean

# Покрытие тестов
gcov_report: clean tests
	./$(TEST_DIR)/tests
	lcov --no-external -o ./$(TEST_DIR)/res.info $(for_lcov) -c -d . --exclude '*/snake_model.h'
	genhtml -o ./$(TEST_DIR)/$(REP) ./$(TEST_DIR)/res.info
	# open ./$(TEST_DIR)/$(REP)/index.html

# установка Doxygen
install_doxygen:
	sudo apt install graphviz && sudo apt install doxygen

# Генерация документации
dvi:
	doxygen
	# open ./$(DOC)/html/index.html

# Создаем build-архив с играми и документацией
dist: install dvi
	@mkdir -p $(DIST)
	@cp -R ./$(BUILD)/$(CLIBRG) ./$(DIST)/$(CLIBRG)
	@cp -R ./$(BUILD)/$(DESKBRG) ./$(DIST)/$(DESKBRG)
	@cp -R ./$(DOC) ./$(DIST)/$(DOC)
	@cd ./$(DIST) && tar cvzf brick_games.tgz *
	@cd ./$(DIST) && rm -rf $(CLIBRG) $(DESKBRG) $(DOC)
	@make clean

# Утечки
valgrind: clean tests
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -s ./$(TEST_DIR)/tests
	@make clean
	@make clean_tests

# Cтатический анализатор кода
cppcheck:
	find . -type f \( -name "*.h" -o -name "*.c" -o -name "*.cpp" \) | xargs $(CPPCHECK) $(CPPCHECK_FLAGS)

# Проверка на стиль
clang:
	@cp ../materials/linters/.$(CLANG) ./
	find . -name "*.h" -o -name "*.c" -o -name "*.cpp" | xargs $(CLANG) $(SG) -n
	find . -name "*.h" -o -name "*.c" -o -name "*.cpp" | xargs $(CLANG) $(SG) -i
	@rm .$(CLANG)

# Удаляем объектные файлы и библиотеки
clean:
	@find . -type f -name "*.o" -exec rm -f {} +
	@find . -type f -name "*.a" -exec rm -f {} +

# Удаляем информацию по покрытию и компиляционные файлы по тестам
clean_tests:
	@rm -rf ./$(TEST_DIR)/$(TEST_DIR) ./$(TEST_DIR)/*.info ./$(TEST_DIR)/$(REP)
	@find . -type f -name "*.gc*" -exec rm -f {} +

# Удаляем папку build
clean_build:
	@rm -rf ./$(BUILD)

# Удаляем папку с документацией
clean_doc:
	@rm -rf ./$(DOC)

# Удаляем рекорды
clean_high_score:
	@rm -rf ./high_score_tetris.txt ./high_score_snake.txt

# Удаляем архив с билдами и документацией
clean_dist:
	@rm -rf dist

# Всё удаляем
clean_all: clean clean_tests clean_build clean_doc clean_high_score clean_dist

# Загружаем проект с чистого листа
rebuild: clean_all all