OUTNAME = manuscript-$(shell date +%F).pdf

all: compression.pdf

compression.pdf: manuscript.tex
	pdflatex manuscript.tex; bibtex manuscript; pdflatex manuscript.tex; pdflatex manuscript.tex;
	mv manuscript.pdf ${OUTNAME}

clean:
	rm -rf manuscript*.pdf
	rm -f manuscript.log 
	rm -f manuscript.dvi 
	rm -f manuscript.aux 
	rm -f manuscript.bbl
	rm -f manuscript.blg
	rm -f manuscript.bcf