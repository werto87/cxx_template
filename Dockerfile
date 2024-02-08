FROM conanio/gcc13-ubuntu16.04

COPY src /home/conan/cxx_template/src
COPY CMakeLists.txt /home/conan/cxx_template
COPY conanfile.py /home/conan/cxx_template
COPY main.cxx /home/conan/cxx_template


WORKDIR /home/conan/cxx_template

RUN sudo chown -R conan /home/conan  && conan install . --output-folder=build --settings build_type=Release  --settings compiler.cppstd=gnu20 --build=missing

WORKDIR /home/conan/cxx_template/build

RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -D CMAKE_BUILD_TYPE=Release

RUN cmake --build .