# Genie tutorial-April-2024, ICTS-Banglore, India 


<ul>
<li>Schdule of the workshop:  https://www.icts.res.in/event/page/27770</li>
</ul>

Clone the Working directory and codes for tutorial session:   

      git clone https://github.com/JaydipSingh/genie_tutorial.git

  **Step - 1**: Start by installing Apptainer/Singularity container in your linux/windows system and just follow these steps, use build and shell command to build and open the container. 

 
    apptainer build --sandbox Fedora40 docker://fedora:40 
    apptainer shell --writable --fakeroot Fedora40/


Note: In case you want to delete your sandbox : 
    
     chmod -R +rw Fedora40 && rm -rf Fedora40

 **Step - 2**  The lists the prerequisite packages that need to be installed to be able to configure, build and run ROOT. You can install these packages from anywhere not dependent on folder label. 
 

    yum install git make cmake gcc-c++ gcc binutils xrootd-client-devel.x86_64 root-net-davix.x86_64 libX11-devel libXpm-devel libXft-devel libXext-devel python \
    mesa-libGL-devel mesa-libGLU-devel glew-devel ftgl-devel mysql-devel \
    fftw-devel cfitsio-devel graphviz-devel libuuid-devel \
    avahi-compat-libdns_sd-devel openldap-devel python-devel python3-numpy \
    libxml2-devel gsl-devel readline-devel qt5-qtwebengine-devel \
    R-devel R-Rcpp-devel R-RInside-devel libnsl2-devel.x86_64 libtool davix-devel


**Step - 3 : Pythia6 and Pythia8 Installation**

Install everything in /opt/ folder 
       

      cd /opt/
       mkdir Pythia && cd Pythia
       mkdir Pythia6 && cd Pythia6 

Copy and paste the code from here to install pythia6 =>https://github.com/GENIE-MC/Generator/blob/master/src/scripts/build/ext/build_pythia6.sh

    chmod  +x build_pythia6.sh 
    ./build_pythia6.sh 

Same for Pythia8 ( optional ):

         cd /opt/Pythia/ 
         mkdir Pythia8 && cd Pythia8 

          curl -o pythia8310.tgz https://pythia.org/download/pythia83/pythia8310.tgz
           tar xvfz pythia8310.tgz
           ln -s pythia8310 pythia8
           cd pythia8310
           ./configure --prefix=/opt/Pythia/Pythia8 
           make 


**Step - 4 ROOT installation** 
I always prefer to go with the latest version of root but you can work with your version, check your path very carefully in the arguments. I have disable some of the features available in my installation, you can ON/OFF more to save the installation time.

     cd /opt/ 
     git clone https://github.com/root-project/root.git
     cd root
     git checkout -b v6-30-00 v6-30-00
     cd  ..
     mkdir  root_build root_install 
     cd  root_build
     cmake -DCMAKE_INSTALL_PREFIX=/opt/root_install/ -Dmathmore=ON -Dpythia6=ON -DPYTHIA6_DIR=/opt/Pythia/Pythia6/v6_428/ -DPYTHIA6_INCLUDE_DIR=/opt/Pythia/Pythia6/v6_428/inc/ -DPYTHIA6_LIBRARY=/opt/Pythia/Pythia6/v6_428/lib/libPythia6.so  -Dpythia8=ON -DPYTHIA8_DIR=/opt/Pythia/Pythia8/pythia8/ -DPYTHIA8_INCLUDE_DIR=/opt/Pythia/Pythia8/pythia8/include/ -DPYTHIA8_LIBRARY=/opt/Pythia/Pythia8/pythia8/lib/libpythia8.so -Dxrootd=OFF -Dwebgui=OFF -Dtmva-pymva=OFF -Dtmva=OFF -Dtmva-cpu=OFF /opt/root/
    cmake --build . --target install -- -j4 

*Note :* One can verify root installation as fallows.

     source /opt/root_install/bin/thisroot.sh
     root 
 

**Step - 5** Log4 cpp Installation : 
Install it from here only, download it, and copy-paste it in folder “/opt/Log4cpp”: 
https://sourceforge.net/projects/log4cpp/
     
     cd /opt/
     mkdir Log4cpp      /// paste and untar the download in this folder 
     cd log4cpp
     ./autogen.sh
     ./configure --prefix=/opt/Log4cpp/
      make 
      make install 


**Step - 6** Install libxml2 library :  yum install libxml2

**Step - 7** Install LHAPDF library : ( my version LHAPDF-6.5.4 )

    cd /opt/
    mkdir LHAPDF
    cd LHAPDF
    wget https://lhapdf.hepforge.org/downloads/?f=LHAPDF-6.5.4.tar.gz -O LHAPDF-6.5.4.tar.gz
    tar xf LHAPDF-6.5.4.tar.gz
    cd LHAPDF-6.5.4
    ./configure --prefix=/opt/LHAPDF/    // This one may have issue with python interface so disable-python  
    ./configure --prefix=/opt/LHAPDF/ --disable-python
    make
    make install 

IMPORTANT INFORMATION ABOUT PDF SETS;LHAPDF no longer bundles PDF set data in the package tarball.
The sets are instead all stored online at : http://lhapdfsets.web.cern.ch/lhapdfsets/current/, and you should install those that you wish to use into : /Users/jdsingh/GENIE/src/LHAPDF/share/LHAPDF
The downloadable PDF sets are packaged as tarballs, which
must be expanded to be used. The simplest way to do this is with the 'lhapdf' script, e.g. to install the CT10nlo PDF set: lhapdf install CT10nlo
The same effect can be achieved manually with, e.g.: 

    wget http://lhapdfsets.web.cern.ch/lhapdfsets/current/CT10nlo.tar.gz -O- | tar xz -C /opt/LHAPDF/share/LHAPDF

