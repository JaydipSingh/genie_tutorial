## script to setup env for GENIE 

echo "Setting GENIE environment variables..."

export WORKDIR=/opt # !!!

#genie
export GENIE=${WORKDIR}/Generator-R-3_02_00
export PATH=$GENIE/bin:$PATH
export LD_LIBRARY_PATH=$GENIE/lib:$LD_LIBRARY_PATH
export XSECSPLINEDIR=$WORKDIR/data

#root
export ROOTSYS=${WORKDIR}/root_install # !!!
source $ROOTSYS/bin/thisroot.sh

#pythia (location of libPythia6.so)
export PYTHIA6=${WORKDIR}/Pythia/Pythia6/v6_428/lib # !!!
export LD_LIBRARY_PATH=$PYTHIA6:$LD_LIBRARY_PATH

#lhapdf
export LHAPDF=${WORKDIR}/LHAPDF # !!!
export LHAPATH=$GENIE/data/evgen/pdfs
export PATH=$LHAPDF/bin:$PATH
export LD_LIBRARY_PATH=$LHAPDF/lib:$LD_LIBRARY_PATH

#log4cpp (if installed locally)
export LOG4CPP=${WORKDIR}/Log4cpp/
export PATH=$LOG4CPP/bin:$PATH
export LD_LIBRARY_PATH=$LOG4CPP/lib:$LD_LIBRARY_PATH

#libxml2 (if installed locally)
#LIBXML2=/your/software/area/gsoft/libxml2/install
#export PATH=$LIBXML2/bin:$PATH
#export LD_LIBRARY_PATH=$LIBXML2/lib:$LD_LIBRARY_PATH
