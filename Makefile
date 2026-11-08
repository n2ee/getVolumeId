CC       = gcc
CFLAGS   = -Wall -Wextra -O2
TARGET   = get_vsn
SOURCE   = get_vsn.c
DESTDIR  = /usr/local/bin

.PHONY: all install clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

install: $(TARGET)
	install -o root -g wheel -m 755 getVolumeId $(DESTDIR)/getVolumeId
	install -o root -g wheel -m 4755 $(TARGET) $(DESTDIR)/$(TARGET)
	codesign --force --sign - $(DESTDIR)/$(TARGET)

clean:
	rm -f $(TARGET)

