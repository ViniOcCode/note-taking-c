FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    python3 \
    py3-pip \
    build-base \
    ninja \
    git \
    vim \
    bash


# When repo stay public just use this
WORKDIR /app

RUN pip3 install meson --break-system-packages
