CC       = gcc
CFLAGS   = -Wall -Wextra -g
TARGET   = inverted.exe

SRCS     = main.c \
           create_database.c \
           insert_last.c \
           display_database.c \
           file_validation.c \
           search.c \
           save_database.c \
           update_database.c \
           hash_function.c

OBJS     = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c inverted_Search.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET) $(ARGS)

.PHONY: all clean run