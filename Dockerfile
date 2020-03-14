FROM ubuntu:18.04 AS builder
WORKDIR /project
RUN apt-get update && \
    apt-get install -y bash cmake git vim gcc apt-utils && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

SHELL ["/bin/bash", "-c"]

RUN groupadd -r chapter7 && useradd -r -s /bin/false -g chapter7 chapter7

WORKDIR /chapter7
RUN chown -R chapter7:chapter7 /chapter7
USER chapter7

RUN git clone --recursive https://github.com/essentialsofparallelcomputing/Chapter7.git

ENTRYPOINT ["bash"]
