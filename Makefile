all:index.html
%.html:%.txt ${IMGDST} img/photo_serial_small.jpg
	asciidoc -a data-uri -a img $<
%.pdf:%.txt ${IMGDST}
	a2x -fpdf -darticle --fop  $<
clean:
	rm -rf *.html *.pdf img
