
PRXS_DIR=/usr/bin
PRXS=$(PRXS_DIR)/prxs
LIBS=/usr/local/lib
SOURCE=mod_limit_login_post_pass.c

mod_libmemcached_deny.so:
	$(PRXS) -c $(SOURCE) 

install: mod_libmemcached_deny.so
	$(PRXS) $(SOURCE) -i

clean:
	rm -v *.la
	rm -v *.lo
	rm -v *.o
	rm -frv .libs
