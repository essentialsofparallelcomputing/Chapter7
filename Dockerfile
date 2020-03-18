FROM ubuntu:18.04 AS builder
WORKDIR /project
RUN apt-get update && \
    apt-get install -y cmake git vim gcc g++ wget software-properties-common && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Installing latest GCC compiler (version 9) for best vectorization
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get update && \
    apt-get install -y gcc-9 g++-9 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9 --slave /usr/bin/gcov gcov /usr/bin/gcov-9

# Installing Intel compilers since they give the best vectorization among compiler vendors
# Also installing Intel Advisor to look at vectorization performance
RUN wget -q https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS-2023.PUB
RUN apt-key add GPG-PUB-KEY-INTEL-SW-PRODUCTS-2023.PUB
RUN rm -f GPG-PUB-KEY-INTEL-SW-PRODUCTS-2023.PUB
RUN echo "deb https://apt.repos.intel.com/oneapi all main" >> /etc/apt/sources.list.d/oneAPI.list
RUN echo "deb [trusted=yes arch=amd64] https://repositories.intel.com/graphics/ubuntu bionic main" >> /etc/apt/sources.list.d/intel-graphics.list
RUN apt-get update && \
     apt-get install -y \
             intel-hpckit-getting-started \
             intel-oneapi-common-vars \
             intel-oneapi-common-licensing \
             intel-oneapi-dev-utilities \
             intel-oneapi-icc \
             intel-oneapi-ifort \
             intel-oneapi-openmp \
             intel-oneapi-inspector && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Needed libraries for Intel Inspector graphics user interface
RUN apt-get update && \
    apt-get install -y libgtk2.0-0 libxxf86vm1 libsm6 libnss3 libnss3 libx11-xcb1 libxtst6 \
            libasound2 libatk-bridge2.0-0 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

SHELL ["/bin/bash", "-c"]

RUN groupadd chapter7 && useradd -m -s /bin/bash -g chapter7 chapter7

WORKDIR /home/chapter7
RUN chown -R chapter7:chapter7 /home/chapter7
USER chapter7

RUN git clone --recursive https://github.com/essentialsofparallelcomputing/Chapter7.git

ENTRYPOINT ["bash"]
