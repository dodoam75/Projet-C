# ============================================================
# Makefile - Compilation du projet ShopFlow
# ------------------------------------------------------------
# make          : compile tous les modules et cree l'executable 'shopflow'
# make valgrind : lance le programme sous valgrind (detection des fuites)
# make clean    : supprime les .o et l'executable
# Options -Wall -Wextra : exigees par le sujet (zero avertissement).
# ============================================================
CC      = gcc
CFLAGS  = -Wall -Wextra -g
TARGET  = shopflow
SRC     = main.c produit.c client.c commande.c statistique.c utils.c initialisation.c
OBJ     = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean valgrind
