#!/bin/sh
docker build --no-cache -t chapter7 .
#docker run -it --entrypoint /bin/bash chapter7
docker build --no-cache -f Dockerfile.Ubuntu20.04 -t chapter7 .
#docker run -it --entrypoint /bin/bash chapter7
docker build --no-cache -f Dockerfile.debian -t chapter7 .
#docker run -it --entrypoint /bin/bash chapter7
