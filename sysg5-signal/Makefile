EXEC=read_time_out read_time_out2 nb_signal file_attente_signal blocage_signal_sans_masque blocage_signal_avec_masque bascule bascule_viable rapport

all: $(EXEC)

read_time_out: codes/read_time_out.c
	gcc codes/read_time_out.c -o programmes/read_time_out.exe

read_time_out2: codes/read_time_out2.c
	gcc codes/read_time_out2.c -o programmes/read_time_out2.exe

nb_signal: codes/nb_signal.c
	gcc codes/nb_signal.c -o programmes/nb_signal.exe

file_attente_signal: codes/file_attente_signal.c
	gcc codes/file_attente_signal.c -o programmes/file_attente_signal.exe

blocage_signal_sans_masque : codes/blocage_signal_sans_masque.c
	gcc codes/blocage_signal_sans_masque.c -o programmes/blocage_signal_sans_masque.exe

blocage_signal_avec_masque : codes/blocage_signal_avec_masque.c
	gcc codes/blocage_signal_avec_masque.c -o programmes/blocage_signal_avec_masque.exe

bascule : codes/bascule.c
	gcc codes/bascule.c -o programmes/bascule.exe

bascule_viable : codes/bascule_viable.c
	gcc codes/bascule_viable.c -o programmes/bascule_viable.exe

rapport : RapportSIGNALSCHELLEKENS52010.tex
	pdflatex RapportSIGNALSCHELLEKENS52010.tex
	pdflatex RapportSIGNALSCHELLEKENS52010.tex