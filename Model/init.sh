#check if build already exists, if not
mkdir build #function 0
cd build
# if exists delete everything inside it

#Function with and bool addon cmake args
mkdir build
cd build # down below is the bool addon
cmake .. #cmake args here
make install
cd .. #out of build
cd .. #out of folder #fucntion 2
#function end

#check if wget is installed, if not install it or throw warnings
wget https://github.com/mlpack/mlpack/archive/refs/tags/4.3.0.tar.gz
tar -xzf 4.3.0.tar.gz
mv mlpack-4.3.0 mlpack
rm -r 4.3.0.tar.gz
cd mlpack
mkdir build # function 0
cd build

# cereal
wget https://github.com/USCiLab/cereal/archive/refs/tags/v1.3.2.tar.gz
tar -xzf v1.3.2.tar.gz
mv cereal-1.3.2 cereal
cd cereal
mkdir build #function 1,2, cmake args = -DBUILD_DOC=OFF -DBUILD_SANDBOX=OFF -DBUILD_TESTS=OFF
cd build
cmake -DBUILD_DOC=OFF -DBUILD_SANDBOX=OFF -DBUILD_TESTS=OFF ..
make install
cd ..
cd ..

# in mlpack build
cmake -DDOWNLOAD_DEPENDENCIES=ON -DBUILD_CLI_EXECUTABLES=OFF ..
# check if deps folder is created
# check for ens, if no ens
cd deps
cd ensmallen-2.20.0
mkdir build # function 1,2 no cmake args
cd build
cmake ..
make install
cd ..
cd ..

# in mlpack build
make install
cd ..
