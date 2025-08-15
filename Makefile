CC = gcc
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    CFLAGS = -fPIC -Wall -bundle -undefined dynamic_lookup
    PAMDIR = /usr/local/lib/pam
    PAM_CONFIG = /etc/pam.d/sudo
else
    CFLAGS = -fPIC -Wall -shared
    PAMDIR = /lib/security
    PAM_CONFIG = /etc/pam.d/sudo
endif

all: pam_yes.so

pam_yes.so: pam_yes.c
ifeq ($(UNAME_S),Darwin)
	$(CC) $(CFLAGS) -o pam_yes.so pam_yes.c
else
	$(CC) $(CFLAGS) -o pam_yes.so pam_yes.c -lpam
endif

install: pam_yes.so
ifeq ($(UNAME_S),Darwin)
	codesign -s - pam_yes.so || true
	sudo mkdir -p $(PAMDIR)
	sudo cp pam_yes.so $(PAMDIR)/pam_yes.so.2
else
	sudo cp pam_yes.so $(PAMDIR)/
endif
	@echo "Module installed. Run 'make configure' for setup instructions."


clean:
	rm -f pam_yes.so

configure:
ifeq ($(UNAME_S),Darwin)
	@echo "Add this line to $(PAM_CONFIG):"
	@echo "auth sufficient $(PAMDIR)/pam_yes.so.2"
	@echo "Note: macOS PAM configuration may require additional setup"
else
	@echo "Add this line to $(PAM_CONFIG):"
	@echo "auth sufficient pam_yes.so"
endif

.PHONY: all install clean configure