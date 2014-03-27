include make.inc

LIB_VER       = 3.00.00
LIB_HEPMC_A   = libHepMC.a
LIB_HEPMC_SO  = libHepMC.so
LIB_HEPMC_OBJ = src/GenParticle.o src/GenEvent.o src/GenVertex.o \
                src/Log.o src/GenEventVersion.o \
                src/IO_Base.o src/IO_GenEvent.o src/IO_HepMC2_adapter.o

all: lib

lib: $(LIB_HEPMC_OBJ)
	ar cr lib/$(LIB_HEPMC_A) $(LIB_HEPMC_OBJ)
	$(LD) $(LDFLAGS) $(SOFLAGS) -o lib/$(LIB_HEPMC_SO).$(LIB_VER) $(LIB_HEPMC_OBJ)
	ln -sf $(LIB_HEPMC_SO).$(LIB_VER) lib/$(LIB_HEPMC_SO)

%.o: %.cc
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f src/*.o lib/*
