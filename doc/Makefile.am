## Process this file with automake to produce Makefile.in.

# Dia, the version i have at least, doesn't do very good EPS output
# (some of the text is scaled strangely). So this will work, but 
# it is probably better to use something like gimp to convert the 
# dia exported PNG files to EPS manually.
#
# Here we use 'convert' from the well known 'ImageMagick' package
# to do conversion from png to eps/pdf for figures. 
# PDF form is required for quagga.pdf, using PDFTex at least.
#
# TeX implementation, which we depend on already anyway.
#
# dia -> (dia) -> png -> (convert) -> eps -> (epstopdf) -> pdf
SUFFIXES = .png .eps .dia .pdf
DIATOPNG = dia -t png -e
DIATOEPS = dia -t eps -e
PNGTOEPS = convert -antialias -contrast -despeckle
PNGTOPDF = $(PNGTOEPS)
EPSTOPDF = epstopdf

# The figure sources
figures_names_parts = -normal-processing -rs-processing
figures_sources = $(figures_names_parts:%=fig%.dia)
figures_png = $(figures_names_parts:%=fig%.png)
figures_pdf = $(figures_names_parts:%=fig%.pdf)
figures_eps = $(figures_names_parts:%=fig%.eps)
figures_txt = $(figures_names_parts:%=fig%.txt)

# rather twisted logic because we have to build PDFs of the EPS figures for
# PDFTex and yet build one PDF, quagga.pdf, from texi source. Which means we
# cant rely on a single automatic rule for *.pdf, eg the one automatically
# provided by automake. If you are an automake wizard, please feel free to
# compact it somehow.

#quagga.pdf: $(info_TEXINFOS) $(quagga_TEXINFOS)
#	$(TEXI2PDF) -o "$@" $< || true

info_TEXINFOS = quagga.texi

quagga_TEXINFOS = appendix.texi basic.texi bgpd.texi filter.texi \
	install.texi ipv6.texi kernel.texi main.texi ospf6d.texi ospfd.texi \
	overview.texi protocol.texi ripd.texi ripngd.texi routemap.texi \
	snmp.texi vtysh.texi routeserver.texi defines.texi $(figures_png) \
	snmptrap.texi ospf_fundamentals.texi isisd.texi nhrpd.texi \
	$(figures_txt)

.png.eps:
	$(PNGTOEPS) $< "$@"

.png.pdf:
	$(PNGTOPDF) $< "$@"

.dia.png:
	$(DIATOPNG) "$@" $<

man_MANS =

if PIMD
man_MANS += pimd.8
endif

if BGPD
man_MANS += bgpd.8
endif

if ISISD
man_MANS += isisd.8
endif

if OSPF6D
man_MANS += ospf6d.8
endif

if OSPFCLIENT
man_MANS += ospfclient.8
endif

if OSPFD
man_MANS += ospfd.8
endif

if RIPD
man_MANS += ripd.8
endif

if RIPNGD
man_MANS += ripngd.8
endif

if NHRPD
man_MANS += nhrpd.8
endif

if VTYSH
man_MANS += vtysh.1
endif

if WATCHQUAGGA
man_MANS += watchquagga.8
endif

if ZEBRA
man_MANS += zebra.8
endif

AM_MAKEINFOHTMLFLAGS = --css-include=$(srcdir)/texinfo.css

EXTRA_DIST = BGP-TypeCode draft-zebra-00.ms draft-zebra-00.txt \
	bgpd.8 isisd.8 ospf6d.8 ospfclient.8 ospfd.8 ripd.8 \
	ripngd.8 nhrpd.8 pimd.8 vtysh.1 watchquagga.8 zebra.8 \
	mpls/ChangeLog.opaque.txt mpls/cli_summary.txt \
	mpls/opaque_lsa.txt mpls/ospfd.conf \
	$(figures_sources) $(figures_png) $(figures_txt) \
	texinfo.tex texinfo.css

draft-zebra-00.txt: draft-zebra-00.ms
	groff -T ascii -ms $< > $@

CLEANFILES = *.{fn,fns,cp,cps,ky,kys}
DISTCLEANFILES = quagga.info*

# do nothing for DVI, so we don't have to generate or distribute EPS
# figures
dvi: # nothing
