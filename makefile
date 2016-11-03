
PROJECTS := FrameLight \
2NPuntiSfera \
ODE_exponential \
ODE_oscillator \
PDE_Gottlieb \
PDE_KDV \
PDE_waves

all:
	@for i in $(PROJECTS) ; do \
	$(MAKE) -C $$i ;\
	done

clean:
	@for i in $(PROJECTS) ; do \
	$(MAKE) -C $$i clean ;\
	done

cleanall:
	@for i in $(PROJECTS) ; do \
	$(MAKE) -C $$i cleanall ;\
	done
	
