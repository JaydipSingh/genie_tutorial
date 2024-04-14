# Genie tutorial ICTS-Banglore, India 



<ul>
<li>Schdule of the workshop:  https://www.icts.res.in/event/page/27770</li>
</ul>

  **Step - 1**: Start by installing Apptainer in your linux/windows system and just follow these steps, use build and shell command to build and open the container. 

 
    apptainer build --sandbox Fedora40 docker://fedora:40 
    apptainer shell --writable --fakeroot Fedora40/


Note: In case you want to delete your sandbox : 
    
     chmod -R +rw Fedora40 && rm -rf Fedora40

 **Step - 2**  The lists the prerequisite packages that need to be installed to be able to configure, build and run ROOT.
 

    yum install git make cmake gcc-c++ gcc binutils xrootd-client-devel.x86_64 \ root-net-davix.x86_64 libX11-devel libXpm-devel libXft-devel libXext-devel python \
    mesa-libGL-devel mesa-libGLU-devel glew-devel ftgl-devel mysql-devel \
    fftw-devel cfitsio-devel graphviz-devel libuuid-devel \
    avahi-compat-libdns_sd-devel openldap-devel python-devel python3-numpy \
    libxml2-devel gsl-devel readline-devel qt5-qtwebengine-devel \
    R-devel R-Rcpp-devel R-RInside-devel libnsl2-devel.x86_64 libtool


**Step - 3 : Pythia6 and Pythia8 Installation**

Install everything in /opt/ folder 

       mkdir /opt/Phythia/Pythia6 && cd /opt/Pythia/Pythia6

Copy and paste the code from here to install pythia6 =>https://github.com/GENIE-MC/Generator/blob/master/src/scripts/build/ext/build_pythia6.sh

    chmod  +x build_pythia6.sh 
    ./build_pythia6.sh 

Same for Pythia8 ( optional ):

         mkdir /opt/Phythia/Pythia8 && cd /opt/Pythia/Pythia8 

          curl -o pythia8310.tgz https://pythia.org/download/pythia83/pythia8310.tgz
           tar xvfz pythia8310.tgz
           ln -s pythia8310 pythia8
           cd pythia8310
           ./configure --prefix=/opt/Pythia/Pythia8 
           make 


**Step - 4 ROOT installation** 
I always prefer to go with the latest version of root but you can work with your version, check your path very carefully in the arguments. I have disable some of the features available in my installation, you can ON/OFF more to save the installation time.


     git clone https://github.com/root-project/root.git
     cd root
     git checkout -b v6-30-00 v6-30-00
     cd  ..
     mkdir  root_build && root_install 
     cd  root_build
     cmake -DCMAKE_INSTALL_PREFIX=/opt/root_install/ -Dmathmore=ON -Dpythia6=ON -DPYTHIA6_DIR=/opt/Pythia/Pythia6/v6_428/ -DPYTHIA6_INCLUDE_DIR=/opt/Pythia/Pythia6/v6_428/inc/ -DPYTHIA6_LIBRARY=/opt/Pythia/Pythia6/v6_428/lib/libPythia6.so  -Dpythia8=ON -DPYTHIA8_DIR=/opt/Pythia/Pythia8/pythia8/ -DPYTHIA8_INCLUDE_DIR=/opt/Pythia/Pythia8/pythia8/include/ -DPYTHIA8_LIBRARY=/opt/Pythia/Pythia8/pythia8/lib/libpythia8.so -Dxrootd=OFF -Dwebgui=OFF -Dtmva-pymva=OFF -Dtmva=OFF -Dtmva-cpu=OFF /opt/root/
    cmake --build . --target install -- -j4 

*Note :* One can verify root installation as fallows.

     source /opt/root_install/bin/thisroot.sh
     root 
 

**Step - 5** Log4 cpp Installation : 

mkdir /opt/Log4cpp/ 

Install it from here only, download it, and copy-paste it in folder “/opt/Log4cpp”: 
https://sourceforge.net/projects/log4cpp/
  cd log4cpp
 ./autogen.sh
./configure –prefix=/opt/Log4cpp/
make && make install 


Install libxml2 library : 



Install LHAPDF library : ( my version LHAPDF-6.5.4 )


wget https://lhapdf.hepforge.org/downloads/?f=LHAPDF-6.5.4.tar.gz -O LHAPDF-6.5.4.tar.gz
# ^ or use a web browser to download, which will get the filename correct
tar xf LHAPDF-6.5.4.tar.gz
cd LHAPDF-6.5.4
./configure --prefix=/path/for/installation

 This one may have issue with python interface so use this Or 

 ./configure --prefix=/opt/lhapdf_install/ --disable-python

IMPORTANT INFORMATION ABOUT PDF SETS
LHAPDF no longer bundles PDF set data in the package tarball.
The sets are instead all stored online at
  http://lhapdfsets.web.cern.ch/lhapdfsets/current/
and you should install those that you wish to use into
  /Users/jdsingh/GENIE/src/LHAPDF/share/LHAPDF
The downloadable PDF sets are packaged as tarballs, which
must be expanded to be used. The simplest way to do this is with
the 'lhapdf' script, e.g. to install the CT10nlo PDF set:
  lhapdf install CT10nlo
