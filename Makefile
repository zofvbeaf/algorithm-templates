all:
	xelatex -shell-escape algorithm_template.tex
	cp algorithm_template.pdf ../../public/pdf/
clean:
	rm -rf *.aux *.log *.out *.toc _minted-algorithm_template
	