**Step - 8**
Prepare a script for environment setup :
 
        cd /opt/
        vi do_env_R_3_02.sh

Paste the following code but set your path correctly: 


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

**Step - 9** GENIE INSTALLATION : We will use this release for this tutorial : https://github.com/GENIE-MC/Generator/releases/tag/R-3_02_00
 
    cd /opt/
    source do_env_R_3_02.sh 
    wget https://github.com/GENIE-MC/Generator/archive/refs/tags/R-3_02_00.tar.gz   // untar it using : tar -zxvf .....
    mkdir /opt/R-3_02_00_build 
    cd Generator-R-3_02_00
    ./configure --prefix=/opt/R-3_02_00_build/ --enable-atmo --enable-pythia8 --enable-lhapdf6 --with-lhapdf6-lib=/opt/LHAPDF/lib --with-lhapdf6-inc=/opt/LHAPDF/include --with-log4cpp-inc=/opt/Log4cpp/include --with-log4cpp-lib=/opt/Log4cpp/lib --with-pythia8-lib=/opt/Pythia/Pythia8/pythia8/lib --with-pythia6-lib=/opt/Pythia/Pythia6/v6_428/lib --with-pythia6-inc=/opt/Pythia/Pythia6/v6_428/inc
    make && make install 


**References:**<br />
      1) GENIE Installation: https://hep.ph.liv.ac.uk/~costasa/genie/get_started.html <br />
      2) GENIE development: http://releases.genie-mc.org/   <br />
      3) GENIE User guide: https://genie-docdb.pp.rl.ac.uk/cgi-bin/ShowDocument?docid=2 <br />
      4)  Recent workshop: https://indico.fnal.gov/event/57388/ <br />
      5) NUSTEC workshop :  https://indico.phys.vt.edu/event/44/timetable/#20210315.detailed <br />
      6) Pythia6 Script : https://github.com/GENIE-MC/Generator/tree/master/src/scripts/build/ext  <br />
      7) Install singularity: https://singularity-tutorial.github.io/01-installation/
**Particles and Ions code** See Appendix D 

=>Electorn : 12,-12, Muon : 14, -14, Tau : 16, -16 <br />
=>GENIE has adopted the standard PDG (2006) particle codes. For ions it has adopted a PDG extension, using the 10-digit code 10LZZZAAAI where AAA is the total baryon number, ZZZ is the total charge, 
L is the number of strange quarks and I is the isomer number (I=0 corresponds to the ground state). <br />
So, for example:<br />
1000010010 → H1 <br />
1000060120 → C12 <br />
1000080160 → O16 <br />
1000260560 → Fe56<br />
and so on.

**Data generation and analysis excercise**

*Step (i)* First, open the Sandbox with the shell command and do the source to start working with GENIE.

  apptainer shell Fedora40   // no need to add extra arguments this time ex: --writable --fakeroot
  source /opt/do_env_R_3_03.sh
 
*Step (ii)*  Download the Xscetion-generated data from here: https://scisoft.fnal.gov/scisoft/packages/genie_xsec/
Keep the file in a folder: genie_tutorial/Xsec_data/ 

*Step (iii)*   Electorn : 12,-12, Muon : 14, -14, Tau : 16, -16

       gevgen -r 1 -n 1000 -p 14 -t 1000080160 -e 1 --cross-sections ../XSec_data/gxspl-NUsmall.xml --seed 171872 --event-generator-list CCQE 
       gevdump -f generated_file_name -n 10   // query check the dump data //  

*Step (iV)* Using neutrino flux file, Ex- DUNE-ND_flux file 
 
          gevgen -r 2 -n 1000 -p 14 -t 1000010020 -e .2 4.5 -f /opt/flux_files/DUNE-nu-NDFlux.dat --cross-sections XSec_data/gxspl-NUsmall.xml --seed 171872 --event-generator-list CCQE

*Example 1 :* Generate events using detector geometry, Ex: ANNIE, DUNE-ND/FD and INO , define your own detector geometry, will be discussed into the GEANT4 session. 

     gevgen -r 1 -n 100 -p 14 -g ../gdml/annie_v04.gdml -t 1000080160 -e 1 --cross-sections /home/jaydip/GENIE_tutorial/XSec_data/gxspl-NUsmall.xml --seed 171872 --event-generator-list CCQE 


To use a target mix of 88.79% (weight fraction) O16 and 11.21% H (i.e. ‘water’) type:
‘-g 1000080160[0.8879],1000010010[0.1121]’


     gevgen -r 1 -n 100 -p 14 -g ../gdml/annie_v04.gdml -t 1000080160[0.8879],1000010010[0.1121] -e 1 --cross-sections /home/jaydip/GENIE_tutorial/XSec_data/gxspl-NUsmall.xml --seed 171872 --event-generator-list CCQE

##$$$$$$$$$$$$   END INSTALLATION AND VALIDATION $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

 Use this code for your analysis : 
      ./gtestEventLoop -f gntp.1.ghep.root

File to check or set the models : 
/opt/Generator-R-3_02_00/config/Messenger.xml


  Problem 1: Generate 10K events for your experiment ( ex : DUNE ), and plot the distribution of the event as a function of true and reconstructed neutrino energy. 

Tested at my EX1 : gevgen -r 2 -n 10000 -p 14 -t 1000080160 -e 1 --cross-sections /home/jaydip/GENIE_tutorial/XSec_data/gxspl-NUsmall.xml --seed 171872 --event-generator-list CCQE

Note : To use a target mix of 88.79% (weight fraction) O16 and 11.21% H (i.e. ‘water’) type: ‘-g 1000080160[0.8879],1000010010[0.1121]’
 