The same effect can be achieved manually with, e.g.:
  wget http://lhapdfsets.web.cern.ch/lhapdfsets/current/CT10nlo.tar.gz -O- | tar xz -C /Users/jdsingh/GENIE/src/LHAPDF/share/LHAPDF


Prepare a script for environment setup : 

vi do_env_R_3_03.sh
Paste the following code but set your path correctly: 

#!/bin/bash
echo "Setting GENIE environment variables..."
export GENIEBASE=/opt
export GENIE=$GENIEBASE/Generator-R-3_02_00
export PYTHIA8=$GENIEBASE/Pythia/Pythia8/pythia8/lib
export PYTHIA6=$GENIEBASE/Pythia/Pythia6/v6_428/lib
export ROOTSYS=$GENIEBASE/root_install
export LHAPATH=$GENIEBASE/lhapdf_install
export LHAPDF_INC=$GENIEBASE/lhapdf_install/include
export LHAPDF_LIB=$GENIEBASE/lhapdf_install/lib
export XSECSPLINEDIR=$GENIEBASE/data
export LD_LIBRARY_PATH=$LHAPDF_LIB:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$PYTHIA8:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$PYTHIA6:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$GENIE/lib:$LD_LIBRARY_PATH
export PATH=$GENIE/bin:$ROOTSYS/bin:$PATH
unset GENIEBASE


source /opt/do_env_R_3_03.sh

GENIE INSTALLATION :

https://github.com/GENIE-MC/Generator/releases/tag/R-3_02_00
 
cd /opt/ 
wget https://github.com/GENIE-MC/Generator/archive/refs/tags/R-3_02_00.tar.gz
mkdir /opt/R-3_02_00_build 
cd into the source folder and configure it now: 
cd Generator-R-3_02_00


./configure --prefix=/opt/R-3_02_00_build/ --enable-atmo --enable-pythia8 --enable-lhapdf6 --with-lhapdf6-lib=/opt/lhapdf_install/lib --with-lhapdf6-inc=/opt/lhapdf_install/include --with-log4cpp-inc=/uer/include --with-log4cpp-lib=/usr/lib --with-pythia8-lib=/opt/Pythia/Pythia8/pythia8/lib --with-pythia6-lib=/opt/Pythia/Pythia6/v6_428/lib --with-pythia6-inc=/opt/Pythia/Pythia6/v6_428/inc


References:<br />
      1) GENIE Installation: https://hep.ph.liv.ac.uk/~costasa/genie/get_started.html <br />
      2) GENIE development: http://releases.genie-mc.org/   <br />
      3) GENIE User guide: https://genie-docdb.pp.rl.ac.uk/cgi-bin/ShowDocument?docid=2 <br />
      4)  Recent workshop: https://indico.fnal.gov/event/57388/ <br />
      5) NUSTEC workshop :  https://indico.phys.vt.edu/event/44/timetable/#20210315.detailed <br />
      6) Pythia6 Script : https://github.com/GENIE-MC/Generator/tree/master/src/scripts/build/ext  <br />
      7) Install singularity: https://singularity-tutorial.github.io/01-installation/


 
Let’s generate the first set of data : 
Step 1: Download the Xscetion-generated data from here: https://scisoft.fnal.gov/scisoft/packages/genie_xsec/

Keep the file in a folder: /GENIE_tutorial/Xsec_data 
In the same way download the flux file and keep it in another folder: /GENIE_tutorial/flux_file

 First, open the Sandbox with the shell command and do the source to start working with GENIE. 

apptainer shell Fedora40
source /opt/do_env_R_3_03.sh

gevgen -r 3 -n 100 -p 14 -t 1000010020 -e 1.0 --cross-sections /home/jaydip/GENIE_tutorial/XSec_data/gxspl-NUsmall.xml --seed 171872

Using flux file, Ex- DUNE-ND_flux file 
gevgen -r 2 -n 1000 -p 14 -t 1000010020 -e .2 4.5 -f /home/jaydip/GENIE_tutorial/flux_files/DUNE-nu-NDFlux.dat --cross-sections /home/jaydip/GENIE_tutorial/XSec_data/gxspl-NUsmall.xml --seed 171872



The command for printing the event.

  gevdump -f gntp.1.ghep.root
  
   gevdump -f gntp.1.ghep.root -n 1,10   //           printing events from 1 to 10 
    gevdump -f gntp.1.ghep.root -n 1     //  

   Use this code for your analysis : 
      ./gtestEventLoop -f gntp.1.ghep.root

File to check or set the models : 
/opt/Generator-R-3_02_00/config/Messenger.xml


  Problem 1: Generate 10K events for your experiment ( ex : DUNE ), and plot the distribution of the event as a function of true and reconstructed neutrino energy. 

Tested at my EX1 : gevgen -r 2 -n 10000 -p 14 -t 1000080160 -e 1 --cross-sections /home/jaydip/GENIE_tutorial/XSec_data/gxspl-NUsmall.xml --seed 171872 --event-generator-list CCQE

Note : To use a target mix of 88.79% (weight fraction) O16 and 11.21% H (i.e. ‘water’) type: ‘-g 1000080160[0.8879],1000010010[0.1121]’
 


